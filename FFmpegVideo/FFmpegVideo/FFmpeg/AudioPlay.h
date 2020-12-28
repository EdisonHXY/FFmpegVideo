#pragma once
#include "PackQueue.h"
#include "FrameQueue.h"
extern "C" {

#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}
class CAudioPlay
{
public:
	CAudioPlay();
	~CAudioPlay();

	//播放
	bool Play();

	//停止
	bool Stop();

	//获取状态
	PLAYSTATUE_FF GetStatus();

	//获取时钟
	double GetAudioClock();

public:
	const uint32_t BUFFER_SIZE;// 缓冲区的大小
	CPackQueue m_audioq;
	double m_audio_clock; // audio clock
	AVStream *m_stream; // audio stream
	int m_stream_index;
	uint8_t *m_audio_buff;       // 解码后数据的缓冲空间
	uint32_t m_audio_buff_size;  // buffer中的字节数
	uint32_t m_audio_buff_index; // buffer中未发送数据的index

	AVCodecContext *m_audio_ctx; // 已经调用avcodec_open2打开
	PLAYSTATUE_FF m_status;
	SDL_mutex* m_stopLock;
private:
	static void audio_callback(void* userdata, Uint8 *stream, int len);
	void HandleAudioData(Uint8 *stream, int len);
	int audio_decode_frame(uint8_t *audio_buf, int buf_size);
};

