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

	//播放 多路画面时 只能打开一路的音频 enableAudio
	int Play(const char *szFileUrl, void *lwnd, CRect wndRc, bool enableAudio = true, bool enableVideo  = true);
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

	//获取地址
	string GetPlayUrl();

	//设置缓存的最大包数
	void SetPacketNum(int nNum);

	static void InitData();
	static void UnInitData();

private:
	AVFormatContext *m_pFormatCtx;
	CVideoPlay m_videoPlay;
	CAudioPlay m_audioPlay;
	string m_fileURL;
	void *m_showHand;
	int m_showW;
	int m_showH;
	bool m_bStop;
	bool m_controlEnableAudio;
	bool m_controlEnableVideo;
	fStatusPlayCallBack m_statusCB;
	void *m_statusCBParam;
	PLAYSTATUE_FF m_currentStatus;

	fPlayProcessCallBack m_processCB;
	void* m_processCBParam;

	int m_totalTimeLength;

	bool m_haveVideo;
	bool m_haveAudio;
	unsigned int m_readPacketMaxNum;
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

