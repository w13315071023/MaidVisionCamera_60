#include "HelloWorldScene.h"
#include "PostureAnalysisScene.h"
#include "DataMager.h"
#include "SerialMager.h"
#include "SettingScene.h"
#include "GolfXIMager.h"
#include "MovieVideoLayer.h"
#include "RecordClass.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	printf("初始化HelloWorld\n");
    {//初始化成员变量
		m_curCueType = CUETYPE_TIEGAN;
		m_curGender = GENDER_MAN;
		m_isBeginButtonOn = false;
		
        m_pCueTtpeArr[0] = CCMenuItemImage::create(
										"HomeUI/yihaomu.png",
										"HomeUI/yihaomuon.png",
										"HomeUI/yihaomuon.png",
                                        this,
										menu_selector(HelloWorld::menuCueTtpeCallback));
        m_pCueTtpeArr[1] = CCMenuItemImage::create(
										"HomeUI/mugan.png",
										"HomeUI/muganon.png",
										"HomeUI/muganon.png",
                                        this,
										menu_selector(HelloWorld::menuCueTtpeCallback));
        m_pCueTtpeArr[2] = CCMenuItemImage::create(
										"HomeUI/tiegan.png",
										"HomeUI/tieganon.png",
										"HomeUI/tieganon.png",
                                        this,
										menu_selector(HelloWorld::menuCueTtpeCallback));
        m_pCueTtpeArr[3] = CCMenuItemImage::create(
										"HomeUI/waqigan.png",
										"HomeUI/waqiganon.png",
										"HomeUI/waqiganon.png",
                                        this,
										menu_selector(HelloWorld::menuCueTtpeCallback));

        m_pGenderArr[0] = CCMenuItemImage::create(
										"HomeUI/nan.png",
										"HomeUI/nanon.png",
										"HomeUI/nanon.png",
                                        this,
										menu_selector(HelloWorld::menuGenderCallback));
        m_pGenderArr[1] = CCMenuItemImage::create(
										"HomeUI/nv.png",
										"HomeUI/nvon.png",
										"HomeUI/nvon.png",
                                        this,
										menu_selector(HelloWorld::menuGenderCallback));
    }
    //创建控件
	CCSprite* pBackGround = CCSprite::create("HomeUI/Bg.png");

	CCMenuItemImage* pBeginItem = CCMenuItemImage::create(
									"HomeUI/jinruxitong1.png",
									"HomeUI/jinruxitong2.png",
									this,
									menu_selector(HelloWorld::menuCallback));
    CCSprite* pSprite1 = CCSprite::create("HomeUI/bianyuanguang.png");
    CCSprite* pSprite2 = CCSprite::create("HomeUI/bianyuanguang.png");
    //为控件设置位置
	pBackGround->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));

	pBeginItem->setPosition(ccp(VISIBLEW / 2 - 200, 130));

	m_pCueTtpeArr[0]->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 + 300));
	m_pCueTtpeArr[1]->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 + 170));
	m_pCueTtpeArr[2]->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 + 40));
	m_pCueTtpeArr[3]->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 - 90));
	m_pGenderArr[0]->setPosition(ccp(VISIBLEW / 2 + 350, VISIBLEH*0.59));
	m_pGenderArr[1]->setPosition(ccp(VISIBLEW / 2 + 350, VISIBLEH*0.42));

	pSprite1->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 + 40));
	m_pCueTtpeArr[2]->setEnabled(false);
	pSprite2->setPosition(ccp(VISIBLEW / 2 + 350, VISIBLEH*0.59));
	m_pGenderArr[0]->setEnabled(false);
    //设置控件标签
    pSprite1->setTag(1);
    pSprite2->setTag(2);
    m_pCueTtpeArr[0]->setTag(CUETYPE_YIHAOMU);
    m_pCueTtpeArr[1]->setTag(CUETYPE_MUGAN);
    m_pCueTtpeArr[2]->setTag(CUETYPE_TIEGAN);
    m_pCueTtpeArr[3]->setTag(CUETYPE_WAQIGAN);
    m_pGenderArr[0]->setTag(GENDER_MAN);
    m_pGenderArr[1]->setTag(GENDER_WOMAN);
    //将控件添加到渲染树
	this->addChild(pBackGround);
    this->addChild(pSprite1);
    this->addChild(pSprite2);
    //创建按钮层并添加按钮
	CCMenuItemImage* pSetting = CCMenuItemImage::create(
		"HomeUI/shezhi1.png",
		"HomeUI/shezhi2.png",
		this,
		menu_selector(HelloWorld::menuSettingCallback));
	pSetting->setPosition(ccp(VISIBLEW/2+200,130));
	CCMenu* pMenu = CCMenu::create(
								m_pCueTtpeArr[0],
								m_pCueTtpeArr[1],
								m_pCueTtpeArr[2],
								m_pCueTtpeArr[3],
								m_pGenderArr[0],
								m_pGenderArr[1],
								pBeginItem,
								pSetting,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	this->scheduleUpdate();
    return true;
}
//按钮的回调函数
void HelloWorld::menuCallback(CCObject* pSender)
{
	if (m_isBeginButtonOn)
	{
		return;
	}
	m_isBeginButtonOn = true;
	printf("进入系统\n");
	Ext_IsResetGG = true;
	DataMager::shareDataMager()->m_curCuetype = this->m_curCueType;
	DataMager::shareDataMager()->m_curGender = this->m_curGender;
	DataMager::shareDataMager()->SaveData();
	//转到姿势分析界面
	SerialMager::getInstence()->setThreshold(Ext_SerialThreshold);
	GolfXIMager::getInstence()->setClubType(140);

	if (MovieVideoLayer::m_Camera1)
	{
		MovieVideoLayer::m_Camera1->setExposureTime(Ext_VideoExposureTime);
		MovieVideoLayer::m_Camera1->setGain(Ext_VideoGain);
	}
	if (MovieVideoLayer::m_Camera2)
	{
		MovieVideoLayer::m_Camera2->setExposureTime(Ext_VideoExposureTime);
		MovieVideoLayer::m_Camera2->setGain(Ext_VideoGain);
	}

	printf("转到姿势分析界面\n");
	CCDirector::sharedDirector()->replaceScene(PostureAnalysisScene::CreateScene());
}
void HelloWorld::menuSettingCallback(CCObject* pSender)
{
	Ext_IsResetGG = true;
	CCDirector::sharedDirector()->pushScene(SettingScene::getScene());
}
//界面的触摸事件
void HelloWorld::menuCueTtpeCallback(CCObject* pSender)
{
	Ext_IsResetGG = true;
	//获取标识控件
	CCNode* pNode1 = this->getChildByTag(1);
	

	for (int i = 0; i < 4; i++)
	{
		m_pCueTtpeArr[i]->setEnabled(true);
		//判断有没有点击到球杆
		if (m_pCueTtpeArr[i] == pSender)
		{
			//记录选择的球杆
			m_curCueType = (CUETYPE)m_pCueTtpeArr[i]->getTag();
			instenceTarget = m_pCueTtpeArr[i]->getTag();
			//将标识控件移动到选择标签前
			pNode1->setPosition(ccp(
				m_pCueTtpeArr[i]->getPosition().x,
				m_pCueTtpeArr[i]->getPosition().y));
			m_pCueTtpeArr[i]->setEnabled(false);
		}
	}
}
void HelloWorld::menuGenderCallback(CCObject* pSender)
{
	Ext_IsResetGG = true;
	CCNode* pNode1 = this->getChildByTag(2);

    for(int i = 0;i < 2;i++)
    {
		m_pGenderArr[i]->setEnabled(true);
        //判断有没有点击到性别
        if(m_pGenderArr[i] == pSender)
        {
            //记录选择的性别
            m_curGender = (GENDER)m_pGenderArr[i]->getTag();
            //将标识控件移动到选择标签前
			pNode1->setPosition(ccp(
                m_pGenderArr[i]->getPosition().x,
                m_pGenderArr[i]->getPosition().y));
			m_pGenderArr[i]->setEnabled(false);
        }
    }
}
void HelloWorld::update(float dt)
{
	if (!SerialMager::getInstence()->getComPort())
	{
		CCMessageBox("请链接小盒子","警告！");
		CCDirector::sharedDirector()->end();
	}
}