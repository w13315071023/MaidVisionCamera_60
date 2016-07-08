#pragma once
#include "Tools.h"
class ResetGGMager :public CCObject
{
private:
	static ResetGGMager* m_Self;
	int m_ResetTime;
	ResetGGMager(void);
public:
	~ResetGGMager(void);
	void update(float dt);
	static ResetGGMager* ResetGGMager::getInstance();
	static void pause();
	static void resume();
};

