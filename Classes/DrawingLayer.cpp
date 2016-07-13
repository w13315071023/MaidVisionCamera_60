#include "DrawingLayer.h"
#include "PostureAnalysisScene.h"
#include "MyMenu.h"

DrawingLayer::DrawingLayer(void)
{
}
DrawingLayer::~DrawingLayer(void)
{
}
bool DrawingLayer::init()
{
    //初始化父类
    if(!CCLayer::init())
    {
        return false;
    }
    m_bIsDrawing = false;
    m_bIsDelete = false;
    m_bIsCls = false;
    m_bIsDrawRect = false;
    m_bIsDrawCircle = false;
	m_bIsDrawAngle = false;
	m_bIsDrawAngleEnd = false;
    m_PointEnd = ccp(-10,-10);
    m_cSelectedColor = ccc3(255,0,0);
	m_pRedLayer = CCLayerColor::create(ccc4(255, 0, 0, 255), 60, 42);
	m_pGreenLayer = CCLayerColor::create(ccc4(0, 255, 0, 255), 60, 42);
	m_pBlueLayer = CCLayerColor::create(ccc4(0, 0, 255, 255), 60, 42);
	m_pYellowLayer = CCLayerColor::create(ccc4(255, 255, 0, 255), 60, 42);

	m_pColorBox = CCSprite::create("UI_DrawLayer/彩块边缘光.png");
	m_pColorBox->setPosition(ccp(1857 + 200, 483 + 58 * 3));
	this->addChild(m_pColorBox);
	m_pFontBox = CCSprite::create("UI_DrawLayer/字体边缘光.png");
	m_pFontBox->setPosition(ccp(1857, -100));
	this->addChild(m_pFontBox);

    //创建绘图按钮开关
	m_pMenuItemToggle = CCMenuItemToggle::createWithTarget(
		this, menu_selector(DrawingLayer::menuToggleCallBack),
		CCMenuItemImage::create("UI_DrawLayer/绘图.png", "UI_DrawLayer/绘图.png"),
		CCMenuItemImage::create("UI_DrawLayer/关闭.png", "UI_DrawLayer/关闭.png"),
		NULL);
	//创建绘图工具按钮
	m_pDrawAngleItem = CCMenuItemImage::create(
		"UI_DrawLayer/画角.png",
		"UI_DrawLayer/画角.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));
	m_pDrawCirItem = CCMenuItemImage::create(
		"UI_DrawLayer/画圆.png",
		"UI_DrawLayer/画圆.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));
	m_pDrawRecItem = CCMenuItemImage::create(
		"UI_DrawLayer/画框.png",
		"UI_DrawLayer/画框.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));
	m_pDrawingItem = CCMenuItemImage::create(
		"UI_DrawLayer/画线.png",
		"UI_DrawLayer/画线.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));

	m_pDeleteItem = CCMenuItemImage::create(
		"UI_DrawLayer/撤销.png",
		"UI_DrawLayer/撤销.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));

	m_pClsItem = CCMenuItemImage::create(
		"UI_DrawLayer/清除.png",
		"UI_DrawLayer/清除.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));
    //关闭层的忽略锚点
    m_pRedLayer->ignoreAnchorPointForPosition(false);
    m_pGreenLayer->ignoreAnchorPointForPosition(false);
    m_pBlueLayer->ignoreAnchorPointForPosition(false);
    m_pYellowLayer->ignoreAnchorPointForPosition(false);
    //设置按钮的锚点
    m_pMenuItemToggle->setAnchorPoint(ccp(0.5,0.5));
    m_pDrawingItem->setAnchorPoint(ccp(0.5,0.5));
    m_pDeleteItem->setAnchorPoint(ccp(0.5,0.5));
	m_pClsItem->setAnchorPoint(ccp(0.5, 0.5));
	m_pDrawAngleItem->setAnchorPoint(ccp(0.5, 0.5));
	m_pDrawRecItem->setAnchorPoint(ccp(0.5, 0.5));
	m_pDrawCirItem->setAnchorPoint(ccp(0.5, 0.5));
	m_pRedLayer->setAnchorPoint(ccp(0.5, 0.5));
	m_pGreenLayer->setAnchorPoint(ccp(0.5, 0.5));
	m_pBlueLayer->setAnchorPoint(ccp(0.5, 0.5));
	m_pYellowLayer->setAnchorPoint(ccp(0.5, 0.5));
    //设置按钮的位置
	m_pDrawAngleItem->setPosition(ccp(1857, -100));
	m_pMenuItemToggle->setPosition(ccp(1857, 93));
	m_pDrawingItem->setPosition(ccp(1857, -100));
	m_pDeleteItem->setPosition(ccp(1857, -100));
	m_pClsItem->setPosition(ccp(1857, -100));
	m_pDrawRecItem->setPosition(ccp(1857, -100));
	m_pDrawCirItem->setPosition(ccp(1857, -100));
	m_pRedLayer->setPosition(ccp(1857+200, 483+58*3));
	m_pGreenLayer->setPosition(ccp(1857+200,483+58*2));
	m_pBlueLayer->setPosition(ccp(1857+200, 483+58*1));
	m_pYellowLayer->setPosition(ccp(1857+200, 483+58*0));
    //将控件添加到渲染树
    this->addChild(m_pRedLayer);
    this->addChild(m_pGreenLayer);
    this->addChild(m_pBlueLayer);
    this->addChild(m_pYellowLayer);
    //将按钮添加到按钮层并渲染
	MyMenu* pMenu = MyMenu::create(
                                m_pMenuItemToggle,
                                m_pDrawingItem,
                                m_pDeleteItem,
                                m_pClsItem,
                                m_pDrawRecItem,
                                m_pDrawCirItem,
								m_pDrawAngleItem,
                                NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

    return true;
}
//开关按钮的回调函数
void DrawingLayer::menuToggleCallBack(CCObject* pSender)
{
	Ext_IsResetGG = true;
    //获取开关按钮当前的状态
    int index = m_pMenuItemToggle->getSelectedIndex();
    //CCLog("%d",index);
    if(index == 1)
    {
        //控制按钮和选色板的动画位置（进入）
		//m_pDrawAngleItem->runAction(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 5)));
		//m_pDrawRecItem->runAction(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 4)));
		//m_pDrawCirItem->runAction(CCMoveTo::create(0.3, ccp(1857, 155+62*3)));
		//m_pDrawingItem->runAction(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 2)));
		//m_pDeleteItem->runAction(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 1)));
		//m_pClsItem->runAction(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 0)));
		//m_pRedLayer->runAction(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 3)));
		//m_pGreenLayer->runAction(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 2)));
		//m_pBlueLayer->runAction(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 1)));
		//m_pYellowLayer->runAction(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 0)));
		//m_pColorBox->runAction(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 3)));
		m_pDrawAngleItem->setPosition( ccp(1857, 155 + 62 * 5));
		m_pDrawRecItem->setPosition(ccp(1857, 155 + 62 * 4));
		m_pDrawCirItem->setPosition( ccp(1857, 155 + 62 * 3));
		m_pDrawingItem->setPosition(ccp(1857, 155 + 62 * 2));
		m_pDeleteItem->setPosition(ccp(1857, 155 + 62 * 1));
		m_pClsItem->setPosition(ccp(1857, 155 + 62 * 0));
		m_pRedLayer->setPosition( ccp(1857, 545 + 58 * 3));
		m_pGreenLayer->setPosition(ccp(1857, 545 + 58 * 2));
		m_pBlueLayer->setPosition(ccp(1857, 545 + 58 * 1));
		m_pYellowLayer->setPosition(ccp(1857, 545 + 58 * 0));
		m_pColorBox->setPosition(ccp(1857, 545 + 58 * 3));
    }
    else
    {
        //控制按钮和选色板的动画位置（退出）
		//m_pDrawAngleItem->runAction(CCMoveTo::create(0.3, ccp(1857, -100)));
		//m_pDrawingItem->runAction(CCMoveTo::create(0.3, ccp(1857, -100)));
		//m_pDeleteItem->runAction(CCMoveTo::create(0.3, ccp(1857, -100)));
		//m_pClsItem->runAction(CCMoveTo::create(0.3, ccp(1857, -100)));
		//m_pDrawRecItem->runAction(CCMoveTo::create(0.3, ccp(1857, -100)));
		//m_pDrawCirItem->runAction(CCMoveTo::create(0.3, ccp(1857, -100)));
		//m_pRedLayer->runAction(CCMoveTo::create(0.3, ccp(1857 + 200, 545 + 58 * 3)));
		//m_pGreenLayer->runAction(CCMoveTo::create(0.3, ccp(1857 + 200, 545 + 58 * 2)));
		//m_pBlueLayer->runAction(CCMoveTo::create(0.3, ccp(1857 + 200, 545 + 58 * 1)));
		//m_pYellowLayer->runAction(CCMoveTo::create(0.3, ccp(1857 + 200, 545 + 58 * 0)));
		//m_pColorBox->runAction(CCMoveTo::create(0.3, ccp(m_pColorBox->getPosition().x + 200, m_pColorBox->getPosition().y)));
		//m_pFontBox->runAction(CCMoveTo::create(0.3, ccp(1857, -100)));

		m_pDrawAngleItem->setPosition(ccp(1857, -100));
		m_pDrawingItem->setPosition(ccp(1857, -100));
		m_pDeleteItem->setPosition(ccp(1857, -100));
		m_pClsItem->setPosition(ccp(1857, -100));
		m_pDrawRecItem->setPosition( ccp(1857, -100));
		m_pDrawCirItem->setPosition(ccp(1857, -100));
		m_pRedLayer->setPosition(ccp(1857 + 200, 545 + 58 * 3));
		m_pGreenLayer->setPosition(ccp(1857 + 200, 545 + 58 * 2));
		m_pBlueLayer->setPosition(ccp(1857 + 200, 545 + 58 * 1));
		m_pYellowLayer->setPosition(ccp(1857 + 200, 545 + 58 * 0));
		m_pColorBox->setPosition(ccp(m_pColorBox->getPosition().x + 200, m_pColorBox->getPosition().y));
		m_pFontBox->setPosition(ccp(1857, -100));

        //关闭触摸事件
        this->setTouchEnabled(false);
        //关闭绘画工具
        m_bIsDrawing = false;
        m_bIsDelete = false;
        m_bIsCls = false;
        m_bIsDrawRect = false;
        m_bIsDrawCircle = false;
    }
}
//按钮的回调函数
void DrawingLayer::menuCallBack(CCObject* pSender)
{
	Ext_IsResetGG = true;
    if(m_pDrawingItem == pSender)
    {//绘画按钮的事件
        m_bIsDelete = false;
        m_bIsDrawing = true;
        m_bIsDrawRect = false;
        m_bIsDrawCircle = false;
		m_bIsDrawAngle = false;
		m_pFontBox->setPosition(m_pDrawingItem->getPosition());
    }
    else if(m_pDeleteItem == pSender)
    {
		m_bIsDrawAngleEnd = false;
		m_curAngle = {};
		if (m_DrawSta.empty())
		{
			return;
		}
		//取出当前最后一次绘画ID
		int index = m_DrawSta.top();
		switch (index)
		{
		case 1:
		{
			m_bIsDrawAngleEnd = false;
			m_curAngle = {};
			//删除线段
			bool IsDelPoint = false;
			vector<ColorPoint> ::reverse_iterator riter = m_PointVec.rbegin();
			while (riter != m_PointVec.rend())
			{
				if (riter->pos.equals(m_PointEnd))
				{
					IsDelPoint = !IsDelPoint;
					if (IsDelPoint == true)
					{
						m_PointVec.erase((riter + 1).base());
						riter = m_PointVec.rbegin();
					}
					else
					{
						break;
					}
				}
				else
				{
					m_PointVec.erase((riter + 1).base());
					riter = m_PointVec.rbegin();
				}
			}
		}
		break;
		//删除画框
		case 2:
		{
			if (!m_RectVec.empty())
			{
				m_RectVec.pop_back();
			}
		}
		break;
		//删除圆
		case 3:
		{
			if (!m_CircleVec.empty())
			{
				m_CircleVec.pop_back();
			}
		}
		break;
		//删除角
		case 4:
		{
			if (!m_AngleVec.empty())
			{
				this->removeChild(m_AngleVec.back().label);
				m_AngleVec.pop_back();
			}
		}
		break;
		}
		//弹出栈顶
		m_DrawSta.pop();
	}
    else if(m_pDrawRecItem == pSender)
    {//画框按钮的事件
		m_pFontBox->setPosition(m_pDrawRecItem->getPosition());
        m_bIsDelete = false;
        m_bIsDrawing = false;
        m_bIsDrawRect = true;
        m_bIsDrawCircle = false;
		m_bIsDrawAngle = false;
    }
    else if(m_pDrawCirItem == pSender)
    {//画圆按钮的事件
		m_pFontBox->setPosition(m_pDrawCirItem->getPosition());
        m_bIsDelete = false;
        m_bIsDrawing = false;
        m_bIsDrawRect = false;
        m_bIsDrawCircle = true;
		m_bIsDrawAngle = false;
    }
	else if (m_pDrawAngleItem == pSender)
	{//画角按钮的事件
		m_pFontBox->setPosition(m_pDrawAngleItem->getPosition());
		m_bIsDelete = false;
		m_bIsDrawing = false;
		m_bIsDrawRect = false;
		m_bIsDrawCircle = false;
		m_bIsDrawAngle = true;
	}
    else if(m_pClsItem == pSender)
    {//清楚按钮的回调
		this->ClsAll();
    }
    //开启单点触摸
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
}
//触摸按下时的回调
bool DrawingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	Ext_IsResetGG = true;
    //获取触摸点
    CCPoint pos = pTouch->getLocation();
    //选取颜色
    if(m_pRedLayer->boundingBox().containsPoint(pos))
    {
        m_cSelectedColor = m_pRedLayer->getColor();
		m_pColorBox->setPosition(m_pRedLayer->getPosition());
    }
    else if(m_pGreenLayer->boundingBox().containsPoint(pos))
    {
        m_cSelectedColor = m_pGreenLayer->getColor();
		m_pColorBox->setPosition(m_pGreenLayer->getPosition());
    }
    else if(m_pBlueLayer->boundingBox().containsPoint(pos))
    {
        m_cSelectedColor = m_pBlueLayer->getColor();
		m_pColorBox->setPosition(m_pBlueLayer->getPosition());
    }
    else if(m_pYellowLayer->boundingBox().containsPoint(pos))
    {
        m_cSelectedColor = m_pYellowLayer->getColor();
		m_pColorBox->setPosition(m_pYellowLayer->getPosition());
    }
	if (
		m_bIsDrawing == false &&
		m_bIsDrawRect == false &&
		m_bIsDrawCircle == false &&
		m_bIsDrawAngle == false)
    {
        return false;
    }
    //记录画线点开始
	if (pos.x<100 || pos.x>1820 || pos.y<100 || pos.y>980)
	{
		return false;
	}
    if(m_bIsDrawing == true)
    {
        ColorPoint cp;
        cp.pos = pos;
        cp.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
        m_PointVec.push_back(cp);
    }
    //记录画框坐标开始
    else if(m_bIsDrawRect == true)
    {
        m_curRect.pos1 = pos;
        m_curRect.pos2 = pos;
        m_curRect.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
    }
    //记录画圆坐标开始
    else if(m_bIsDrawCircle == true)
    {
        m_curCircle.center = pos;
        m_curCircle.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
    }
	//记录画角坐标开始
	else if (m_bIsDrawAngle == true)
	{
		if (m_bIsDrawAngleEnd == false)
		{
			m_curAngle.pos1 = pos;
			m_curAngle.pos2 = pos;
			m_curAngle.pos3 = pos;
			m_curAngle.c4b = ccc4(m_cSelectedColor.r,
				m_cSelectedColor.g,
				m_cSelectedColor.b,
				255);
		}
		else
		{
			m_curAngle.pos3 = pos;
			CCPoint vector1 = (m_curAngle.pos2 - m_curAngle.pos1).normalize();
			CCPoint vector2 = (m_curAngle.pos3 - m_curAngle.pos1).normalize();
			float radians = ccpAngle(vector1, vector2);
			m_curAngle.angle = CC_RADIANS_TO_DEGREES(radians);
			char name[32];
			sprintf(name, "%.2f", m_curAngle.angle);
			m_curAngle.label = CCLabelTTF::create(name, "airal", 20);
			m_curAngle.label->setPosition(ccp(m_curAngle.pos1.x + 10, m_curAngle.pos1.y));
			m_curAngle.label->setColor(ccc3(0, 255, 255));
			this->addChild(m_curAngle.label);
		}
	}
    return true;
    
}
//触摸移动时的回调
void DrawingLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	Ext_IsResetGG = true;
    //获取触摸点
    CCPoint pos = pTouch->getLocation();
	if (pos.x<100 || pos.x>1820 || pos.y<100 || pos.y>980)
	{
		return;
	}
    //记录绘画触摸点
    if(m_bIsDrawing == true)
    {
        ColorPoint cp;
        cp.pos = pos;
        cp.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
        m_PointVec.push_back(cp);
    }
    else if(m_bIsDrawRect == true)
    {
        m_curRect.pos2 = pos;
    }
    else if(m_bIsDrawCircle == true)
    {
        float a = m_curCircle.center.x;
        float b = m_curCircle.center.y;
        float d = sqrt(pow(a-pos.x,2)+pow(b-pos.y,2));
        m_curCircle.radius = d;
    }
	else if (m_bIsDrawAngle == true)
	{
		if (m_bIsDrawAngleEnd == false)
		{
			m_curAngle.pos2 = pos;
		}
		else
		{
			m_curAngle.pos3 = pos;
			CCPoint vector1 = (m_curAngle.pos2 - m_curAngle.pos1).normalize();
			CCPoint vector2 = (m_curAngle.pos3 - m_curAngle.pos1).normalize();
			float radians = ccpAngle(vector1, vector2);
			m_curAngle.angle = CC_RADIANS_TO_DEGREES(radians);
			char name[32];
			sprintf(name, "%.2f", m_curAngle.angle);
			m_curAngle.label->setString(name);
		}
	}
}
//触摸抬起时的回调
void DrawingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	Ext_IsResetGG = true;
    CCPoint pos = pTouch->getLocation();
	if (pos.x<100 || pos.x>1820 || pos.y<100 || pos.y>980)
	{
		return;
	}
    //记录画线点结束
    if(m_bIsDrawing == true)
    {
        ColorPoint cp;

        cp.pos = pos;
        cp.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
        m_PointVec.push_back(cp);
        cp.pos = m_PointEnd;
        m_PointVec.push_back(cp);
		m_DrawSta.push(1);
    }
    //记录画框坐标结束
    else if(m_bIsDrawRect == true)
    {
        m_curRect.pos2 = pos;
        m_RectVec.push_back(m_curRect);
        m_curRect.pos1 = ccp(-1,-1);
        m_curRect.pos2 = ccp(-1,-1);
		m_DrawSta.push(2);
    }
    //记录画圆坐标结束
    else if(m_bIsDrawCircle == true)
    {
        float a = m_curCircle.center.x;
        float b = m_curCircle.center.y;
        float d = sqrt(pow(a-pos.x,2)+pow(b-pos.y,2));
        m_curCircle.radius = d;
        m_CircleVec.push_back(m_curCircle);
        m_curCircle.radius = 0;
		m_DrawSta.push(3);
    }
	//记录画角坐标结束
	else if (m_bIsDrawAngle == true)
	{
		if (m_bIsDrawAngleEnd == false)
		{
			m_curAngle.pos2 = pos;
		}
		else
		{
			m_curAngle.pos3 = pos;
			CCPoint vector1 = (m_curAngle.pos2 - m_curAngle.pos1).normalize();
			CCPoint vector2 = (m_curAngle.pos3 - m_curAngle.pos1).normalize();
			float radians = ccpAngle(vector1, vector2);
			m_curAngle.angle = CC_RADIANS_TO_DEGREES(radians);
			m_AngleVec.push_back(m_curAngle);
			m_DrawSta.push(4);
			m_curAngle = {};
		}
		m_bIsDrawAngleEnd = !m_bIsDrawAngleEnd;
	}
}
//绘画函数
void DrawingLayer::draw(void)
{
	//设置绘画时的属性
	ccPointSize(LINEWIDTH);
	glLineWidth(LINEWIDTH);
    //根据记录的绘画点画线
    vector<ColorPoint> ::iterator iter;
    for(iter = m_PointVec.begin();iter != m_PointVec.end();iter++)
    {
        if(iter == m_PointVec.begin())
        {
            ccDrawColor4B((*iter).c4b.r,(*iter).c4b.g,(*iter).c4b.b,(*iter).c4b.a);
            ccDrawPoint((*iter).pos);
        }
		else if ((*iter).pos.equals(m_PointEnd))
        {
            continue;
        }
        else if((*(iter-1)).pos.equals(m_PointEnd))
        {
            ccDrawColor4B((*iter).c4b.r,(*iter).c4b.g,(*iter).c4b.b,(*iter).c4b.a);
            ccDrawPoint((*iter).pos);
        }
        else
        {
            ccDrawColor4B((*iter).c4b.r,(*iter).c4b.g,(*iter).c4b.b,(*iter).c4b.a);
            ccDrawLine((*(iter-1)).pos,(*iter).pos);
        }
    }
    //根据记录坐标画框
    ccDrawColor4B(m_curRect.c4b.r,
                m_curRect.c4b.g,
                m_curRect.c4b.b,
                m_curRect.c4b.a);
    ccDrawRect(m_curRect.pos1,m_curRect.pos2);
    vector<ColorRect> ::iterator Riter;
    for(Riter = m_RectVec.begin();Riter != m_RectVec.end();Riter++)
    {
        ccDrawColor4B(Riter->c4b.r,
                    Riter->c4b.g,
                    Riter->c4b.b,
                    Riter->c4b.a);
        ccDrawRect(Riter->pos1,Riter->pos2);
    }
    //根据记录坐标画圆
    ccDrawColor4B(m_curCircle.c4b.r,m_curCircle.c4b.g,m_curCircle.c4b.b,m_curCircle.c4b.a);
    ccDrawCircle(m_curCircle.center,m_curCircle.radius,
        m_curCircle.angle,m_curCircle.segments,m_curCircle.drawLineToCenter);
    vector<ColorCircle> ::iterator Citer;
    for(Citer = m_CircleVec.begin();Citer != m_CircleVec.end();Citer++)
    {
        ccDrawColor4B(Citer->c4b.r,
                    Citer->c4b.g,
                    Citer->c4b.b,
                    Citer->c4b.a);
        ccDrawCircle(Citer->center,
                    Citer->radius,
                    Citer->angle,
                    Citer->segments,
                    Citer->drawLineToCenter);
    }
	//根据记录坐标画角
	ccDrawColor4B(m_curAngle.c4b.r, m_curAngle.c4b.g, m_curAngle.c4b.b, m_curAngle.c4b.a);
	ccDrawLine(m_curAngle.pos1, m_curAngle.pos2);
	ccDrawLine(m_curAngle.pos1, m_curAngle.pos3);
    vector<ColorAngle> ::iterator Angle;
	for (Angle = m_AngleVec.begin(); Angle != m_AngleVec.end(); Angle++)
    {
		ccDrawColor4B(Angle->c4b.r,
					Angle->c4b.g,
					Angle->c4b.b,
					Angle->c4b.a);
		ccDrawLine(Angle->pos1, Angle->pos2);
		ccDrawLine(Angle->pos1, Angle->pos3);
    }
}
//清楚所有绘制数据
void DrawingLayer::ClsAll()
{
	Ext_IsResetGG = true;
	m_bIsDrawAngleEnd = false;
	m_curAngle = {};
	if (!m_PointVec.empty())
	{
		m_PointVec.clear();
	}
	if (!m_RectVec.empty())
	{
		m_RectVec.clear();
	}
	if (!m_CircleVec.empty())
	{
		m_CircleVec.clear();
	}
	if (!m_AngleVec.empty())
	{
		vector<ColorAngle> ::iterator Angle;
		for (Angle = m_AngleVec.begin(); Angle != m_AngleVec.end(); Angle++)
		{
			this->removeChild(Angle->label);
		}
		m_AngleVec.clear();
	}
}