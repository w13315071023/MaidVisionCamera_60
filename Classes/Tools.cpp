#include "Tools.h"
#include "GuangGao.h"

extern int instenceTarget = 140;
extern INT	Ext_cameraNum = 0; 
extern bool Ext_IsGolfXI = false;
extern bool Ext_IsResetGG = false;
extern bool Ext_IsThreadOn = false;
extern bool Ext_IsTurnEnd = false;
extern bool Ext_IsRecordBegin = false;
extern int Ext_VideoSize = 0;
extern int Ext_VideoSleep = 1000;
extern int Ext_SerialThreshold = 800;
extern int Ext_VideoGain = 64;
extern int Ext_VideoExposureTime = 15000;
extern float Ext_ToPixels = 0.3;

extern bool Ext_TiaoShi = true;
extern bool Ext_IsFrontCamera = true;
extern bool Ext_IsTurnCamera = false;

string GBKToUTF8(const string& strGBK)
{
	string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}

bool readValue(const char* pszFileName, Document& value)
{
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	path = path + pszFileName;
	unsigned long size;
	char* file = (char*)CCFileUtils::sharedFileUtils()->
		getFileData(path.c_str(), "r", &size);
	if (size == 0)
	{
		return false;
	}
	file[size] = '\0';
	value.Parse<kParseDefaultFlags>(file);
	if (value.HasParseError())
	{
		return false;
	}
	return true;
}
void saveValue(rapidjson::Value& root, const char* pszFileName)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer>writer(buffer);
	root.Accept(writer);
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	path = path + pszFileName;
	FILE* file = fopen(path.c_str(), "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}