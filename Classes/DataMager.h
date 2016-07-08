#pragma once
#include "Tools.h"

class DataMager
{
private:
	static DataMager* m_pSelf;
	DataMager(void);
public:
	int m_Size;
	GENDER m_curGender;
	CUETYPE m_curCuetype;
	map<int,GolfData> m_GolfDataMap;
	list<unsigned char*> m_VideoListFront;
	list<unsigned char*> m_VideoListSide;
public:
	~DataMager(void);
	static DataMager* shareDataMager();

	float getVelocity_xById(int id);
	float getVelocity_yById(int id);
	float getVelocity_zById(int id);
	float getTimeById(int id);

	CUETYPE getCueTypeById(int id);
	void removeDataById(int id);

	int size();
	void clsData();
	void SaveData();
	void PushData(double backspin, double sidespin, double pitch, double yaw, double velocity, double cam_confidence);
};

