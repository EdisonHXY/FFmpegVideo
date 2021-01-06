#include "stdafx.h"
#include "CenterManager.h"


CCenterManager::CCenterManager()
{
}


CCenterManager::~CCenterManager()
{
}

CCenterManager * CCenterManager::GetInstance()
{
	static CCenterManager cen = CCenterManager();
	return &cen;
}

void CCenterManager::SetStausCall(fStatusPlayCallBack cb, void *lParm)
{
	m_play.SetStausCall(cb, lParm);
}

int CCenterManager::Play(const char *szFileUrl, void *lwnd, CRect wndRc)
{
	return m_play.Play(szFileUrl, lwnd, wndRc);
}

void CCenterManager::Stop()
{
	return m_play.Stop();
}

void CCenterManager::Pause()
{
	return m_play.Pause();
}

void CCenterManager::ContinuePlay()
{
	return m_play.ContinuePlay();
}

void CCenterManager::SetLoopStatus(bool bOpen)
{
	return m_play.SetLoopStatus(bOpen);
}

PLAYSTATUE_FF CCenterManager::GetPlayStatus()
{
	return m_play.GetPlayStatus();
}
