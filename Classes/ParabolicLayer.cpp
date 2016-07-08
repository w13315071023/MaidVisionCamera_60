#include "ParabolicLayer.h"
#include "DataMager.h"
#include "DrawNode.h"


ParabolicLayer::ParabolicLayer(void)
{
}


ParabolicLayer::~ParabolicLayer(void)
{
	vector<vector<CCPoint>*> ::iterator iter = m_vec.begin();
	for (iter; iter != m_vec.end(); iter++)
	{
		delete (*iter);
	}
}
bool ParabolicLayer::init()
{
	if (!CCSprite::initWithFile("DataUI/paowutu.png"))
    {
        return false;
    }
	DataMager* pDate = DataMager::shareDataMager();
	for (size_t i = 0; i < pDate->size(); i++)
	{
		vector<CCPoint>* vecTemp = new vector<CCPoint>();
		vecTemp->push_back(ccp(0,0));
		for (size_t Time = 0; Time <= pDate->getTimeById(i)+1; Time++)
		{
			float x = pDate->getVelocity_xById(i) * Time;
			float y = pDate->getVelocity_zById(i) * Time - GRAVITY * Time * Time / 2;

			if (y < 0)
			{
				y = 0;
				x = pDate->getVelocity_xById(i) * pDate->getTimeById(i);
				vecTemp->push_back(ccp(x*PAOWUBILI, y*PAOWUBILI));
				break;
			}
			vecTemp->push_back(ccp(x*PAOWUBILI, y*PAOWUBILI));
		}
		m_vec.push_back(vecTemp);
	}

	DrawNode* pDrawNode = DrawNode::create();
	pDrawNode->setPosition(ccp(54,46));
	pDrawNode->setDrawPoint(m_vec);
	this->addChild(pDrawNode);

    return true;
}
//void ParabolicLayer::draw(void)
//{
//
//}