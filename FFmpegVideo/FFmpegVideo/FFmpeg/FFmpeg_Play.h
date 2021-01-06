#pragma once
#include "SDL.h"
#include <string>
using namespace std;
extern "C"
{
#include <libavutil/time.h>
}


#include "AudioPlay.h"
#include "VideoPlay.h"
#include <iostream>
using namespace std;

typedef void(*fStatusPlayCallBack)(PLAYSTATUE_FF ss, void *lParam);
class CFFmpeg_Play
{
public:
	CFFmpeg_Play();
	~CFFmpeg_Play();

	//设置回调
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
	AVFormatContext *m_pFormatCtx;
	CVideoPlay m_videoPlay;
	CAudioPlay m_audioPlay;
	string m_fileURL;
	void *m_showHand;
	int m_showW;
	int m_showH;
	bool m_bStop;
	fStatusPlayCallBack m_statusCB;
	void *m_statusCBParam;
	PLAYSTATUE_FF m_currentStatus;


private:
	bool OpenUrl(const char *szFileUrl);
private:
	void DoExit();

private:
	static int ThreadPlay(void *arg); 
	int ExectPlayURL();
	static int decode_thread(void *arg);
	void ExectDecode();
private:
	bool m_playLoop;



};

