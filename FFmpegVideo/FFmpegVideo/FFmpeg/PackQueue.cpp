#include "stdafx.h"
#include "PackQueue.h"


CPackQueue::CPackQueue()
{
	m_nb_packets = 0;
	m_size = 0;

	m_mutex = SDL_CreateMutex();
	m_cond = SDL_CreateCond();
}


CPackQueue::~CPackQueue()
{
	SDL_DestroyMutex(m_mutex);
	SDL_DestroyCond(m_cond);
}

bool CPackQueue::PushQueue(const AVPacket *packet)
{
	AVPacket *pkt = av_packet_alloc();
	if (av_packet_ref(pkt, packet) < 0)
		return false;

	SDL_LockMutex(m_mutex);
	m_queue.push(pkt);

	m_size += pkt->size;
	m_nb_packets++;

	SDL_CondSignal(m_cond);
	SDL_UnlockMutex(m_mutex);
	return true;
}

bool CPackQueue::PopQueue(AVPacket *packet, bool block)
{
	bool ret = false;

	SDL_LockMutex(m_mutex);
	//while (true)
	{
		if (!m_queue.empty())
		{
			if (av_packet_ref(packet,m_queue.front()) < 0)
			{
				SDL_UnlockMutex(m_mutex);
				return false;
			}
			AVPacket *pkt = m_queue.front();

			m_queue.pop();
			av_packet_free(&pkt);
			m_nb_packets--;
			m_size -= packet->size;
			SDL_UnlockMutex(m_mutex);
			return true;
		}
// 		else
// 		{
// 			SDL_CondWait(m_cond, m_mutex);
// 
// 		}
	}
	
	
	SDL_UnlockMutex(m_mutex);
	return ret;
}

bool CPackQueue::Clear()
{
	SDL_LockMutex(m_mutex);
	while (!m_queue.empty())
	{
		AVPacket *pkt = m_queue.front();
		m_queue.pop();

		av_packet_free(&pkt);
	}
	m_nb_packets = 0;
	m_size = 0;
	SDL_UnlockMutex(m_mutex);
	return true;
}
