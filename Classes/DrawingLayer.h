#pragma once
#include "Tools.h"

USING_NS_CC;
class DrawingLayer:public CCLayer
{
private:
	//static DrawingLayer* m_pSelf;
	//DrawingLayer(void);
public:
    //按钮和选色板
    CCMenuItemToggle* m_pMenuItemToggle;
	CCMenuItemImage* m_pDrawingItem;
	CCMenuItemImage* m_pDrawRecItem;
	CCMenuItemImage* m_pDrawCirItem;
	CCMenuItemImage* m_pDrawAngleItem;
	CCMenuItemImage* m_pDeleteItem;
	CCMenuItemImage* m_pClsItem;
    CCLayerColor* m_pRedLayer;
    CCLayerColor* m_pGreenLayer;
    CCLayerColor* m_pBlueLayer;
    CCLayerColor* m_pYellowLayer;
	CCSprite* m_pColorBox;
	CCSprite* m_pFontBox;
    //绘画容器
    vector<ColorPoint> m_PointVec;
    vector<ColorRect> m_RectVec;
    vector<ColorCircle> m_CircleVec;
	vector<ColorAngle> m_AngleVec;
	stack<int> m_DrawSta;
    //当前选择的颜色和绘画形状
    ccColor3B m_cSelectedColor;
    CCPoint m_PointEnd;
    ColorRect m_curRect;
    ColorCircle m_curCircle;
	ColorAngle m_curAngle;
    //开关
    bool m_bIsDrawRect;
    bool m_bIsDrawCircle;
    bool m_bIsDrawing;
	bool m_bIsDrawAngle;
	bool m_bIsDrawAngleEnd;
    bool m_bIsDelete;
    bool m_bIsCls;
public:
	//static DrawingLayer* shareDrawingLayer(void);
	DrawingLayer(void);
    ~DrawingLayer(void);
    CREATE_FUNC(DrawingLayer);
    //按钮和开关按钮的回调函数
    void menuToggleCallBack(CCObject* pSender);
    void menuCallBack(CCObject* pSender);
    //类初始化
    virtual bool init();
    //触摸事件
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //绘画函数
    void draw(void);
	void ClsAll();
};

