#pragma once

#include "Tools.h"
class MyTableViewCall :public CCTableViewCell
{
public:
	MyTableViewCall(){};
	~MyTableViewCall(){};

	CCLabelTTF* m_pBackspinLabel;
	CCLabelTTF* m_pSidespinLabel;
	CCLabelTTF* m_pVelocityLabel;
	CCLabelTTF* m_pPitchLabel;
	CCLabelTTF* m_pYawLabel;
};

class DataView:public CCLayer,public CCTableViewDataSource,public CCTableViewDelegate
{
public:
	DataView(void);
	~DataView(void);
	CREATE_FUNC(DataView);
	virtual bool init();
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
};

