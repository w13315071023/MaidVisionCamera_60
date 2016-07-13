#pragma once
#include "cocos2d.h"

USING_NS_CC;
class MyMenu : public CCMenu
{
public:

	int m_curTime;
	bool m_isTouching;


    MyMenu(void);
    ~MyMenu(void);
	/** creates an empty MyMenu */
	static MyMenu* create();

	/** creates a MyMenu with MyMenuItem objects
	* @lua NA
	*/
	static MyMenu* create(CCMenuItem* item, ...);

	/** creates a MyMenu with a CCArray of MyMenuItem objects
	* @js NA
	*/
	static MyMenu* createWithArray(CCArray* pArrayOfItems);

	/** creates a MyMenu with it's item, then use addChild() to add
	* other items. It is used for script, it can't init with undetermined
	* number of variables.
	* @js NA
	*/
	static MyMenu* createWithItem(CCMenuItem* item);

	/** creates a MyMenu with MyMenuItem objects
	* @js NA
	* @lua NA
	*/
	static MyMenu* createWithItems(CCMenuItem *firstItem, va_list args);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void update(float dt);
};

