#pragma once
#include "Tools.h"

class UINode:public CCSprite
{
public:
	CCLabelTTF* m_pLabelTTF;
	UINode(void);
	~UINode(void);
	CREATE_FUNC(UINode);
	bool init();
	void update(float dt);
	void menuCallBackZuo(CCObject* pSender);
	void menuCallBackYou(CCObject* pSender);
};

