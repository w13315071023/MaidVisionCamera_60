#pragma once
#include "VideoClass.h"
#include "Tools.h"

USING_NS_CC;
class RecordClass;
class MovieVideoLayer :public Sender, public VideoClass 
{
public:
	RecordClass* m_Camera;
	int m_ShowIndex;
	int m_TransIndex;
	static RecordClass* m_Camera1;
	static RecordClass* m_Camera2;
	unsigned char* m_pFrameImageRGB;
	tSdkFrameHead m_FrameImageHead;
public:
	MovieVideoLayer();
	~MovieVideoLayer();
    static MovieVideoLayer* create(int Direction);
	bool init(int Direction);
	void update(float dt);
	void Record(bool isRecord);
	void TransData();
	void RecordOk();
};
