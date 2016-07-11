#pragma once
#include "Tools.h"
class Logo:public CCLayer
{
public:
	Logo(void);
	~Logo(void);
	static CCScene* getScene();
	CREATE_FUNC(Logo);
	bool init();
	void update(float dt);
};

