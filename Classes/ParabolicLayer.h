#pragma once
#include "Tools.h"

USING_NS_CC;
//Å×ÎïÍ¼
class ParabolicLayer:public CCSprite
{
private:
	int m_fTime;
	float m_fVelocity;
	float m_fAngle;
public:
	vector<vector<CCPoint>*> m_vec;
    ParabolicLayer(void);
    ~ParabolicLayer(void);
    CREATE_FUNC(ParabolicLayer);
    bool init();
	//virtual void draw(void);
};

