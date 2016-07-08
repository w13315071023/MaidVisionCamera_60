#pragma once
#include "cocos2d.h"

USING_NS_CC;
class DataShowLayer:public CCSprite
{
public:
    DataShowLayer(void);
    ~DataShowLayer(void);
    CREATE_FUNC(DataShowLayer);
    bool init();
	void ShowData(float Backspin, float Sidespin, float Velocity, float Pitch, float Yaw, float Cam_confidence);

	CCLabelTTF* m_pBackspinLabel;
	CCLabelTTF* m_pSidespinLabel;
	CCLabelTTF* m_pVelocityLabel;
	CCLabelTTF* m_pPitchLabel;
	CCLabelTTF* m_pYawLabel;
	CCLabelTTF* m_pCam_confidenceLabel;
};

