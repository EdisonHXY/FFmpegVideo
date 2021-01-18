#pragma once
/*!
 * \class 读取出来的待解码数据
 *
 * \brief 
 *
 * \author HXY10
 * \date 十二月 2020
 */
#include <queue>
#include <SDL.h>
#include <SDL_thread.h>
extern "C" {
#include <libavcodec\avcodec.h>
}


class CPackQueue
{
public:
	CPackQueue();
	~CPackQueue();

	bool PushQueue(const AVPacket *packet);
	bool PopQueue(AVPacket *packet, bool block);
	bool Clear();
public:
	std::queue<AVPacket*> m_queue;
	Uint32    m_nb_packets;
	Uint32    m_size;
	SDL_mutex *m_mutex;
	SDL_cond  *m_cond;
};

