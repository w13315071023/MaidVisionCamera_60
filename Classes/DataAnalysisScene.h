#pragma once
#include "Tools.h"

USING_NS_CC;
class GroundLayer;
class ParabolicLayer;
class TargetLayer;
class DataShowLayer;
class DrawingLayer;
class DataView;
class DataAnalysisScene:public CCLayer
{
public:
	static DrawingLayer* m_pDrawingLayer2;
    DataAnalysisScene(void);
    ~DataAnalysisScene(void);
	DataView* m_pDataView;
    //落点图
    GroundLayer*        m_pGroundLayer;
    //抛物图
    ParabolicLayer*     m_pParabolicLayer;
    //靶心图
    TargetLayer*        m_pTargetLayer;
    //数据显示
    DataShowLayer*      m_pDataShowLayer;
    //场景的创建函数
    static CCScene* CreateScene();
    //本类的创建函数
    CREATE_FUNC(DataAnalysisScene);
    //初始化函数
    bool init();
    //按钮的回调函数
    void menuCallback(CCObject* pSender);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};

