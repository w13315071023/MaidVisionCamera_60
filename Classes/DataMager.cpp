#include "DataMager.h"


DataMager* DataMager::m_pSelf = nullptr;
DataMager* DataMager::shareDataMager()
{
	if (!m_pSelf)
	{
		m_pSelf = new DataMager();
	}
	return m_pSelf;
}
DataMager::DataMager(void)
{
	m_Size = 0;
	//for (size_t i = 0; i < 100; i++)
	//{
	//	m_GolfDataMap[i].gender = GENDER_MAN;
	//	m_GolfDataMap[i].cuetype = CUETYPE_TIEGAN;
	//	m_GolfDataMap[i].velocity = rand() % 30 + 50;
	//	m_GolfDataMap[i].pitch = rand() % 60;
	//	m_GolfDataMap[i].yaw = rand() % 60 - 30;
	//	m_GolfDataMap[i].backspin = 0;
	//	m_GolfDataMap[i].sidespin = 0;
	//	m_GolfDataMap[i].cam_confidence = 0;
	//}

	Document doc;
	if (readValue("GolfData.json", doc))
	{
		for (size_t i = 0; i < doc.Size(); i++)
		{
			m_GolfDataMap[i].gender = (GENDER)doc[i]["gender"].GetInt();
			m_GolfDataMap[i].cuetype = (CUETYPE)doc[i]["cuetype"].GetInt();
			m_GolfDataMap[i].backspin = doc[i]["backspin"].GetDouble();
			m_GolfDataMap[i].sidespin = doc[i]["sidespin"].GetDouble();
			m_GolfDataMap[i].pitch = doc[i]["pitch"].GetDouble();
			m_GolfDataMap[i].yaw = doc[i]["yaw"].GetDouble();
			m_GolfDataMap[i].velocity = doc[i]["velocity"].GetDouble();
			m_GolfDataMap[i].cam_confidence = doc[i]["cam_confidence"].GetDouble();
			m_Size++;
		}
	}
	else
	{
		SaveData();
	}
	//readValue("Setting.json", doc)
}
DataMager::~DataMager(void)
{
}
float DataMager::getVelocity_xById(int id)
{
	return m_GolfDataMap[id].velocity /
		sqrtf(1 +
		tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].yaw))*tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].yaw)) +
		tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].pitch))*tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].pitch)));
}
float DataMager::getVelocity_yById(int id)
{
	return m_GolfDataMap[id].velocity * tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].yaw)) /
		sqrtf(1 +
		tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].yaw)) * tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].yaw)) +
		tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].pitch)) * tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].pitch)));
}
float DataMager::getVelocity_zById(int id)
{
	return m_GolfDataMap[id].velocity * tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].pitch)) /
		sqrtf(1 +
		tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].yaw)) * tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].yaw)) +
		tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].pitch)) * tan(CC_DEGREES_TO_RADIANS(m_GolfDataMap[id].pitch)));
}
//float DataMager::getVelocity_xById(int id)
//{
//	//Vx = cos 仰角 * 初速度
//	return cos(m_GolfDataMap[id].pitch)*sin(m_GolfDataMap[id].yaw)*m_GolfDataMap[id].velocity;
//}
//float DataMager::getVelocity_yById(int id)
//{
//	return cos(m_GolfDataMap[id].pitch)*cos(m_GolfDataMap[id].yaw)*m_GolfDataMap[id].velocity;
//}
//float DataMager::getVelocity_zById(int id)
//{
//	//Vz = sin 仰角 * 初速度
//	return sin(m_GolfDataMap[id].pitch)*m_GolfDataMap[id].velocity;
//}
float DataMager::getTimeById(int id)
{
	return 2 * getVelocity_zById(id) / GRAVITY;
}
//float DataMager::getTimeById(int id)
//{
//	//时间 = 2 * 初速度* sin 仰角/9.8
//	return 2 * m_GolfDataMap[id].velocity*sin(m_GolfDataMap[id].pitch) / GRAVITY;
//}
CUETYPE DataMager::getCueTypeById(int id)
{
	return m_GolfDataMap[id].cuetype;
}
void DataMager::removeDataById(int id)
{

}
int DataMager::size()
{
	return m_GolfDataMap.size();
}
void DataMager::SaveData()
{
	Document::AllocatorType allocator;
	Value array(kArrayType);
	for (size_t i = 0; i < m_GolfDataMap.size(); i++)
	{
		Value object(kObjectType);
		object.AddMember("gender", m_GolfDataMap[i].gender, allocator);
		object.AddMember("cuetype", m_GolfDataMap[i].cuetype, allocator);
		object.AddMember("backspin", m_GolfDataMap[i].backspin, allocator);
		object.AddMember("sidespin", m_GolfDataMap[i].sidespin, allocator);
		object.AddMember("pitch", m_GolfDataMap[i].pitch, allocator);
		object.AddMember("yaw", m_GolfDataMap[i].yaw, allocator);
		object.AddMember("velocity", m_GolfDataMap[i].velocity, allocator);
		object.AddMember("cam_confidence", m_GolfDataMap[i].cam_confidence, allocator);

		array.PushBack(object, allocator);
	}

	saveValue(array, "GolfData.json");
}
void DataMager::clsData()
{
	m_GolfDataMap.clear();
	//this->SaveData();
}
void DataMager::PushData(double backspin, double sidespin, double pitch, double yaw, double velocity, double cam_confidence)
{
	m_GolfDataMap[m_Size].gender = m_curGender;
	m_GolfDataMap[m_Size].cuetype = m_curCuetype;
	m_GolfDataMap[m_Size].backspin = backspin;
	m_GolfDataMap[m_Size].sidespin = sidespin;
	m_GolfDataMap[m_Size].pitch = pitch;
	m_GolfDataMap[m_Size].yaw = yaw;
	m_GolfDataMap[m_Size].velocity = velocity;
	m_GolfDataMap[m_Size].cam_confidence = cam_confidence;
	m_Size++;
}