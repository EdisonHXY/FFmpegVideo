#pragma once
#include "FFmpeg/FFmpeg_Play.h"
class CCenterManager
{
public:
	~CCenterManager();
	static CCenterManager *GetInstance();

	void SetStausCall(fStatusPlayCallBack cb, void *lParm);

	//播放
	int Play(const char *szFileUrl, void *lwnd, CRect wndRc);
	//停止
	void Stop();
	//暂停
	void Pause();

	//继续播放
	void ContinuePlay();

	//循环播放控制
	void SetLoopStatus(bool bOpen);

	//获取 当前状态
	PLAYSTATUE_FF GetPlayStatus();

private:
	CCenterManager();
	CFFmpeg_Play m_play;
};

