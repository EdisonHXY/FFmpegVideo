#pragma once
#include "FFmpeg/FFmpeg_Play.h"
class CCenterManager
{
public:
	~CCenterManager();
	static CCenterManager *GetInstance();
	//设置状态回调
	void SetStausCall(fStatusPlayCallBack cb, void *lParm);
	//设置进度回调
	void SetPlayProcessCall(fPlayProcessCallBack cb, void *lPram);

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
	//获取文件时长 需要先调用Play
	double GetPlayDuration();

	//设置音量
	void SetVolum(int nNum);

private:
	CCenterManager();
	CFFmpeg_Play m_play;
};

