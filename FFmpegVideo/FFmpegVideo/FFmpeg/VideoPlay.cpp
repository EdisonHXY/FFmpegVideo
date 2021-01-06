#include "stdafx.h"
#include "VideoPlay.h"

static const double SYNC_THRESHOLD = 0.01;
static const double NOSYNC_THRESHOLD = 10.0;
CVideoPlay::CVideoPlay()
{
	m_video_ctx = NULL;
	m_stream_index = -1;
	m_status = PLAYSTATUE_FF_STOP;

	m_frame_timer = 0.0;
	m_frame_last_delay = 0.0;
	m_frame_last_pts = 0.0;
	m_video_clock = 0.0;

	m_frame = nullptr;
	m_displayFrame = nullptr;
	m_window = nullptr;
	m_renderer = nullptr;
	m_stopLock = SDL_CreateMutex();
	m_decodThread = nullptr;
}


CVideoPlay::~CVideoPlay()
{
	Stop();
	SDL_DestroyMutex(m_stopLock);
}

bool CVideoPlay::Stop()
{
	m_status = PLAYSTATUE_FF_STOP;
	Sleep(500);
	SDL_LockMutex(m_stopLock);
	if (m_frame)
	{
		av_frame_free(&m_frame);
		m_frame = nullptr;
	}
	if (m_displayFrame && m_displayFrame->data[0])
	{
		av_free(m_displayFrame->data[0]);
	}
	if (m_displayFrame)
	{
		av_frame_free(&m_displayFrame);
		m_displayFrame = nullptr;
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

	if (m_bmp)
	{
		SDL_DestroyTexture(m_bmp);
		m_bmp = nullptr;
	}
	if (m_video_ctx)
	{

		avcodec_close(m_video_ctx);
		avcodec_free_context(&m_video_ctx);
		m_video_ctx = NULL;
	}
	m_videoPackQ.Clear();
	m_videoFrameQ.Clear();
	m_frame_timer = 0.0;
	m_frame_last_delay = 0.0;
	m_frame_last_pts = 0.0;
	m_video_clock = 0.0;
	m_stream_index = -1;
	m_stream = nullptr;
	SDL_UnlockMutex(m_stopLock);
	return true;
}

void CVideoPlay::Play(void *lwnd, int width, int height)
{
	m_status = PLAYSTATUE_FF_ING;
	
	
	m_window = SDL_CreateWindowFrom(lwnd);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);

	m_bmp = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
		width, height);

	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = width;
	m_rect.h = height;
	
	m_frame = av_frame_alloc();
	m_displayFrame = av_frame_alloc();

	m_displayFrame->format = AV_PIX_FMT_YUV420P;
	m_displayFrame->width = width;
	m_displayFrame->height = height;

	int numBytes = avpicture_get_size((AVPixelFormat)m_displayFrame->format, m_displayFrame->width, m_displayFrame->height);
	uint8_t *buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));

	avpicture_fill((AVPicture*)m_displayFrame, buffer, (AVPixelFormat)m_displayFrame->format, m_displayFrame->width, m_displayFrame->height);

	m_decodThread = SDL_CreateThread(Decode, "", this);
 
 	ScheduleRefresh(40); // start display

	SDL_ShowWindow(m_window);
}

void CVideoPlay::ControlPlayPause(bool bPause)
{
	m_status = bPause ?  PLAYSTATUE_FF_PAUSE : PLAYSTATUE_FF_ING;

	if (!bPause)
	{
		m_frame_timer = static_cast<double>(av_gettime()) / 1000000.0;
	}
}

double CVideoPlay::Synchronize(AVFrame *srcFrame, double pts)
{
	double frame_delay;

	if (pts != 0)
		m_video_clock = pts; // Get pts,then set video clock to it
	else
		pts = m_video_clock; // Don't get pts,set it to video clock

	frame_delay = av_q2d(m_stream->codec->time_base);
	frame_delay += srcFrame->repeat_pict * (frame_delay * 0.5);

	m_video_clock += frame_delay;
	return pts;
}

PLAYSTATUE_FF CVideoPlay::GetStatus()
{
	return m_status;
}

