#pragma once
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class DrawNode :public CCNode
{
public:
	CREATE_FUNC(DrawNode);
	vector<vector<CCPoint>*> m_pVec;
	DrawNode(void);
	~DrawNode(void);

	virtual bool init();
	virtual void draw(void);
	void setDrawPoint(vector<vector<CCPoint>*> pVec);
};

