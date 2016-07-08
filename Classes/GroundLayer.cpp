#include "GroundLayer.h"
#include "DataMager.h"
#include "DrawNode.h"


GroundLayer::GroundLayer(void)
{
}


GroundLayer::~GroundLayer(void)
{
	vector<vector<CCPoint>*> ::iterator iter = m_vec.begin();
	for (iter; iter != m_vec.end(); iter++)
	{
		delete (*iter);
	}
}
bool GroundLayer::init()
{
	if (!CCSprite::initWithFile("DataUI/luodiantu.png"))
    {
        return false;
    }
	CCSprite* pBaxin = CCSprite::create("DataUI/baxinxiao.png");
	pBaxin->setPosition(ccp(272, 54 + instenceTarget * LUODIANBILI));
	this->addChild(pBaxin,-1);
	DataMager* pDate = DataMager::shareDataMager();
	for (size_t i = 0; i < pDate->size(); i++)
	{
		vector<CCPoint>* vecTemp = new vector<CCPoint>();
		vecTemp->push_back(ccp(0, 0));

		float x = pDate->getVelocity_xById(i)*pDate->getTimeById(i)*LUODIANBILI;
		float y = pDate->getVelocity_yById(i)*pDate->getTimeById(i)*LUODIANBILI;

		if (x>0&&y<150&&y>-150)
		{
			vecTemp->push_back(ccp(x, y));
			m_vec.push_back(vecTemp);
		}
		else
		{
			float ff = y > 0 ? 150.0f : -150.0f;
			x = ff / (y / x);
			vecTemp->push_back(ccp(x, ff * LUODIANBILI));
			m_vec.push_back(vecTemp);
		}
	}

	DrawNode* pDrawNode = DrawNode::create();
	pDrawNode->setPosition(ccp(272, 54));
	pDrawNode->setDrawPoint(m_vec);
	pDrawNode->setRotation(-90);
	this->addChild(pDrawNode);

    return true;
}