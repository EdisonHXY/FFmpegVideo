#pragma once
#include "PackQueue.h"
#include "FrameQueue.h"
extern "C" {

#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libswscale\swscale.h>
#include <libavutil\time.h>
}
class CVideoPlay
{
public:
	CVideoPlay();
	~CVideoPlay();
	bool Stop();
	void Play(void *lwnd, int width, int height);
	
	PLAYSTATUE_FF GetStatus();
	void RefreshVideo(double dtime);

public:
	CPackQueue m_videoPackQ;
	CFrameQueue m_videoFrameQ;

	AVCodecContext *m_video_ctx;  // have already be opened by avcodec_open2

	AVFrame *m_frame;
	AVFrame *m_displayFrame;
	AVStream *m_stream;           // video stream
	int m_stream_index;
	double m_frame_timer;         // Sync fields
	double m_frame_last_pts;
	double m_frame_last_delay;
	double m_video_clock;

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_bmp;
	SDL_Rect m_rect;

	PLAYSTATUE_FF m_status;
private:
	double Synchronize(AVFrame *srcFrame, double pts);
	static int Decode(void *arg);
	void HanldeDecode();
	void ScheduleRefresh(int delay);
	static uint32_t sdl_refresh_timer_cb(uint32_t interval, void *opaque);

};

