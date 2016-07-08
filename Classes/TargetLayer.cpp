#include "TargetLayer.h"
#include "DataMager.h"
#include "DrawNode.h"


TargetLayer::TargetLayer(void)
{
}
TargetLayer::~TargetLayer(void)
{
	vector<vector<CCPoint>*> ::iterator iter = m_vec.begin();
	for (iter; iter != m_vec.end(); iter++)
	{
		delete (*iter);
	}
}
bool TargetLayer::init()
{
	if (!CCSprite::initWithFile("DataUI/baxinda.png"))
    {
        return false;
    }
	this->setRotation(-90);
	DataMager* pDate = DataMager::shareDataMager();
	for (size_t i = 0; i < pDate->size(); i++)
	{
		float x = pDate->getVelocity_xById(i)*pDate->getTimeById(i) - instenceTarget;
		float y = pDate->getVelocity_yById(i)*pDate->getTimeById(i);
		if (y> - 30 && 
			y< 30 &&
			x > - 30 &&
			x < 30)
		{
			char name[4];
			sprintf(name, "%d", i);
			CCLabelTTF* ttf = CCLabelTTF::create(name, "Arial", 24);
			ttf->setPosition(ccp((x + 30)*5.3, (30 - y)*5.3));
			ttf->setRotation(90);
			this->addChild(ttf);
		}
	}
    return true;
}