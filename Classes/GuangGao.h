#pragma once
#include "Tools.h"
class GuangGao :public CCLayer
{
public:
	int m_Time;
	CCSprite* m_pImage;
public:
	GuangGao(void);
	~GuangGao(void);
	static CCScene* getScene();
	CREATE_FUNC(GuangGao);
	virtual bool init();
	virtual void update(float dt);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};

