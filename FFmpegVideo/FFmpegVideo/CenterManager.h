#pragma once
#include "FFmpeg/FFmpeg_Play.h"
class CCenterManager
{
public:
	~CCenterManager();
	static CCenterManager *GetInstance();

	//����
	int Play(const char *szFileUrl, void *lwnd, CRect wndRc);
	//ֹͣ
	void Stop();
	//��ͣ
	void Pause();
private:
	CCenterManager();
	CFFmpeg_Play m_play;
};

