#include "ResetGGMager.h"
#include "GuangGao.h"

#define SCHEDULE CCDirector::sharedDirector()->getScheduler() 

ResetGGMager* ResetGGMager::m_Self = NULL;
ResetGGMager* ResetGGMager::getInstance()
{
	if (!m_Self)
	{
		m_Self = new ResetGGMager();
	}
	
	return m_Self;
}
ResetGGMager::ResetGGMager(void)
{
	m_ResetTime = 0;
	SCHEDULE->scheduleUpdateForTarget(this, 0, false);
}
ResetGGMager::~ResetGGMager(void)
{
	SCHEDULE->unscheduleUpdateForTarget(this);
}
void ResetGGMager::update(float dt)
{
	if (Ext_IsResetGG)
	{
		Ext_IsResetGG = false;
		m_ResetTime = 0;
	}
	else
	{
		m_ResetTime++;
	}
	if (m_ResetTime == 18000)
	{
		this->pause();
		CCDirector::sharedDirector()->pushScene(GuangGao::getScene());
	}
}
void ResetGGMager::pause()
{
	SCHEDULE->pauseTarget(m_Self);
}
void ResetGGMager::resume()
{
	SCHEDULE->resumeTarget(m_Self);
}