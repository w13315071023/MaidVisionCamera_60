#pragma once
#include "Tools.h"
#include "PostureAnalysisScene.h"
class SerialMager :public Reseaver
{
private:
	static SerialMager* sInstence;
	SerialMager(void);
public:
	static SerialMager* getInstence();
	~SerialMager(void);
	bool init();

	char* com_num;
	bool m_IsCom;
	int m_curMsg;
	void unLoadInstence();
	void SeriaUpdate();
	void setThreshold(int threshold);
	bool getComPort();
};