#pragma once
#include "FFmpeg/FFmpeg_Play.h"
class CCenterManager
{
public:
	~CCenterManager();
	static CCenterManager *GetInstance();

	//²¥·Å
	int Play(const char *szFileUrl, void *lwnd, CRect wndRc);
	//Í£Ö¹
	void Stop();
	//ÔÝÍ£
	void Pause();
private:
	CCenterManager();
	CFFmpeg_Play m_play;
};

