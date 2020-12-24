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

int CCenterManager::Play(const char *szFileUrl, void *lwnd, CRect wndRc)
{
	return m_play.Play(szFileUrl, lwnd, wndRc);
}

void CCenterManager::Stop()
{
	return m_play.Stop();
}
