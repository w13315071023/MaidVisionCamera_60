#include "MyMenu.h"


MyMenu::MyMenu(void)
{
	m_curTime = 0;
	m_isTouching = false;
}


MyMenu::~MyMenu(void)
{
}
MyMenu* MyMenu::create()
{
	return MyMenu::create(NULL, NULL);
}

MyMenu * MyMenu::create(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args, item);

	MyMenu *pRet = MyMenu::createWithItems(item, args);

	va_end(args);

	return pRet;
}

MyMenu* MyMenu::createWithArray(CCArray* pArrayOfItems)
{
	MyMenu *pRet = new MyMenu();
	if (pRet && pRet->initWithArray(pArrayOfItems))
	{
		pRet->scheduleUpdate();
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

MyMenu* MyMenu::createWithItems(CCMenuItem* item, va_list args)
{
	CCArray* pArray = NULL;
	if (item)
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while (i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}
	return MyMenu::createWithArray(pArray);
}

MyMenu* MyMenu::createWithItem(CCMenuItem* item)
{
	return MyMenu::create(item, NULL);
}
bool MyMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	bool temp = CCMenu::ccTouchBegan(touch, event);
	if (temp)
	{
		m_isTouching = true;
	}
	return temp;
}
void MyMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCMenu::ccTouchMoved(touch, event);
}
void MyMenu::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	m_isTouching = false;
	CCMenu::ccTouchEnded(touch, event);
}
void MyMenu::update(float dt)
{
	if (m_isTouching)
	{
		if (m_curTime > 10)
		{
			printf("time out!\n");
			this->ccTouchEnded(0,0);
			m_curTime = 0;
		}
		m_curTime++;
	}
	else
	{
		m_curTime = 0;
	}
}