#include "SettingScene.h"
#include "MovieVideoLayer.h"
#include "RecordClass.h"
#include "UINode.h"
#include "MyMenu.h"

CCScene* SettingScene::getScene()
{
	CCScene* scene = CCScene::create();
	if (scene)
	{
		CCLayer* layer = SettingScene::create();
		scene->addChild(layer);
	}
	else
	{
		printf("Error:createScene");
	}
	return scene;
}
SettingScene::SettingScene(void)
{
}
SettingScene::~SettingScene(void)
{
}
bool SettingScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSprite* pBackGround1 = CCSprite::create("SettingUI/Bg1.png");
	CCSprite* pBackGround2 = CCSprite::create("SettingUI/Bg2.png");
	pBackGround1->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	pBackGround2->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(pBackGround1,-2);
	this->addChild(pBackGround2,-1);
	CCSprite* pSetting = CCSprite::create("SettingUI/shezhiFont.png");
	pSetting->setPosition(ccp(324,890));
	//设置靶心距离
	CCSprite* pBaxin = CCSprite::create("SettingUI/baxinFont.png");
	pBaxin->setPosition(ccp(600, 430));
	this->addChild(pBaxin);
	UINode* pNode = UINode::create();
	pNode->setPosition(ccp(1140,430));
	this->addChild(pNode);
	//视频延迟
	CCSprite* pVidelSleep = CCSprite::create("SettingUI/yanchiFont.png");
	pVidelSleep->setPosition(ccp(600, 530));
	m_VideoSleepSlider = CCControlSlider::create("SettingUI/gdtBg.png", "SettingUI/gdtQj.png", "SettingUI/gdtAn.png");
	m_VideoSleepSlider->setPosition(ccp(1100, 530));
	m_VideoSleepSlider->setMaximumValue(1500);
	m_VideoSleepSlider->setMinimumValue(500);
	m_VideoSleepSlider->setValue(Ext_VideoSleep);
	m_VideoSleepSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::valueChanged), CCControlEventValueChanged);

	char name[32];
	sprintf(name, "%d", Ext_VideoSleep);
	m_VideoSleepLabel = CCLabelTTF::create(name, "arial", 24);
	m_VideoSleepLabel->setPosition(ccp(1500, 530));
	
	//声音预制
	CCSprite* pSerialThreshold = CCSprite::create("SettingUI/shengyinFont.png");
	pSerialThreshold->setPosition(ccp(600, 630));

	m_SerialThresholdSlider = CCControlSlider::create("SettingUI/gdtBg.png", "SettingUI/gdtQj.png", "SettingUI/gdtAn.png");
	m_SerialThresholdSlider->setPosition(ccp(1100, 630));
	m_SerialThresholdSlider->setMaximumValue(1000);
	m_SerialThresholdSlider->setMinimumValue(500);
	m_SerialThresholdSlider->setValue(Ext_SerialThreshold);
	m_SerialThresholdSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::valueChanged), CCControlEventValueChanged);
	sprintf(name, "%d", Ext_SerialThreshold);
	m_SerialThresholdLabel = CCLabelTTF::create(name, "arial", 24);
	m_SerialThresholdLabel->setPosition(ccp(1500, 630));

	//视频亮度
	CCSprite* pVideoGain = CCSprite::create("SettingUI/liangduFont.png");
	pVideoGain->setPosition(ccp(600, 730));

	m_VideoGainSlider = CCControlSlider::create("SettingUI/gdtBg.png", "SettingUI/gdtQj.png", "SettingUI/gdtAn.png");
	m_VideoGainSlider->setPosition(ccp(1100, 730));
	m_VideoGainSlider->setMaximumValue(64);
	m_VideoGainSlider->setMinimumValue(1);
	m_VideoGainSlider->setValue(Ext_VideoGain);
	m_VideoGainSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::valueChanged), CCControlEventValueChanged);
	sprintf(name, "%d", Ext_VideoGain);
	m_VideoGainLabel = CCLabelTTF::create(name, "arial", 24);
	m_VideoGainLabel->setPosition(ccp(1500, 730));

	//相机位置
	CCSprite* pSetCameraLabel = CCSprite::create("SettingUI/xiangjiFont.png");
	pSetCameraLabel->setPosition(ccp(600, 230));

	CCMenuItemToggle* pSetCameraItem = CCMenuItemToggle::createWithTarget(
		this, menu_selector(SettingScene::SetCameraCallBack),
		CCMenuItemImage::create("SettingUI/zmqj.png", "SettingUI/zmqj.png"),
		CCMenuItemImage::create("SettingUI/cmqj.png", "SettingUI/cmqj.png"), NULL
		);
	pSetCameraItem->setPosition(ccp(1140, 230));
	pSetCameraItem->setSelectedIndex(Ext_IsFrontCamera?0:1);
	//情景模式
	CCSprite* pSetQingjing = CCSprite::create("SettingUI/qingjingmoshi.png");
	pSetQingjing->setPosition(ccp(600, 330));

	CCMenuItemToggle* pSetQingjingItem = CCMenuItemToggle::createWithTarget(
		this, menu_selector(SettingScene::SetQingjingCallBack),
		CCMenuItemImage::create("SettingUI/qingtian.png", "SettingUI/qingtian.png"),
		CCMenuItemImage::create("SettingUI/yintian.png", "SettingUI/yintian.png"),
		CCMenuItemImage::create("SettingUI/shinei.png", "SettingUI/shinei.png"), NULL
		);
	pSetQingjingItem->setPosition(ccp(1140, 330));
	if (Ext_VideoExposureTime == 3000)
	{
		pSetQingjingItem->setSelectedIndex(0);
	}
	else if (Ext_VideoExposureTime == 4000)
	{
		pSetQingjingItem->setSelectedIndex(1);
	}
	else if (Ext_VideoExposureTime == 15000)
	{
		pSetQingjingItem->setSelectedIndex(2);
	}

	CCMenuItemImage* pEnter = CCMenuItemImage::create("SettingUI/qdan1.png", "SettingUI/qdan2.png", this, menu_selector(SettingScene::menuCallBack));
	pEnter->setPosition(ccp(VISIBLEW / 2, 90));

	MyMenu* pMenu = MyMenu::create(pEnter, pSetCameraItem, pSetQingjingItem, NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(pSetting);
	this->addChild(m_VideoSleepSlider);
	this->addChild(m_SerialThresholdSlider);
	this->addChild(m_VideoGainSlider);
	this->addChild(m_VideoSleepLabel);
	this->addChild(m_SerialThresholdLabel);
	this->addChild(m_VideoGainLabel);
	this->addChild(pSetCameraLabel);
	this->addChild(pVidelSleep);
	this->addChild(pSerialThreshold);
	this->addChild(pVideoGain);
	this->addChild(pSetQingjing);
	this->addChild(pMenu);

	return true;
}
void SettingScene::valueChanged(CCObject* sender, CCControlEvent controlEvent)
{
	char value[32];
	if (sender == m_VideoSleepSlider)
	{
		Ext_VideoSleep = (int)m_VideoSleepSlider->getValue();
		sprintf(value, "%d", Ext_VideoSleep);
		m_VideoSleepLabel->setString(value);
	}
	else if (sender == m_SerialThresholdSlider)
	{
		Ext_SerialThreshold = (int)m_SerialThresholdSlider->getValue();
		sprintf(value, "%d", Ext_SerialThreshold);
		m_SerialThresholdLabel->setString(value);
	}
	else if (sender == m_VideoGainSlider)
	{
		Ext_VideoGain = (int)m_VideoGainSlider->getValue();
		sprintf(value, "%d", Ext_VideoGain);
		m_VideoGainLabel->setString(value);
	}
}
void SettingScene::SetQingjingCallBack(CCObject* obj)
{
	if (0 == ((CCMenuItemToggle*)obj)->getSelectedIndex())
	{
		Ext_VideoExposureTime = 3000.0;
	}
	else if (1 == ((CCMenuItemToggle*)obj)->getSelectedIndex())
	{
		Ext_VideoExposureTime = 4000.0;
	}
	else if (2 == ((CCMenuItemToggle*)obj)->getSelectedIndex())
	{
		Ext_VideoExposureTime = 15000.0;
	}
}
void SettingScene::onExit()
{
	CCLayer::onExit();

	Document::AllocatorType allocator;
	Value object(kObjectType);
	
	object.AddMember("VideoSleep", Ext_VideoSleep, allocator);
	object.AddMember("SerialThreshold", Ext_SerialThreshold, allocator);
	object.AddMember("VideoGain", Ext_VideoGain, allocator);
	object.AddMember("VideoExposureTime", Ext_VideoExposureTime, allocator);
	object.AddMember("ToPixels", Ext_ToPixels, allocator);

	saveValue(object, "Setting.json");
}
void SettingScene::menuCallBack(CCObject* obj)
{
	CCDirector::sharedDirector()->popScene();
}
void SettingScene::SetCameraCallBack(CCObject* obj)
{
	if (0 == ((CCMenuItemToggle*)obj)->getSelectedIndex())
	{
		Ext_IsFrontCamera = true;
	}
	else
	{
		Ext_IsFrontCamera = false;
	}
}