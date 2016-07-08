#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include"Tools.h"

USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
    CUETYPE m_curCueType;
    GENDER m_curGender;
	float m_curTarget;
    CCMenuItemImage* m_pCueTtpeArr[4];
    CCMenuItemImage* m_pGenderArr[2];

    //初始化函数
    virtual bool init();
	virtual void update(float dt);
    static cocos2d::CCScene* scene();
    //按钮的回调函数
    void menuCallback(CCObject* pSender);
	void menuSettingCallback(CCObject* pSender);
	void menuCueTtpeCallback(CCObject* pSender);
	void menuGenderCallback(CCObject* pSender);
	bool onTextFieldAttachWithIME(CCTextFieldTTF * sender);
	bool onTextFieldDetachWithIME(CCTextFieldTTF * sender);
	bool onTextFieldInsertText(CCTextFieldTTF * sender, const char * text, int nLen);
	bool onTextFieldDeleteBackward(CCTextFieldTTF * sender, const char * delText, int nLen);
    //当前类的创建函数（宏）
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
