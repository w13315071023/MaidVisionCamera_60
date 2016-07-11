#include "VideoClass.h"


VideoClass::VideoClass(void)
{
	m_Width = 640;
	m_Height = 480;
	m_IsPlayOver = true;
	m_pTexture = new CCTexture2D();
	m_pSprite = new CCSprite();
	m_pTexture->initWithData(
		NULL,
		kTexture2DPixelFormat_RGB888,
		0,
		0,
		CCSize(640, 480));
	m_pSprite->initWithTexture(m_pTexture);
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(ccp(0.5,0.5));
}


VideoClass::~VideoClass(void)
{
	m_pTexture->release();
	if (!m_VideoList.empty())
	{
		m_VideoIter = m_VideoList.begin();
		for (m_VideoIter; m_VideoIter != m_VideoList.end(); m_VideoIter++)
		{
			av_free(*m_VideoIter);
		}
	}
}
void VideoClass::ShowVideo()
{
	if (m_VideoList.empty())
	{
		m_IsPlayOver = true;
		return;
	}
	if (m_VideoIter != m_VideoList.end())
	{
		m_pTexture->updateVideoWithData(
			*m_VideoIter,
			kTexture2DPixelFormat_RGB888,
			640,
			480,
			CCSize(630, 470));
		m_pSprite->initWithTexture(m_pTexture);
		m_VideoIter++;
	}
	else
	{
		m_IsPlayOver = true;
		m_VideoIter = m_VideoList.begin();
	}
}
void VideoClass::ShowDemoVideo()
{                                       
	if (m_VideoList.empty())
	{
		m_IsPlayOver = true;
		return;
	}
	if (m_VideoIter != m_VideoList.end())
	{
		m_pTexture->updateVideoWithData(
			*m_VideoIter,
			kTexture2DPixelFormat_RGB888,
			m_Width,
			m_Height,
			CCSize(630, 470));
		m_pSprite->initWithTexture(m_pTexture);
		m_VideoIter++;
	}
	else
	{
		m_IsPlayOver = true;
		m_VideoIter = m_VideoList.begin();
	}
}
void VideoClass::ReSetVideo()
{
	this->m_VideoIter = this->m_VideoList.begin();
	this->ShowVideo();
}
void VideoClass::ReSetDemoVideo()
{
	this->m_VideoIter = this->m_VideoList.begin();
	this->ShowDemoVideo();
}