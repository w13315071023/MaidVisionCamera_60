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

	typedef bool(*GET_COM)(char**, int&);
	typedef bool(*COM_OFF_ON)(const char*);
	typedef int(*FETCH_MSG)(void);
	typedef void(*SET_THRESHOLD)(int);
	char* com_num;
	bool m_IsCom;
	int m_curMsg;
	GET_COM get_com_port;
	COM_OFF_ON open_com_port;
	FETCH_MSG fetch_msg;
	SET_THRESHOLD set_threshold;
	void unLoadInstence();
	void SeriaUpdate();
	void setThreshold(int threshold);
	bool getComPort();
};