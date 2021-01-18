#include "stdafx.h"
#include "FFmpeg_Play.h"



CFFmpeg_Play::CFFmpeg_Play()
{
	m_pFormatCtx = NULL;
	m_statusCB = nullptr;
	m_statusCBParam = nullptr;
	m_playLoop = false;
	m_currentStatus = PLAYSTATUE_FF_STOP;
	m_processCB = 0;
	m_processCBParam = 0;
	m_totalTimeLength = 0;
}


CFFmpeg_Play::~CFFmpeg_Play()
{
	Stop();
}

void CFFmpeg_Play::SetStausCall(fStatusPlayCallBack cb, void *lParm)
{
	m_statusCB = cb;
	m_statusCBParam = lParm;
}

void CFFmpeg_Play::SetPlayProcessCall(fPlayProcessCallBack cb, void *lPram)
{
	m_processCB = cb;
	m_processCBParam = lPram;
}

int CFFmpeg_Play::Play(const char *szFileUrl, void *lwnd, CRect wndRc)
{
	m_fileURL = szFileUrl;
	m_showH = wndRc.Height();
	m_showHand = lwnd;
	m_showW = wndRc.Width();
	SDL_CreateThread(ThreadPlay, "", this);
	return 0;
}

void CFFmpeg_Play::Stop()
{
	SDL_Event event;

	event.type = FF_QUIT_EVENT;
	SDL_PushEvent(&event);

}

void CFFmpeg_Play::Pause()
{
	SDL_Event event;

	event.type = FF_PAUSE_EVENT;
	SDL_PushEvent(&event);
}

void CFFmpeg_Play::ContinuePlay()
{
	SDL_Event event;

	event.type = FF_ContinuPlay_EVENT;
	SDL_PushEvent(&event);
}

void CFFmpeg_Play::SetLoopStatus(bool bOpen)
{
	m_playLoop = bOpen;
}

PLAYSTATUE_FF CFFmpeg_Play::GetPlayStatus()
{
	return m_currentStatus;
}

bool CFFmpeg_Play::OpenUrl(const char *szFileUrl)
{
	
	// Open input file
	if (avformat_open_input(&m_pFormatCtx, szFileUrl, nullptr, nullptr) < 0)
		return false;

	if (avformat_find_stream_info(m_pFormatCtx, nullptr) < 0)
		return false;

	m_totalTimeLength = m_pFormatCtx->duration / 1000000;
	for (uint32_t i = 0; i < m_pFormatCtx->nb_streams; i++)
	{
		if (m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && m_audioPlay.m_stream_index < 0)
			m_audioPlay.m_stream_index = i;

		if (m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && m_videoPlay.m_stream_index < 0)
			m_videoPlay.m_stream_index = i;
	}

	m_haveVideo = m_videoPlay.m_stream_index >= 0;
	m_haveAudio = m_audioPlay.m_stream_index >= 0;

	if (m_videoPlay.m_stream_index < 0 && m_audioPlay.m_stream_index < 0)
		return false;
	

	if (m_haveAudio)
	{
		// Fill audio state
		AVCodec *pCodec = avcodec_find_decoder(m_pFormatCtx->streams[m_audioPlay.m_stream_index]->codec->codec_id);
		if (!pCodec)
			return false;

		m_audioPlay.m_stream = m_pFormatCtx->streams[m_audioPlay.m_stream_index];
		m_audioPlay.m_audio_ctx = avcodec_alloc_context3(pCodec);
		if (avcodec_copy_context(m_audioPlay.m_audio_ctx, m_pFormatCtx->streams[m_audioPlay.m_stream_index]->codec) != 0)
			return false;

		avcodec_open2(m_audioPlay.m_audio_ctx, pCodec, nullptr);

	}

	if (m_haveVideo)
	{
		// Fill video state
		AVCodec *pVCodec = avcodec_find_decoder(m_pFormatCtx->streams[m_videoPlay.m_stream_index]->codec->codec_id);
		if (!pVCodec)
			return false;
		m_videoPlay.m_stream = m_pFormatCtx->streams[m_videoPlay.m_stream_index];
		m_videoPlay.m_video_ctx = avcodec_alloc_context3(pVCodec);
		if (avcodec_copy_context(m_videoPlay.m_video_ctx, m_pFormatCtx->streams[m_videoPlay.m_stream_index]->codec) != 0)
			return false;

		avcodec_open2(m_videoPlay.m_video_ctx, pVCodec, nullptr);

		m_videoPlay.m_frame_timer = static_cast<double>(av_gettime()) / 1000000.0;
		m_videoPlay.m_frame_last_delay = 40e-3;
	}
	

	return true;
}

void CFFmpeg_Play::DoExit()
{
	m_totalTimeLength = 0;
	m_bStop = true;
	m_videoPlay.Stop();
	m_audioPlay.Stop();
	if (m_pFormatCtx)
	{
		avformat_close_input(&m_pFormatCtx);
	}

	SDL_Quit();
}

