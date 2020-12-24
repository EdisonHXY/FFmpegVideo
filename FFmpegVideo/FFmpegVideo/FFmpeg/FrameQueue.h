#pragma once
/*!
 * \class 解码出来的数据
 *
 * \brief 
 *
 * \author HXY10
 * \date 十二月 2020
 */
#include <SDL_thread.h>
#include <queue>
extern "C" {

#include <libavcodec\avcodec.h>

}
enum PLAYSTATUE_FF
{
	PLAYSTATUE_FF_ING,
	PLAYSTATUE_FF_STOP,
	PLAYSTATUE_FF_PAUSE
};

#define FF_QUIT_EVENT    (SDL_USEREVENT + 2)
#define FF_PAUSE_EVENT    (SDL_USEREVENT + 3)
#define FF_REFRESH_EVENT    (SDL_USEREVENT + 4)


class CFrameQueue
{
public:
	CFrameQueue();
	~CFrameQueue();

	bool PushQueue(const AVFrame *frame);
	bool PopQueue(AVFrame **frame);
	bool Clear();
public:
	uint32_t m_nb_frames;
	static const int capacity = 30;
	std::queue<AVFrame*> m_queue;
private:

	SDL_mutex* m_mutex;
	SDL_cond * m_cond;
};

