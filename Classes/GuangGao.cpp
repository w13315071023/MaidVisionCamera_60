#include "GuangGao.h"
#include "ResetGGMager.h"

GuangGao::GuangGao(void)
{
}
GuangGao::~GuangGao(void)
{
}
CCScene* GuangGao::getScene()
{
	CCScene* scene = CCScene::create();
	GuangGao* layer = GuangGao::create();

	scene->addChild(layer);
	return scene;
}
bool GuangGao::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_Time = 0;
	m_pImage = CCSprite::create("GG.png");
	m_pImage->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	this->addChild(m_pImage);

	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);
	this->scheduleUpdate();
	return true;
}
void GuangGao::update(float dt)
{
	m_Time++;
	m_Time = m_Time % 3000;
	switch (m_Time)
	{
	case 1:
	{

	}
	break;
	case 1000:
	{

	}
	break;
	case 2000:
	{

	}
	break;
	}
}
bool GuangGao::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	ResetGGMager::resume();
	CCDirector::sharedDirector()->popScene();
	return false;
}