void CVideoPlay::RefreshVideo(double dtime)
{
	if (m_status == PLAYSTATUE_FF_PAUSE)
	{
		ScheduleRefresh(100);
		return;
	}

	if (m_stream_index < 0 || m_status != PLAYSTATUE_FF_ING)
	{
		ScheduleRefresh(100);
		return;
	}

	
	if (m_videoFrameQ.m_queue.empty())
	{
		//m_status = PLAYSTATUE_FF_STOP;
		ScheduleRefresh(1);
	}
	else
	{
		SDL_LockMutex(m_stopLock);
		m_videoFrameQ.PopQueue(&m_frame);
		// 将视频同步到音频上，计算下一帧的延迟时间
		double current_pts = *(double*)m_frame->opaque;
		double delay = current_pts - m_frame_last_pts;
		if (delay <= 0 || delay >= 1.0)
			delay = m_frame_last_delay;

		m_frame_last_delay = delay;
		m_frame_last_pts = current_pts;

		// 当前显示帧的PTS来计算显示下一帧的延迟
		double ref_clock = dtime;

		double diff = current_pts - ref_clock;// diff < 0 => video slow,diff > 0 => video quick

		double threshold = (delay > SYNC_THRESHOLD) ? delay : SYNC_THRESHOLD;

		if (fabs(diff) < NOSYNC_THRESHOLD) // 不同步
		{
			if (diff <= -threshold) // 慢了，delay设为0
			{
				delay = 0;
			}	
			else if (diff >= threshold) // 快了，加倍delay
			{
				delay = diff;

			}
				
		}
		m_frame_timer += delay;
		double actual_delay = m_frame_timer - static_cast<double>(av_gettime()) / 1000000.0;
		if (actual_delay <= 0.010)
			actual_delay = 0.010;

		ScheduleRefresh(static_cast<int>(actual_delay * 1000 + 0.5));

		SwsContext *sws_ctx = sws_getContext(m_video_ctx->width, m_video_ctx->height, m_video_ctx->pix_fmt,
			m_displayFrame->width, m_displayFrame->height, (AVPixelFormat)m_displayFrame->format, SWS_BILINEAR, nullptr, nullptr, nullptr);

		sws_scale(sws_ctx, (uint8_t const * const *)m_frame->data, m_frame->linesize, 0,
			m_video_ctx->height, m_displayFrame->data, m_displayFrame->linesize);

		// Display the image to screen
		SDL_UpdateYUVTexture(m_bmp, &(m_rect), m_displayFrame->data[0], m_displayFrame->linesize[0], m_displayFrame->data[1], m_displayFrame->linesize[1], m_displayFrame->data[2], m_displayFrame->linesize[2]);

		//SDL_UpdateTexture(video->bmp, &(video->rect), video->displayFrame->data[0], video->displayFrame->linesize[0]);
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_bmp, &m_rect, &m_rect);
		SDL_RenderPresent(m_renderer);

		sws_freeContext(sws_ctx);
		av_frame_unref(m_frame);
		SDL_UnlockMutex(m_stopLock);
	}
	
	
}

int CVideoPlay::Decode(void *arg)
{
	CVideoPlay *p = (CVideoPlay*)arg;
	p->HanldeDecode();
	return 0;
}

void CVideoPlay::HanldeDecode()
{
	AVFrame *frame = av_frame_alloc();

	AVPacket packet;
	double pts;
	while (m_status != PLAYSTATUE_FF_STOP)
	{

		if (m_videoPackQ.m_queue.empty() || m_status == PLAYSTATUE_FF_PAUSE)
		{
			Sleep(1);
			continue;
		}

		bool bRet = m_videoPackQ.PopQueue(&packet, true);

		int ret = avcodec_send_packet(m_video_ctx, &packet);
		if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
			continue;

		ret = avcodec_receive_frame(m_video_ctx, frame);
		if (ret < 0 && ret != AVERROR_EOF)
			continue;

		if ((pts = av_frame_get_best_effort_timestamp(frame)) == AV_NOPTS_VALUE)
			pts = 0;

		pts *= av_q2d(m_stream->time_base);

		pts = Synchronize(frame, pts);

		frame->opaque = &pts;

		if (m_videoFrameQ.m_nb_frames >= CFrameQueue::capacity)
			SDL_Delay(500 * 2);

		m_videoFrameQ.PushQueue(frame);

		av_frame_unref(frame);
	}

	av_frame_free(&frame);
}

// 延迟delay ms后刷新video帧
void CVideoPlay::ScheduleRefresh(int delay)
{
	SDL_AddTimer(delay, sdl_refresh_timer_cb, this);
}

uint32_t CVideoPlay::sdl_refresh_timer_cb(uint32_t interval, void *opaque)
{
	SDL_Event event;
	event.type = FF_REFRESH_EVENT;
	event.user.data1 = opaque;
	SDL_PushEvent(&event);
	return 0; /* 0 means stop timer */
}