int CFFmpeg_Play::ThreadPlay(void *arg)
{
	CFFmpeg_Play *p = (CFFmpeg_Play*)arg;

	do 
	{
		int nRet = p->ExectPlayURL();

		if (nRet < 0)
		{
			//发生错误了 或者 停止了
			break;
		}

	} while (p->m_playLoop);

	if (p->m_statusCB)
	{
		p->m_statusCB(PLAYSTATUE_FF_Finish, p->m_statusCBParam);
	}
	p->m_currentStatus = PLAYSTATUE_FF_Finish;
	return 0;
}

double CFFmpeg_Play::GetPlayDuration()
{
	return m_totalTimeLength;
}

void CFFmpeg_Play::SetVolum(int nNum)
{
	//0-128
	if (nNum < 0)
	{
		nNum = 0;
	}
	else if (nNum > 128)
	{
		nNum = 128;
	}

	m_audioPlay.SetVolum(nNum);

}

int CFFmpeg_Play::ExectPlayURL()
{
	bool bRet = false;
	int nRet = 0;
	do
	{
		av_register_all();
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
		//打开文件
		bRet = OpenUrl(m_fileURL.c_str());
		if (!bRet)
		{
			nRet = -1;
			break;
		}
		m_bStop = false;
		m_currentStatus = PLAYSTATUE_FF_ING;
		//读取文件里的内容
		SDL_CreateThread(decode_thread, "", this); // 创建解码线程，读取packet到队列中缓存
		
		if (m_haveVideo)
		{
			//创建视频的线程进行播放
			m_videoPlay.Play(m_showHand, m_showW, m_showH);
		}
		
		if (m_haveAudio)
		{
			//创建音频的线程进行播放
			bRet = m_audioPlay.Play();
			if (!bRet)
			{
				nRet = -2;
				break;
			}
		}
		
		
		 if (m_statusCB)
		 {
			 m_statusCB(PLAYSTATUE_FF_ING, m_statusCBParam);
		 }

		//事件的循环
		SDL_Event event;
		bool bLoop = true;
		while (bLoop) // SDL event loop
		{
			SDL_WaitEvent(&event);
			switch (event.type)
			{
			case FF_QUIT_EVENT:
			case SDL_QUIT:
				bLoop = false;
				DoExit();
				nRet = -5;
				return nRet;
			case FF_REFRESH_EVENT:
			{
				if ((m_audioPlay.GetStatus() == PLAYSTATUE_FF_Finish))
				{
					SDL_CloseAudio();
					bLoop = false;
					break;
				}
				double nPts = m_audioPlay.GetAudioClock();
				if (m_processCB)
				{
					m_processCB(nPts, m_totalTimeLength, m_processCBParam);
				}

				m_videoPlay.RefreshVideo(nPts);
				break;
			}
			case FF_ContinuPlay_EVENT:
				m_audioPlay.ControlPlayPause(false);
				m_videoPlay.ControlPlayPause(false);
				m_currentStatus = PLAYSTATUE_FF_ING;
				if (m_statusCB)
				{
					m_statusCB(PLAYSTATUE_FF_ING, m_statusCBParam);
				}
				break;
			case  FF_PAUSE_EVENT:
				m_currentStatus = PLAYSTATUE_FF_PAUSE;
				m_audioPlay.ControlPlayPause(true);
				m_videoPlay.ControlPlayPause(true);
				if (m_statusCB)
				{
					m_statusCB(PLAYSTATUE_FF_PAUSE,m_statusCBParam);
				}
				break;
			default:
				break;
			}
		}

	} while (0);

	//清理
	DoExit();
	

	return nRet;
}

int CFFmpeg_Play::decode_thread(void *arg)
{
	CFFmpeg_Play *p = (CFFmpeg_Play*)arg;
	p->ExectDecode();
	return 0;
}

void CFFmpeg_Play::ExectDecode()
{
	AVPacket *packet = av_packet_alloc();

	while (!m_bStop)
	{
		//限制队列的数量
// 		if (m_audioPlay.m_audioq.m_queue.size() > 500)
// 		{
// 			continue;
// 		}
		if (m_currentStatus != PLAYSTATUE_FF_ING)
		{
			Sleep(1);
			continue;
		}
		int ret = av_read_frame(m_pFormatCtx, packet);
		if (ret < 0)
		{
			if (ret == AVERROR_EOF)
				break;
			if (m_pFormatCtx->pb->error == 0) // No error,wait for user input
			{
				SDL_Delay(100);
				continue;
			}
			else
				break;
		}

		if (packet->stream_index == m_audioPlay.m_stream_index) // audio stream
		{
			m_audioPlay.m_audioq.PushQueue(packet);
			av_packet_unref(packet);
		}

		else if (packet->stream_index == m_videoPlay.m_stream_index) // video stream
		{
			m_videoPlay.m_videoPackQ.PushQueue(packet);
			av_packet_unref(packet);
		}
		else
			av_packet_unref(packet);
	}

	av_packet_free(&packet);

	return ;
}
