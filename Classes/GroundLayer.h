#pragma once
#include "Tools.h"

USING_NS_CC;
//ÂäµãÍ¼
class GroundLayer:public CCSprite
{
public:
    GroundLayer(void);
    ~GroundLayer(void);
	vector<vector<CCPoint>*> m_vec;
    CREATE_FUNC(GroundLayer);
    bool init();
};

