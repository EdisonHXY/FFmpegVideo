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

	//����״̬�ص�
	void SetStausCall(fStatusPlayCallBack cb, void *lParm);

	//���ý��Ȼص�
	void SetPlayProcessCall(fPlayProcessCallBack cb, void *lPram);

	//����
	int Play(const char *szFileUrl, void *lwnd, CRect wndRc);
	//ֹͣ
	void Stop();
	//��ͣ
	void Pause();
	//��������
	void ContinuePlay();

	//ѭ�����ſ���
	void SetLoopStatus(bool bOpen);

	//��ȡ ��ǰ״̬
	PLAYSTATUE_FF GetPlayStatus();

	//��ȡ�ļ�ʱ�� ��Ҫ�ȵ���Play
	double GetPlayDuration();

	//��������
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

