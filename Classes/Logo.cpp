#include "Logo.h"
#include "LodingScene.h"

CCScene* Logo::getScene()
{
	CCScene* scene = CCScene::create();
	CCLayer* layer = Logo::create();
	scene->addChild(layer);

	return scene;
}
Logo::Logo(void)
{
}
Logo::~Logo(void)
{
}
bool Logo::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSprite* pSprite = CCSprite::create("HomeUI/LOGO.png");
	pSprite->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	this->addChild(pSprite);

	this->scheduleOnce(schedule_selector(Logo::update),0.5);
	return true;
}
void Logo::update(float dt)
{
	CCScene* pLodingScene = LodingScene::getLodingScene();
	CCDirector::sharedDirector()->replaceScene(pLodingScene);
}