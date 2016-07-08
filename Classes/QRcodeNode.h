#pragma once
#include "cocos2d.h"

USING_NS_CC;
class QRcodeNode:public CCNode
{
public:
	QRcodeNode(void);
	~QRcodeNode(void);
public:
	CCSprite* m_BackGround;
	char* m_QRcodeText;
	char* m_PicFile;

	CREATE_FUNC(QRcodeNode);
	virtual bool init();
};

