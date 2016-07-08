#include "UINode.h"


UINode::UINode(void)
{
}


UINode::~UINode(void)
{
}
bool UINode::init()
{
	if (!CCSprite::initWithFile("SettingUI/bxszBg.png"))
	{
		return false;
	}
	CCSize Size = this->getContentSize();
	m_pLabelTTF = CCLabelTTF::create("140","Arial",32);
	m_pLabelTTF->setPosition(ccp(Size.width / 2, Size.height/2));
	this->addChild(m_pLabelTTF);

	CCMenuItemImage* pZuo = CCMenuItemImage::create(
		"SettingUI/jxan.png",
		"SettingUI/jxan.png",
		this, menu_selector(UINode::menuCallBackZuo));
	pZuo->setPosition(ccp(Size.width / 2-160, Size.height / 2));

	CCMenuItemImage* pYou = CCMenuItemImage::create(
		"SettingUI/jdan.png",
		"SettingUI/jdan.png",
		this, menu_selector(UINode::menuCallBackYou));
	pYou->setPosition(ccp(Size.width / 2+160, Size.height / 2));

	CCMenu* pMenu = CCMenu::create(pZuo, pYou,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	
	this->scheduleUpdate();
	return true;
}
void UINode::update(float dt)
{
	char name[8];
	sprintf(name, "%d", instenceTarget);
	m_pLabelTTF->setString(name);
}
void UINode::menuCallBackZuo(CCObject* pSender)
{
	instenceTarget -= 10;
}
void UINode::menuCallBackYou(CCObject* pSender)
{
	instenceTarget += 10;
}