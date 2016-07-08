#include "DrawNode.h"


DrawNode::DrawNode(void)
{
}


DrawNode::~DrawNode(void)
{
}
bool DrawNode::init()
{
	if (!CCNode::init())
	{
		return false;
	}
	return true;
}
void DrawNode::draw(void)
{
	if (m_pVec.empty())
	{
		return;
	}
	//设置绘画时的属性
	ccPointSize(1);
	glLineWidth(1);
	ccDrawColor4B(255, 255, 255, 255);
	//绘制线条
	vector<vector<CCPoint>*> ::iterator iter = m_pVec.begin();
	for (iter; iter != m_pVec.end(); iter++)
	{
		if ((*(*iter)).empty())
		{
			continue;
		}
		if (iter != m_pVec.end()-1)
		{
			ccPointSize(2);
			glLineWidth(2);
			ccDrawColor4B(0, 0, 255, 255);
		}
		else
		{
			ccPointSize(2);
			glLineWidth(2);
			ccDrawColor4B(255, 0, 0, 255);
		}
		vector<CCPoint> ::iterator posIter = (*iter)->begin();
		for (posIter; posIter < (*iter)->end(); posIter++)
		{
			if (posIter == (*iter)->begin())
			{
				ccDrawPoint(*posIter);
			}
			else
			{
				ccDrawLine(*(posIter - 1), *posIter);
			}
		}
	}
}
//加载绘制点数组
void DrawNode::setDrawPoint(vector<vector<CCPoint>*> pVec)
{
	m_pVec = pVec;
}