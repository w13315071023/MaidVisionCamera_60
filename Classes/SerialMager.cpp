#include "SerialMager.h"
#include "DataMager.h"
#include "MovieVideoLayer.h"
#include "PostureAnalysisScene.h"

SerialMager* SerialMager::sInstence = NULL;
SerialMager* SerialMager::getInstence()
{
	if (sInstence == NULL)
	{
		sInstence = new SerialMager();
		if (!sInstence->init())
		{
			delete sInstence;
			sInstence = NULL;
		}
	}

	return sInstence;
}
void SerialMager::unLoadInstence()
{
	if (sInstence)
	{
		delete sInstence;
		sInstence = NULL;
	}
}
SerialMager::SerialMager(void)
{
	m_curMsg = 0;
}
bool SerialMager::init()
{
	m_IsCom = false;
	int length;
	m_IsCom = get_com_port(&com_num, length);

	if (m_IsCom)
	{
		open_com_port(com_num);
	}

	return true;
}
bool SerialMager::getComPort()
{
	int length;
	return get_com_port(&com_num, length);
}
void SerialMager::setThreshold(int threshold)
{
	if (m_IsCom)
	{
		set_threshold(threshold);
	}
}
void SerialMager::SeriaUpdate()
{
	if (!m_IsCom)
	{
		return;
	}
	int msg = 0;
	msg = fetch_msg();
	if (msg == 0 || m_curMsg == msg)
	{
		return;
	}
	m_curMsg = msg;
	Ext_IsResetGG = true;
	if (PostureAnalysisScene::m_bIsPlayVideo)
	{
		return;
	}

	if (m_curMsg == 2)
	{
		if (m_Delegate1)
		{
			m_Delegate1->Record(true);
		}
		if (m_Delegate2)
		{
			m_Delegate2->Record(true);
		}
	}
	else if (m_curMsg == 3)
	{
		if (Ext_IsRecordBegin == true)
		{
			return;
		}
		Ext_IsRecordBegin = true;
		Sleep(Ext_VideoSleep);
		Ext_IsThreadOn = false;

		if (m_Delegate1)
		{
			m_Delegate1->RecordOk();
		}
		if (m_Delegate2)
		{
			m_Delegate2->RecordOk();
		}
		//PostureAnalysisScene::m_bIsPlayVideo = true;
		PostureAnalysisScene* pLayer = (PostureAnalysisScene*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(98);
		CCMenuItemToggle* pToggle = (CCMenuItemToggle*)(pLayer->m_pMenu->getChildByTag(99));
		pToggle->setSelectedIndex(1);
		pLayer->CallbackPause(pToggle);
	}
	else if (m_curMsg == 4)
	{
		if (m_Delegate1)
		{
			m_Delegate1->Record(false);
		}
		if (m_Delegate2)
		{
			m_Delegate2->Record(false);
		}
	}
}
SerialMager::~SerialMager(void)
{
}
