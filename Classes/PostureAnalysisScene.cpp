#include "PostureAnalysisScene.h"
#include "GolfXIMager.h"
#include "DataMager.h"

DrawingLayer* PostureAnalysisScene::m_pDrawingLayer = NULL;
MovieVideoLayer* PostureAnalysisScene::m_pFrontMovieVideoLayer = NULL;
MovieVideoLayer* PostureAnalysisScene::m_pSideMovieVideoLayer = NULL;
DemoVideoLayer* PostureAnalysisScene::m_pFrontDemoVideoLayer = NULL;
DemoVideoLayer* PostureAnalysisScene::m_pSideDemoVideoLayer = NULL;
bool PostureAnalysisScene::m_bIsPlayVideo = false;
bool PostureAnalysisScene::m_bIsTurnCamera = true;
PostureAnalysisScene::PostureAnalysisScene(void)
{
}
PostureAnalysisScene::~PostureAnalysisScene(void)
{
	SerialMager::getInstence()->unLoadInstence();
	m_bIsPlayVideo = false;
	if (m_pFrontDemoVideoLayer)
	{
		m_pFrontDemoVideoLayer->ReSetVideo();
	}
	m_pFrontMovieVideoLayer->ReSetVideo();
	if (Ext_cameraNum == 2)
	{
		if (m_pFrontDemoVideoLayer)
		{
			m_pFrontDemoVideoLayer->ReSetVideo();
		}
		if (m_pSideDemoVideoLayer)
		{
			m_pSideDemoVideoLayer->ReSetVideo();
		}
		m_pFrontMovieVideoLayer->ReSetVideo();
		m_pSideMovieVideoLayer->ReSetVideo();
	}
}
//场景的创建函数
CCScene* PostureAnalysisScene::CreateScene()
{
    //创建一个场景
    CCScene* scene = CCScene::create();
    //创建层
    PostureAnalysisScene* pLayer1 = PostureAnalysisScene::create();
	m_pDrawingLayer = DrawingLayer::create();
    //将层加载到场景中  并返回
    scene->addChild(pLayer1,1,98);
	scene->addChild(m_pDrawingLayer, 2);

    return scene;
}
//初始化函数
bool PostureAnalysisScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
	printf("初始化PostureAnalysisScene\n");
	m_curMenuTag = MENUTAG_FourView;
	m_curMsg = 0;
	m_curSingle = 1.5f / 60.0f;
	m_bIsPlayVideo = false;
	m_bIsStepPlay = false;
	m_bIsVisibleMenu = true;
	m_bSetMode = true;
	m_pUpMoveBy = CCMoveBy::create(0.3,ccp(0,100));
	m_pUpMoveBy->retain();
	m_pDownMoveBy = CCMoveBy::create(0.3, ccp(0, -100));
	m_pDownMoveBy->retain();

	CCSprite* beijing1 = CCSprite::create("VideoUI/beijing1.png");
	beijing1->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	this->addChild(beijing1);
	
	if (!m_pFrontDemoVideoLayer)
	{
		m_pFrontDemoVideoLayer = DemoVideoLayer::create(FRONT);
		m_pFrontDemoVideoLayer->retain();
	}
	if (!m_pFrontMovieVideoLayer)
	{
		m_pFrontMovieVideoLayer = MovieVideoLayer::create(FRONT);
	}
	this->addChild(m_pFrontDemoVideoLayer);
	this->addChild(m_pFrontMovieVideoLayer);
	if (Ext_cameraNum != 0)
	{
		SerialMager::getInstence()->setDelegate1(m_pFrontMovieVideoLayer);
	}
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		"VideoUI/fanhuizhuye1.png",
		"VideoUI/fanhuizhuye2.png",
		this,
		menu_selector(PostureAnalysisScene::menuCallback));
	pBackItem->setPosition(ccp(116, 1000));
	pBackItem->setTag(MENUTAG_Back);

	//播放控制按钮
	CCSprite* beijing5 = CCSprite::create("VideoUI/beijing5.png");
	beijing5->setPosition(ccp(116, 346));
	this->addChild(beijing5);
	m_pREWItem = CCMenuItemImage::create(
		"VideoUI/shangyizhen1.png",
		"VideoUI/shangyizhen2.png",
		this,
		menu_selector(PostureAnalysisScene::CallbackREW));
	m_pFFItem = CCMenuItemImage::create(
		"VideoUI/xiayizhen1.png",
		"VideoUI/xiayizhen2.png",
		this,
		menu_selector(PostureAnalysisScene::CallbackFF));
	m_pRePlayItem = CCMenuItemImage::create(
		"VideoUI/chongbo1.png",
		"VideoUI/chongbo2.png",
		this,
		menu_selector(PostureAnalysisScene::CallbackRePlay));
	m_pPreview = CCMenuItemImage::create(
		"VideoUI/yulan1.png",
		"VideoUI/yulan2.png",
		this,
		menu_selector(PostureAnalysisScene::CallbackPreview));
	m_pSpeedItem = CCMenuItemToggle::createWithTarget(
		this, menu_selector(PostureAnalysisScene::CallbackSpeed),
		CCMenuItemImage::create("VideoUI/sudu1.png", "VideoUI/sudu2.png"),
		CCMenuItemImage::create("VideoUI/sudu3.png", "VideoUI/sudu4.png"),
		CCMenuItemImage::create("VideoUI/sudu5.png", "VideoUI/sudu6.png"),
		NULL);
	m_pSpeedItem->setTag(98);

	m_pPauseItemToggle = CCMenuItemToggle::createWithTarget(
		this, menu_selector(PostureAnalysisScene::CallbackPause),
		CCMenuItemImage::create("VideoUI/bofang1.png", "VideoUI/bofang2.png"),
		CCMenuItemImage::create("VideoUI/zhanting1.png", "VideoUI/zhanting2.png"),
		NULL);
	m_pPauseItemToggle->setTag(99);

	m_pREWItem->setPosition(ccp(116, 346+150));
	m_pFFItem->setPosition(ccp(116, 346+90));
	m_pPauseItemToggle->setPosition(ccp(116, 346+30));
	m_pRePlayItem->setPosition(ccp(116, 346-30));
	m_pSpeedItem->setPosition(ccp(116, 346-90));
	m_pPreview->setPosition(ccp(116, 346-150));

	CCSprite* beijing4 = CCSprite::create("VideoUI/beijing4.png");
	beijing4->setPosition(ccp(116, 80));
	this->addChild(beijing4);
	m_pDanjian = CCMenuItemImage::create(
		"VideoUI/danjian1.png",
		"VideoUI/danjian2.png",
		"VideoUI/danjian2.png",
		this,
		menu_selector(PostureAnalysisScene::CallbackSetMode));
	m_pXunhuan = CCMenuItemImage::create(
		"VideoUI/xunhuanjian1.png",
		"VideoUI/xunhuanjian2.png",
		"VideoUI/xunhuanjian2.png",
		this,
		menu_selector(PostureAnalysisScene::CallbackSetMode));
	m_pXunhuan->setEnabled(false);
	m_pDanjian->setPosition(ccp(116-38,80));
	m_pXunhuan->setPosition(ccp(116 + 38, 80));
	
	m_pMenu = MyMenu::create(
		pBackItem,
		m_pREWItem,
		m_pFFItem,
		m_pRePlayItem,
		m_pSpeedItem,
		m_pPauseItemToggle,
		m_pPreview,
		m_pDanjian,
		m_pXunhuan,
		NULL);
	m_pMenu->setPosition(CCPointZero);
	this->addChild(m_pMenu, 1);

	m_pReadyLabel = CCSprite::create("VideoUI/ready.png");
	m_pReadyLabel->setPosition(ccp(1800, 900));
	m_pReadyLabel->setVisible(false);
	this->addChild(m_pReadyLabel);
	m_pReadyImage = CCSprite::create("VideoUI/xinhao.png");
	m_pReadyImage->setPosition(ccp(1800, 1000));
	m_pReadyImage->setVisible(false);
	this->addChild(m_pReadyImage);

	if (Ext_cameraNum == 2)
	{
		if (!m_pSideDemoVideoLayer)
		{
			m_pSideDemoVideoLayer = DemoVideoLayer::create(SIDE);
			m_pSideDemoVideoLayer->retain();
		}

		if (Ext_IsFrontCamera == m_bIsTurnCamera)
		{
			if (!m_pSideMovieVideoLayer)
			{
				m_pSideMovieVideoLayer = MovieVideoLayer::create(SIDE);
			}
			this->addChild(m_pSideMovieVideoLayer);
		}
		else
		{
			if (!m_pSideMovieVideoLayer)
			{
				m_pSideMovieVideoLayer = MovieVideoLayer::create(SIDE);
			}
			this->addChild(m_pSideMovieVideoLayer);
			swap(m_pSideMovieVideoLayer,m_pFrontMovieVideoLayer);
			m_bIsTurnCamera = Ext_IsFrontCamera;
		}
		SerialMager::getInstence()->setDelegate2(m_pSideMovieVideoLayer);
		//创建视图按钮的菜单项
		CCSprite* beijing3 = CCSprite::create("VideoUI/beijing3.png");
		beijing3->setPosition(ccp(116, 700));
		this->addChild(beijing3);

		m_pFourViewItem = CCMenuItemImage::create(
			"VideoUI/sishitu1.png",
			"VideoUI/sishitu2.png",
			this,
			menu_selector(PostureAnalysisScene::menuCallback));
		m_pFrontViewItem = CCMenuItemToggle::createWithTarget(
			this, menu_selector(PostureAnalysisScene::menuCallback),
			CCMenuItemImage::create("VideoUI/zhengshitu1.png", "VideoUI/zhengshitu2.png"),
			CCMenuItemImage::create("VideoUI/zhengduitu1.png", "VideoUI/zhengduitu2.png"),
			NULL);
		m_pSideViewItem = CCMenuItemToggle::createWithTarget(
			this, menu_selector(PostureAnalysisScene::menuCallback),
			CCMenuItemImage::create("VideoUI/ceshitu1.png", "VideoUI/ceshitu2.png"),
			CCMenuItemImage::create("VideoUI/ceduitu1.png", "VideoUI/ceduitu2.png"),
			NULL);
		m_pFrontAndSideViewItem = CCMenuItemImage::create(
			"VideoUI/zhengcetu1.png",
			"VideoUI/zhengcetu2.png",
			this,
			menu_selector(PostureAnalysisScene::menuCallback));
		
		//修改控件的位置
		m_pFourViewItem->setPosition(ccp(116, 700+90));
		m_pFrontViewItem->setPosition(ccp(116, 700+30));
		m_pSideViewItem->setPosition(ccp(116, 700-30));
		m_pFrontAndSideViewItem->setPosition(ccp(116, 700-90));
		if (Ext_IsTurnCamera == true)
		{
			m_pFrontMovieVideoLayer->setRotation(90);
			m_pSideMovieVideoLayer->setRotation(90);
			m_pFrontDemoVideoLayer->setRotation(90);
			m_pSideDemoVideoLayer->setRotation(90);

			m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 240, VISIBLEH / 2 + 320));
			m_pSideDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 240, VISIBLEH / 2 - 320));
			m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 240, VISIBLEH / 2 + 320));
			m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 240, VISIBLEH / 2 - 320));
		}
		else
		{
			m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2 + 270));
			m_pSideDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2 - 270+5));
			m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2 + 270));
			m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2 - 270+5));
		}
		m_pFrontDemoVideoLayer->setScale(1.125);
		m_pSideDemoVideoLayer->setScale(1.125);
		m_pFrontMovieVideoLayer->setScale(1.125);
		m_pSideMovieVideoLayer->setScale(1.125);

		m_pFrontMovieVideoLayer->setVisible(true);
		m_pSideMovieVideoLayer->setVisible(true);
		//设置视图按钮的标签
		m_pFourViewItem->setTag(MENUTAG_FourView);
		m_pFrontViewItem->setTag(MENUTAG_FrontView);
		m_pSideViewItem->setTag(MENUTAG_SideView);
		m_pFrontAndSideViewItem->setTag(MENUTAG_FrontAndSide);
		//控件添加到渲染树
		this->addChild(m_pSideDemoVideoLayer);
		m_pMenu->addChild(m_pFourViewItem);
		m_pMenu->addChild(m_pFrontViewItem);
		m_pMenu->addChild(m_pSideViewItem);
		m_pMenu->addChild(m_pFrontAndSideViewItem);
	}
	else
	{
		//创建视图按钮的菜单项
		CCSprite* beijing6 = CCSprite::create("VideoUI/beijing6.png");
		beijing6->setPosition(ccp(116, 700));
		this->addChild(beijing6);

		m_pFrontViewItem2 = CCMenuItemImage::create(
			"VideoUI/zhengshitu1.png",
			"VideoUI/zhengshitu2.png",
			this,
			menu_selector(PostureAnalysisScene::menuCallback));
		m_pFrontDemoViewItem = CCMenuItemImage::create(
			"VideoUI/zhengduitu1.png",
			"VideoUI/zhengduitu2.png",
			this,
			menu_selector(PostureAnalysisScene::menuCallback));

		//修改控件的位置
		m_pFrontViewItem2->setPosition(ccp(116, 700-30));
		m_pFrontDemoViewItem->setPosition(ccp(116, 700+30));

		if (!Ext_IsFrontCamera)
		{
			if (!m_pSideDemoVideoLayer)
			{
				m_pSideDemoVideoLayer = DemoVideoLayer::create(SIDE);
				m_pSideDemoVideoLayer->retain();
			}
			this->addChild(m_pSideDemoVideoLayer);
			swap(m_pSideDemoVideoLayer, m_pFrontDemoVideoLayer);
			m_pFrontDemoVideoLayer->setVisible(true);
			m_pSideDemoVideoLayer->setVisible(false);
			m_bIsTurnCamera = Ext_IsFrontCamera;
		}
		m_pFrontMovieVideoLayer->setScale(1.125);
		m_pFrontDemoVideoLayer->setScale(1.125);

		if (Ext_IsTurnCamera == true)
		{
			m_pFrontMovieVideoLayer->setRotation(90);
			m_pFrontDemoVideoLayer->setRotation(90);
			m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 336, VISIBLEH / 2));
			m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 336, VISIBLEH / 2));
		}
		else
		{
			m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2));
			m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2));
		}
		m_pFrontViewItem2->setTag(MENUTAG_FrontView);
		m_pFrontDemoViewItem->setTag(MENUTAG_FrontDemoView);
		
		m_pMenu->addChild(m_pFrontViewItem2);
		m_pMenu->addChild(m_pFrontDemoViewItem);
	}

	if (Ext_IsGolfXI == true)
	{
		CCMenuItemImage* pDataAnalysisItem = CCMenuItemImage::create(
			"VideoUI/shujufenxi1.png",
			"VideoUI/shujufenxi2.png",
			this,
			menu_selector(PostureAnalysisScene::menuCallback));
		pDataAnalysisItem->setPosition(ccp(116, 915));
		pDataAnalysisItem->setTag(MENUTAG_DataAnalysis);
		m_pMenu->addChild(pDataAnalysisItem);
	}
	//else
	//{
	//	CCMenuItemImage* pDataAnalysisItem = CCMenuItemImage::create(
	//		"VideoUI/shujufenxi1.png",
	//		"VideoUI/shujufenxi2.png",
	//		this,
	//		menu_selector(PostureAnalysisScene::menuCallback));
	//	pDataAnalysisItem->setPosition(ccp(116, 915));
	//	pDataAnalysisItem->setTag(MENUTAG_DataAnalysis);
	//	m_pMenu->addChild(pDataAnalysisItem);
	//}
	
	this->schedule(schedule_selector(PostureAnalysisScene::Update), m_curSingle);
	Ext_IsThreadOn = true;

    return true;
}
void PostureAnalysisScene::menuCallback(CCObject* pSender)
{
	Ext_IsResetGG = true;
    //获取视图按钮的标签
    CCNode* pMenuNode = (CCNode*)pSender;
    MENUTAG MenuTag = (MENUTAG)pMenuNode->getTag();
    {//禁止重复点击相同按钮
		if (m_curMenuTag == MenuTag && 
			MenuTag != MENUTAG_FrontView &&
			MenuTag != MENUTAG_SideView)
            return;
        m_curMenuTag = MenuTag;
    }
    //根据获取的视图按钮标签做出响应
    switch(m_curMenuTag)
    {
    case MENUTAG_FourView:
        {
			((CCMenuItemToggle*)m_pMenu->getChildByTag(MENUTAG_FrontView))->setSelectedIndex(0);
			((CCMenuItemToggle*)m_pMenu->getChildByTag(MENUTAG_SideView))->setSelectedIndex(0);
            //控制界面显示
			m_pFrontDemoVideoLayer->setVisible(true);
			m_pSideDemoVideoLayer->setVisible(true);
            m_pFrontMovieVideoLayer->setVisible(true);
            m_pSideMovieVideoLayer->setVisible(true);

			m_pFrontDemoVideoLayer->setScale(1.125);
			m_pSideDemoVideoLayer->setScale(1.125);
			m_pFrontMovieVideoLayer->setScale(1.125);
			m_pSideMovieVideoLayer->setScale(1.125);
			if (Ext_IsTurnCamera == true)
			{
				m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 240, VISIBLEH / 2 + 320));
				m_pSideDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 240, VISIBLEH / 2 - 320));
				m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 240, VISIBLEH / 2 + 320));
				m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 240, VISIBLEH / 2 - 320));
			}
			else
			{
				m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2 + 270));
				m_pSideDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2 - 270+5));
				m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2 + 270));
				m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2 - 270+5));
			}

			m_pDrawingLayer->ClsAll();
        }
        break;
    case MENUTAG_FrontView:
        {
			if (Ext_cameraNum == 2)
			{
				((CCMenuItemToggle*)m_pMenu->getChildByTag(MENUTAG_SideView))->setSelectedIndex(0);
				int index = ((CCMenuItemToggle*)pMenuNode)->getSelectedIndex();
				//控制界面显示
				if (index == 1)
				{
					m_pFrontDemoVideoLayer->setVisible(false);
					m_pSideDemoVideoLayer->setVisible(false);
					m_pFrontMovieVideoLayer->setVisible(true);
					m_pSideMovieVideoLayer->setVisible(false);

					m_pFrontMovieVideoLayer->setScale(2);

					m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));

					m_pDrawingLayer->ClsAll();
				}
				else
				{
					m_pFrontDemoVideoLayer->setVisible(true);
					m_pSideDemoVideoLayer->setVisible(false);
					m_pFrontMovieVideoLayer->setVisible(true);
					m_pSideMovieVideoLayer->setVisible(false);

					m_pFrontDemoVideoLayer->setScale(1.125);
					m_pFrontMovieVideoLayer->setScale(1.125);

					if (Ext_IsTurnCamera == true)
					{
						m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 336, VISIBLEH / 2));
						m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 336, VISIBLEH / 2));
					}
					else
					{
						m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2));
						m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2));
					}
					m_pDrawingLayer->ClsAll();
				}
			}
			else
			{
				m_pFrontDemoVideoLayer->setVisible(false);
				m_pFrontMovieVideoLayer->setVisible(true);

				m_pFrontMovieVideoLayer->setScale(2);
				m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));

				m_pDrawingLayer->ClsAll();
			}
        }
        break;
    case MENUTAG_SideView:
        {
			((CCMenuItemToggle*)m_pMenu->getChildByTag(MENUTAG_FrontView))->setSelectedIndex(0);
			int index = ((CCMenuItemToggle*)pMenuNode)->getSelectedIndex();
			//控制界面显示
			if (index == 1)
			{
				m_pFrontDemoVideoLayer->setVisible(false);
				m_pSideDemoVideoLayer->setVisible(false);
				m_pFrontMovieVideoLayer->setVisible(false);
				m_pSideMovieVideoLayer->setVisible(true);

				m_pSideMovieVideoLayer->setScale(2);

				m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2 ));

				m_pDrawingLayer->ClsAll();
			}
			else
			{
				m_pFrontDemoVideoLayer->setVisible(false);
				m_pSideDemoVideoLayer->setVisible(true);
				m_pFrontMovieVideoLayer->setVisible(false);
				m_pSideMovieVideoLayer->setVisible(true);
				if (Ext_IsTurnCamera == true)
				{
					m_pSideDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 336, VISIBLEH / 2));
					m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 336, VISIBLEH / 2));
					m_pSideDemoVideoLayer->setScale(1.4);
					m_pSideMovieVideoLayer->setScale(1.4);
				}
				else
				{
					m_pSideDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2));
					m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2));
					m_pSideDemoVideoLayer->setScale(1.125);
					m_pSideMovieVideoLayer->setScale(1.125);
				}
				m_pDrawingLayer->ClsAll();
			}
        }
        break;
    case MENUTAG_FrontAndSide:
        {
			((CCMenuItemToggle*)m_pMenu->getChildByTag(MENUTAG_FrontView))->setSelectedIndex(0);
			((CCMenuItemToggle*)m_pMenu->getChildByTag(MENUTAG_SideView))->setSelectedIndex(0);
            //控制界面显示
			m_pFrontDemoVideoLayer->setVisible(false);
			m_pSideDemoVideoLayer->setVisible(false);
            m_pFrontMovieVideoLayer->setVisible(true);
            m_pSideMovieVideoLayer->setVisible(true);

			if (Ext_IsTurnCamera == true)
			{
				m_pFrontMovieVideoLayer->setScale(1.4);
				m_pSideMovieVideoLayer->setScale(1.4);
				m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 336, VISIBLEH / 2));
				m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 + 336, VISIBLEH / 2));
			}
			else
			{
				m_pFrontMovieVideoLayer->setScale(1.125);
				m_pSideMovieVideoLayer->setScale(1.125);
				m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2));
				m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2));
			}

			m_pDrawingLayer->ClsAll();
        }
        break;
	case MENUTAG_FrontDemoView:
		{
			m_pFrontDemoVideoLayer->setVisible(true);
			m_pFrontMovieVideoLayer->setVisible(true);

			if (Ext_IsTurnCamera == true)
			{
				m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 336, VISIBLEH / 2));
				m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 336, VISIBLEH / 2));
				m_pFrontDemoVideoLayer->setScale(1.4);
				m_pFrontMovieVideoLayer->setScale(1.4);
			}
			else
			{
				m_pFrontDemoVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2));
				m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2));
				m_pFrontDemoVideoLayer->setScale(1.125);
				m_pFrontMovieVideoLayer->setScale(1.125);
			}
			m_pDrawingLayer->ClsAll();
		}
		break;
	case MENUTAG_DataAnalysis:
		{
			Ext_IsThreadOn = false;
			this->unschedule(schedule_selector(PostureAnalysisScene::Update));
			CCDirector::sharedDirector()->replaceScene(DataAnalysisScene::CreateScene());
		}
        break;
    case MENUTAG_Back:
        {
            //返回到主界面
			Ext_IsThreadOn = false;
			this->unschedule(schedule_selector(PostureAnalysisScene::Update));
			m_pFrontDemoVideoLayer->release();
			m_pFrontDemoVideoLayer = NULL;
			if (m_pSideDemoVideoLayer)
			{
				m_pSideDemoVideoLayer->release();
				m_pSideDemoVideoLayer = NULL;
			}
            CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
        }
        break;
    }
}
void PostureAnalysisScene::Update(float dt)
{
	if (!SerialMager::getInstence()->getComPort())
	{
		CCMessageBox("请链接小盒子", "警告！");
		CCDirector::sharedDirector()->end();
	}
	if (Ext_IsGolfXI)
	{
		GolfXIMager::getInstence()->DeviceUpdate();

		if (GolfXIMager::m_IsHitBall == true)
		{
			DataMager::shareDataMager()->PushData(
				GolfXIMager::getInstence()->m_curBackSpin,
				GolfXIMager::getInstence()->m_curSideSpin,
				GolfXIMager::getInstence()->m_curVAngle,
				GolfXIMager::getInstence()->m_curHAngle,
				GolfXIMager::getInstence()->m_curBallSpeed,
				0
				);
			DataMager::shareDataMager()->SaveData();
			GolfXIMager::m_IsHitBall = false;
		}
	}
	SerialMager::getInstence()->SeriaUpdate();
	if (m_bIsPlayVideo == true)
	{
		if (!m_pFrontDemoVideoLayer->m_IsPlayOver)
		{
			m_pFrontDemoVideoLayer->ShowDemoVideo();
		}
		if (Ext_cameraNum == 2 && !m_pSideDemoVideoLayer->m_IsPlayOver)
		{
			m_pSideDemoVideoLayer->ShowDemoVideo();
		}
		for (size_t i = 0; i < 2; i++)
		{
			if (Ext_cameraNum &&!m_pFrontMovieVideoLayer->m_IsPlayOver)
			{
				m_pFrontMovieVideoLayer->ShowVideo();
				m_pFrontMovieVideoLayer->TransData();
			}
			if (Ext_cameraNum == 2 && !m_pSideMovieVideoLayer->m_IsPlayOver)
			{
				m_pSideMovieVideoLayer->ShowVideo();
				m_pSideMovieVideoLayer->TransData();
			}
		}
		if (m_pFrontDemoVideoLayer->m_IsPlayOver &&
			(Ext_cameraNum != 2 || m_pSideDemoVideoLayer->m_IsPlayOver) &&
			(!Ext_cameraNum || m_pFrontMovieVideoLayer->m_IsPlayOver))
		{
			if (m_bSetMode)
			{
				this->CallbackRePlay(m_pRePlayItem);
			}
			else
			{
				m_pFrontDemoVideoLayer->ReSetDemoVideo();
				m_pFrontMovieVideoLayer->ReSetVideo();
				if (Ext_cameraNum == 2)
				{
					m_pSideDemoVideoLayer->ReSetDemoVideo();
					m_pSideMovieVideoLayer->ReSetVideo();
				}
				m_bIsPlayVideo = false;
				m_bIsStepPlay = false;
				Ext_IsThreadOn = true;
				Ext_IsRecordBegin = false;
				CCMenuItemToggle* pToggle = (CCMenuItemToggle*)(m_pMenu->getChildByTag(99));
				pToggle->setSelectedIndex(0);
				this->schedule(schedule_selector(PostureAnalysisScene::Update), 1.5f / 60.0f);
			}
		}
	}
	else
	{
		if (Ext_cameraNum)
		{
			m_pFrontMovieVideoLayer->update(dt);
		}
		if (Ext_cameraNum == 2)
		{
			m_pSideMovieVideoLayer->update(dt);
		}
	}
	if (this->m_curMsg != SerialMager::getInstence()->m_curMsg)
	{
		m_curMsg = SerialMager::getInstence()->m_curMsg;
		if (m_curMsg == 2)
		{
			this->CallbackPreview(m_pPreview);
			m_pReadyLabel->setVisible(true);
			m_pReadyImage->setVisible(true);
		}
		else
		{
			m_pReadyLabel->setVisible(false);
			m_pReadyImage->setVisible(false);
		}
	}
}
void PostureAnalysisScene::CallbackREW(CCObject* pSender)
{
	Ext_IsResetGG = true;
	if (m_bIsPlayVideo == false)
	{
		return;
	}
	if (m_bIsStepPlay == false)
	{
		CCMenuItemToggle* pToggle = (CCMenuItemToggle*)(m_pMenu->getChildByTag(99));
		pToggle->setSelectedIndex(0);
		this->CallbackPause(pToggle);
	}
	for (size_t i = 0; i < 2; i++)
	{
		if (!m_pFrontDemoVideoLayer->m_IsPlayOver&&m_pFrontDemoVideoLayer->m_VideoIter != m_pFrontDemoVideoLayer->m_VideoList.begin())
		{
			m_pFrontDemoVideoLayer->m_VideoIter--;
		}
		if (Ext_cameraNum == 2 && !m_pSideDemoVideoLayer->m_IsPlayOver&&m_pSideDemoVideoLayer->m_VideoIter != m_pSideDemoVideoLayer->m_VideoList.begin())
		{
			m_pSideDemoVideoLayer->m_VideoIter--;
		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (Ext_cameraNum &&!m_pFrontMovieVideoLayer->m_IsPlayOver&&m_pFrontMovieVideoLayer->m_VideoIter != m_pFrontMovieVideoLayer->m_VideoList.begin())
		{
			m_pFrontMovieVideoLayer->m_VideoIter--;
		}
		if (Ext_cameraNum == 2 && !m_pSideMovieVideoLayer->m_IsPlayOver&&m_pSideMovieVideoLayer->m_VideoIter != m_pSideMovieVideoLayer->m_VideoList.begin())
		{
			m_pSideMovieVideoLayer->m_VideoIter--;
		}
	}
	this->Update(0);
}
void PostureAnalysisScene::CallbackFF(CCObject* pSender)
{
	Ext_IsResetGG = true;
	if (m_bIsPlayVideo == false)
	{
		return;
	}
	if (m_bIsStepPlay == false)
	{
		CCMenuItemToggle* pToggle = (CCMenuItemToggle*)(m_pMenu->getChildByTag(99));
		pToggle->setSelectedIndex(0);
		this->CallbackPause(pToggle);
	}
	this->Update(0);
}
void PostureAnalysisScene::CallbackRePlay(CCObject* pSender)
{
	Ext_IsResetGG = true;
	if (m_bIsPlayVideo == true)
	{
		m_bIsPlayVideo = false;

		m_pFrontDemoVideoLayer->ReSetDemoVideo();
		m_pFrontMovieVideoLayer->ReSetVideo();
		if (Ext_cameraNum == 2)
		{
			m_pSideDemoVideoLayer->ReSetDemoVideo();
			m_pSideMovieVideoLayer->ReSetVideo();
		}
		if (m_bIsStepPlay == true)
		{
			this->schedule(schedule_selector(PostureAnalysisScene::Update), m_curSingle);
			m_bIsStepPlay = false;
		}
	}
	CCMenuItemToggle* pToggle = (CCMenuItemToggle*)(m_pMenu->getChildByTag(99));
	pToggle->setSelectedIndex(1);
	this->CallbackPause(pToggle);
}
void PostureAnalysisScene::CallbackSpeed(CCObject* pSender)
{
	Ext_IsResetGG = true;
	CCMenuItemToggle* pToggle = (CCMenuItemToggle*)pSender;
	if (pToggle->getSelectedIndex() == 0)
	{
		m_curSingle = 2.0f / 60.0f;
	}
	if (pToggle->getSelectedIndex() == 1)
	{
		m_curSingle = 5.0f / 60.0f;
	}
	if (pToggle->getSelectedIndex() == 2)
	{
		m_curSingle = 8.0f / 60.0f;
	}
	if (m_bIsPlayVideo && !m_bIsStepPlay)
	{
		this->schedule(schedule_selector(PostureAnalysisScene::Update), m_curSingle);
	}
}
void PostureAnalysisScene::CallbackPause(CCObject* pSender)
{
	Ext_IsResetGG = true;
	CCMenuItemToggle* pToggle = (CCMenuItemToggle*)pSender;
	if (pToggle->getSelectedIndex() == 1)
	{
		if (m_bIsStepPlay == true && (
			!m_pFrontDemoVideoLayer->m_IsPlayOver ||
			(Ext_cameraNum != 2 || !m_pSideDemoVideoLayer->m_IsPlayOver) ||
			(!Ext_cameraNum || !m_pFrontMovieVideoLayer->m_IsPlayOver)))
		{
			this->schedule(schedule_selector(PostureAnalysisScene::Update), m_curSingle);
			m_bIsStepPlay = false;
		}
		else
		{
			m_pFrontDemoVideoLayer->ReSetDemoVideo();
			m_pFrontMovieVideoLayer->ReSetVideo();
			m_pFrontDemoVideoLayer->m_IsPlayOver = false;
			m_pFrontMovieVideoLayer->m_IsPlayOver = false;
			if (Ext_cameraNum == 2)
			{
				m_pSideDemoVideoLayer->m_IsPlayOver = false;
				m_pSideMovieVideoLayer->m_IsPlayOver = false;
				m_pSideDemoVideoLayer->ReSetDemoVideo();
				m_pSideMovieVideoLayer->ReSetVideo();
			}
			m_bIsPlayVideo = true;
			this->schedule(schedule_selector(PostureAnalysisScene::Update), m_curSingle);
		}
	}
	else
	{
		m_bIsStepPlay = true;
		this->unschedule(schedule_selector(PostureAnalysisScene::Update));
	}
}
void PostureAnalysisScene::CallbackPreview(CCObject* pSender)
{
	m_pFrontDemoVideoLayer->ReSetDemoVideo();
	m_pFrontMovieVideoLayer->ReSetVideo();
	if (Ext_cameraNum == 2)
	{
		m_pSideDemoVideoLayer->ReSetDemoVideo();
		m_pSideMovieVideoLayer->ReSetVideo();
	}
	m_bIsPlayVideo = false;
	m_bIsStepPlay = false;
	Ext_IsThreadOn = true;
	Ext_IsRecordBegin = false;
	CCMenuItemToggle* pToggle = (CCMenuItemToggle*)(m_pMenu->getChildByTag(99));
	pToggle->setSelectedIndex(0);
	this->schedule(schedule_selector(PostureAnalysisScene::Update), 1.5f / 60.0f);
}
void PostureAnalysisScene::CallbackSetMode(CCObject* pSender)
{
	if (pSender == m_pDanjian)
	{
		m_bSetMode = false;
		m_pDanjian->setEnabled(false);
		m_pXunhuan->setEnabled(true);
	}
	else
	{
		m_bSetMode = true;
		m_pDanjian->setEnabled(true);
		m_pXunhuan->setEnabled(false);
	}
}