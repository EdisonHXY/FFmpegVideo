#include "stdafx.h"
#include "FrameQueue.h"


CFrameQueue::CFrameQueue()
{
	m_nb_frames = 0;

	m_mutex = SDL_CreateMutex();
	m_cond = SDL_CreateCond();
}


CFrameQueue::~CFrameQueue()
{
}

bool CFrameQueue::PushQueue(const AVFrame *frame)
{
	AVFrame* p = av_frame_alloc();

	int ret = av_frame_ref(p, frame);
	if (ret < 0)
		return false;

	p->opaque = (void *)new double(*(double*)p->opaque); //上一个指向的是一个局部的变量，这里重新分配pts空间

	SDL_LockMutex(m_mutex);
	m_queue.push(p);

	m_nb_frames++;

	SDL_CondSignal(m_cond);
	SDL_UnlockMutex(m_mutex);

	return true;
}

bool CFrameQueue::PopQueue(AVFrame **frame)
{
	bool ret = true;

	SDL_LockMutex(m_mutex);
	//while (true)
	{
		if (!m_queue.empty())
		{
			if (av_frame_ref(*frame, m_queue.front()) < 0)
			{
				SDL_UnlockMutex(m_mutex);
				return false;
			}

			auto tmp = m_queue.front();
			m_queue.pop();

			av_frame_free(&tmp);

			m_nb_frames--;
			SDL_UnlockMutex(m_mutex);
			return true;
		}
// 		else
// 		{
// 			SDL_CondWait(m_cond, m_mutex);
// 		}

	}
	

	SDL_UnlockMutex(m_mutex);
	return ret;
}

bool CFrameQueue::Clear()
{
	SDL_LockMutex(m_mutex);
	while (!m_queue.empty())
	{
		m_queue.pop();
	}
	SDL_UnlockMutex(m_mutex);
	return true;
}
