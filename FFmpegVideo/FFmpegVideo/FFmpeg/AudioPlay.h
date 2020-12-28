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

	//����
	bool Play();

	//ֹͣ
	bool Stop();

	//��ȡ״̬
	PLAYSTATUE_FF GetStatus();

	//��ȡʱ��
	double GetAudioClock();

public:
	const uint32_t BUFFER_SIZE;// �������Ĵ�С
	CPackQueue m_audioq;
	double m_audio_clock; // audio clock
	AVStream *m_stream; // audio stream
	int m_stream_index;
	uint8_t *m_audio_buff;       // ��������ݵĻ���ռ�
	uint32_t m_audio_buff_size;  // buffer�е��ֽ���
	uint32_t m_audio_buff_index; // buffer��δ�������ݵ�index

	AVCodecContext *m_audio_ctx; // �Ѿ�����avcodec_open2��
	PLAYSTATUE_FF m_status;
	SDL_mutex* m_stopLock;
private:
	static void audio_callback(void* userdata, Uint8 *stream, int len);
	void HandleAudioData(Uint8 *stream, int len);
	int audio_decode_frame(uint8_t *audio_buf, int buf_size);
};

