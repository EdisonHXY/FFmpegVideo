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
typedef void(*fPlayProcessCallBack)(int nCurrentTime, int nTotalTime, void *lParam);
class CFFmpeg_Play
{
public:
	CFFmpeg_Play();
	~CFFmpeg_Play();

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

	fPlayProcessCallBack m_processCB;
	void* m_processCBParam;

	int m_totalTimeLength;

	bool m_haveVideo;
	bool m_haveAudio;

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

