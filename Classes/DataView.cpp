#include "DataView.h"
#include "DataMager.h"


DataView::DataView(void)
{
}
DataView::~DataView(void)
{
}
bool DataView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->setContentSize(CCSizeMake(1497,869));
	CCSize size = this->getContentSize();
	CCSprite* pBg = CCSprite::create("DataUI/shujuBg.png");
	pBg->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(pBg);

	CCTableView* pTabelView = CCTableView::create(this,CCSizeMake(1400,800));
	pTabelView->setDirection(kCCScrollViewDirectionVertical);
	pTabelView->ignoreAnchorPointForPosition(false);
	pTabelView->setAnchorPoint(ccp(0.5,0.5));
	pTabelView->setPosition(ccp(size.width / 2, size.height / 2));
	pTabelView->setDelegate(this);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(pTabelView);
	pTabelView->reloadData();
	return true;
}
CCTableViewCell* DataView::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	MyTableViewCall* call = (MyTableViewCall*)table->dequeueCell();
	DataMager* pData = DataMager::shareDataMager();
	char name[32];
	if (!call)
	{
		call = new MyTableViewCall();
		call->autorelease();
		CCSprite* pDataOne = CCSprite::create("DataUI/tiaoBg.png");
		pDataOne->setPosition(ccp(700, 45));
		call->addChild(pDataOne);

		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].backspin);
		call->m_pBackspinLabel = CCLabelTTF::create(name, "Arial", 24);

		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].sidespin);
		call->m_pSidespinLabel = CCLabelTTF::create(name, "Arial", 24);

		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].pitch);
		call->m_pPitchLabel = CCLabelTTF::create(name, "Arial", 24);

		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].yaw);
		call->m_pYawLabel = CCLabelTTF::create(name, "Arial", 24);

		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].velocity);
		call->m_pVelocityLabel = CCLabelTTF::create(name, "Arial", 24);

		call->m_pBackspinLabel->setAnchorPoint(ccp(0, 0.5));
		call->m_pSidespinLabel->setAnchorPoint(ccp(0, 0.5));
		call->m_pPitchLabel->setAnchorPoint(ccp(0, 0.5));
		call->m_pYawLabel->setAnchorPoint(ccp(0, 0.5));
		call->m_pVelocityLabel->setAnchorPoint(ccp(0, 0.5));

		call->m_pBackspinLabel->setPosition(ccp(90, 45));
		call->m_pSidespinLabel->setPosition(ccp(390, 45));
		call->m_pPitchLabel->setPosition(ccp(1290, 45));
		call->m_pYawLabel->setPosition(ccp(690, 45));
		call->m_pVelocityLabel->setPosition(ccp(990, 45));

		call->addChild(call->m_pBackspinLabel);
		call->addChild(call->m_pSidespinLabel);
		call->addChild(call->m_pPitchLabel);
		call->addChild(call->m_pYawLabel);
		call->addChild(call->m_pVelocityLabel);
	}
	else
	{
		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].backspin);
		call->m_pBackspinLabel->setString(name);
		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].sidespin);
		call->m_pSidespinLabel->setString(name);
		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].velocity);
		call->m_pPitchLabel->setString(name);
		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].pitch);
		call->m_pYawLabel->setString(name);
		sprintf(name, "%d", (int)pData->m_GolfDataMap[idx].yaw);
		call->m_pVelocityLabel->setString(name);
	}
	return call;
}
unsigned int DataView::numberOfCellsInTableView(CCTableView *table)
{
	return DataMager::shareDataMager()->size();
}
void DataView::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{

}
CCSize DataView::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(1400,90);
}
void DataView::scrollViewDidScroll(CCScrollView* view)
{

}
void DataView::scrollViewDidZoom(CCScrollView* view)
{

}