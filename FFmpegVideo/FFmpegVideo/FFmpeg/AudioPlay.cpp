#include "stdafx.h"
#include "AudioPlay.h"


CAudioPlay::CAudioPlay() :BUFFER_SIZE(192000)
{
	m_audio_ctx = NULL;

	m_stream_index = -1;
	m_stream = NULL;

	m_audio_clock = 0;

	m_audio_buff = new uint8_t[BUFFER_SIZE];
	m_audio_buff_size = 0;
	m_audio_buff_index = 0;

	m_status = PLAYSTATUE_FF_STOP;
	m_stopLock = SDL_CreateMutex();
}


CAudioPlay::~CAudioPlay()
{

	if (m_audio_buff)
		delete[] m_audio_buff;

	SDL_DestroyMutex(m_stopLock);
}

bool CAudioPlay::Play()
{
	SDL_AudioSpec desired;
	desired.freq = m_audio_ctx->sample_rate;
	desired.channels = m_audio_ctx->channels;
	desired.format = AUDIO_S16SYS;
	desired.samples = 1024;
	desired.silence = 0;
	desired.userdata = this;
	desired.callback = audio_callback;

	if (SDL_OpenAudio(&desired, nullptr) < 0)
	{
		return false;
	}
	m_status = PLAYSTATUE_FF_ING;
	SDL_PauseAudio(0); // playing
	return true;
}

bool CAudioPlay::Stop()
{
	SDL_PauseAudio(1);
	m_status = PLAYSTATUE_FF_STOP;
	SDL_LockMutex(m_stopLock);

	m_audioq.Clear();
	
	SDL_CloseAudio();
	m_audio_clock = 0;
	m_audio_buff_size = 0;
	m_audio_buff_index = 0;

	if (m_audio_ctx)
	{
		// Close the codec
		avcodec_close(m_audio_ctx);
		avcodec_free_context(&m_audio_ctx);
		m_audio_ctx = NULL;
	}
	m_stream_index = -1;
	m_stream = nullptr;
	SDL_UnlockMutex(m_stopLock);
	return true;
}

void CAudioPlay::ControlPlayPause(bool bPause)
{
	if (bPause)
	{
		m_status = PLAYSTATUE_FF_PAUSE;
		SDL_PauseAudio(1);
	}
	else
	{
		m_status = PLAYSTATUE_FF_ING;
		SDL_PauseAudio(0);
	}
}

PLAYSTATUE_FF CAudioPlay::GetStatus()
{
	return m_status;
}

double CAudioPlay::GetAudioClock()
{

	int hw_buf_size = m_audio_buff_size - m_audio_buff_index;
	int bytes_per_sec = m_stream->codec->sample_rate * m_audio_ctx->channels * 2;

	double pts = m_audio_clock - static_cast<double>(hw_buf_size) / bytes_per_sec;


	return pts;
}

void CAudioPlay::audio_callback(void* userdata, Uint8 *stream, int len)
{
	CAudioPlay *p = (CAudioPlay*)userdata;
	SDL_LockMutex(p->m_stopLock);
	p->HandleAudioData(stream,len);
	SDL_UnlockMutex(p->m_stopLock);
}

void CAudioPlay::HandleAudioData(Uint8 *stream, int len)
{
	SDL_memset(stream, 0, len);

	if (m_status == PLAYSTATUE_FF_PAUSE || m_stream_index < 0)
	{
		return;
	}

	int audio_size = 0;
	int len1 = 0;
	while (len > 0)// 向设备发送长度为len的数据
	{
		if (m_audio_buff_index >= m_audio_buff_size) // 缓冲区中无数据
		{
			// 从packet中解码数据
			audio_size = audio_decode_frame( m_audio_buff, sizeof(m_audio_buff));
			if (audio_size < 0) // 没有解码到数据或出错，填充0
			{
				m_audio_buff_size = 0;
				memset(m_audio_buff, 0, m_audio_buff_size);
				if (m_audioq.m_queue.size() <=0)
				{
					m_status = PLAYSTATUE_FF_Finish;
				}
				
				break;
			}
			else
				m_audio_buff_size = audio_size;

			m_audio_buff_index = 0;
		}
		len1 = m_audio_buff_size - m_audio_buff_index; // 缓冲区中剩下的数据长度
		if (len1 > len) // 向设备发送的数据长度为len
			len1 = len;

		SDL_MixAudio(stream, m_audio_buff + m_audio_buff_index, len, SDL_MIX_MAXVOLUME);

		len -= len1;
		stream += len1;
		m_audio_buff_index += len1;
		
	}

}

int CAudioPlay::audio_decode_frame(uint8_t *audio_buf, int buf_size)
{
	
	int data_size = 0;
	AVPacket pkt;
	SwrContext *swr_ctx = nullptr;
	static double clock = 0;

	if (m_status == PLAYSTATUE_FF_STOP)
		return -1;
	if (!m_audioq.PopQueue(&pkt, true))
		return -1;

	if (pkt.pts != AV_NOPTS_VALUE)
	{
		m_audio_clock = av_q2d(m_stream->time_base) * pkt.pts;
	}
	int ret = avcodec_send_packet(m_audio_ctx, &pkt);
	if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
		return -1;
	AVFrame *frame = av_frame_alloc();
	ret = avcodec_receive_frame(m_audio_ctx, frame);
	if (ret < 0 && ret != AVERROR_EOF)
		return -1;

	// 设置通道数或channel_layout
	if (frame->channels > 0 && frame->channel_layout == 0)
		frame->channel_layout = av_get_default_channel_layout(frame->channels);
	else if (frame->channels == 0 && frame->channel_layout > 0)
		frame->channels = av_get_channel_layout_nb_channels(frame->channel_layout);

	AVSampleFormat dst_format = AV_SAMPLE_FMT_S16;//av_get_packed_sample_fmt((AVSampleFormat)frame->format);
	Uint64 dst_layout = av_get_default_channel_layout(frame->channels);
	// 设置转换参数
	swr_ctx = swr_alloc_set_opts(nullptr, dst_layout, dst_format, frame->sample_rate,
		frame->channel_layout, (AVSampleFormat)frame->format, frame->sample_rate, 0, nullptr);
	if (!swr_ctx || swr_init(swr_ctx) < 0)
		return -1;

	// 计算转换后的sample个数 a * b / c
	uint64_t dst_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx, frame->sample_rate) + frame->nb_samples, frame->sample_rate, frame->sample_rate, AVRounding(1));
	// 转换，返回值为转换后的sample个数
	int nb = swr_convert(swr_ctx, &audio_buf, static_cast<int>(dst_nb_samples), (const uint8_t**)frame->data, frame->nb_samples);
	data_size = frame->channels * nb * av_get_bytes_per_sample(dst_format);

	// 每秒钟音频播放的字节数 sample_rate * channels * sample_format(一个sample占用的字节数)
	m_audio_clock += static_cast<double>(data_size) / (2 * m_stream->codec->channels * m_stream->codec->sample_rate);


	av_frame_free(&frame);
	swr_free(&swr_ctx);

	return data_size;
}
