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


class CFFmpeg_Play
{
public:
	CFFmpeg_Play();
	~CFFmpeg_Play();

	//²¥·Å
	int Play(const char *szFileUrl, void *lwnd, CRect wndRc);
	//Í£Ö¹
	void Stop();
	//ÔÝÍ£
	void Pause();
private:
	AVFormatContext *m_pFormatCtx;
	CVideoPlay m_videoPlay;
	CAudioPlay m_audioPlay;
	string m_fileURL;
	void *m_showHand;
	int m_showW;
	int m_showH;
	bool m_bStop;
private:
	bool OpenUrl(const char *szFileUrl);
private:
	void DoExit();

private:
	static int ThreadPlay(void *arg); 
	void ExectPlayURL();
	static int decode_thread(void *arg);
	void ExectDecode();
};

