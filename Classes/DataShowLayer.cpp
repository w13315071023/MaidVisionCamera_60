#include "DataShowLayer.h"
#include "DataMager.h"

DataShowLayer::DataShowLayer(void)
{
}


DataShowLayer::~DataShowLayer(void)
{
}
bool DataShowLayer::init()
{
	if (!CCSprite::initWithFile("DataUI/shujuxianshi.png"))
    {
        return false;
    }
	DataMager* pData = DataMager::shareDataMager();

	m_pBackspinLabel = CCLabelTTF::create(GBKToUTF8("0").c_str(), "Arial", 24);
	m_pSidespinLabel = CCLabelTTF::create(GBKToUTF8("0").c_str(), "Arial", 24);
	m_pPitchLabel = CCLabelTTF::create(GBKToUTF8("0").c_str(), "Arial", 24);
	m_pYawLabel = CCLabelTTF::create(GBKToUTF8("0").c_str(), "Arial", 24);
	m_pVelocityLabel = CCLabelTTF::create(GBKToUTF8("0").c_str(), "Arial", 24);
	//m_pCam_confidenceLabel	= CCLabelTTF::create(GBKToUTF8("0").c_str(), "Arial", 24);

	m_pBackspinLabel->setAnchorPoint(ccp(0, 0.5));
	m_pSidespinLabel->setAnchorPoint(ccp(0, 0.5));
	m_pPitchLabel->setAnchorPoint(ccp(0, 0.5));
	m_pYawLabel->setAnchorPoint(ccp(0, 0.5));
	m_pVelocityLabel->setAnchorPoint(ccp(0, 0.5));
	//m_pCam_confidenceLabel->setAnchorPoint(ccp(0, 0.5));

	m_pBackspinLabel->setPosition(ccp(157, 50));
	m_pSidespinLabel->setPosition(ccp(440, 50));
	m_pPitchLabel->setPosition(ccp(752, 50));
	m_pYawLabel->setPosition(ccp(1052, 50));
	m_pVelocityLabel->setPosition(ccp(1342, 50));
	//m_pCam_confidenceLabel->setPosition(ccp( 80, 50));

	this->addChild(m_pBackspinLabel);
	this->addChild(m_pSidespinLabel);
	this->addChild(m_pPitchLabel);
	this->addChild(m_pYawLabel);
	this->addChild(m_pVelocityLabel);
	//this->addChild(m_pCam_confidenceLabel);

    return true;
}
void DataShowLayer::ShowData(
	float Backspin,
	float Sidespin,
	float Velocity,
	float Pitch,
	float Yaw,
	float Cam_confidence)
{
	char name[32];
	sprintf(name, "%d", (int)Backspin);
	m_pBackspinLabel->setString(name);
	sprintf(name, "%d", (int)Sidespin);
	m_pSidespinLabel->setString(name);
	sprintf(name, "%d", (int)Velocity);
	m_pVelocityLabel->setString(name);
	sprintf(name, "%d", (int)Pitch);
	m_pPitchLabel->setString(name);
	sprintf(name, "%d", (int)Yaw);
	m_pYawLabel->setString(name);
}