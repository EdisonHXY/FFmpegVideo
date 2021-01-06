#pragma once
#include "FFmpeg/FFmpeg_Play.h"
class CCenterManager
{
public:
	~CCenterManager();
	static CCenterManager *GetInstance();
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
	CCenterManager();
	CFFmpeg_Play m_play;
};

