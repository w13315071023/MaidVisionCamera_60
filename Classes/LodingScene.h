#pragma once
#include "Tools.h"
class LodingScene:public CCLayer
{
public:
	LodingScene(void);
	~LodingScene(void);
	static CCScene* getLodingScene();
	CREATE_FUNC(LodingScene);
	bool init();
	void update(float dt);
};

