#pragma once

#include <string>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <thread>
#include "tchar.h"
#include "cocos2d.h"
#include <Windows.h>
#include"cocos-ext.h"
#include "CocoStudio\Json\rapidjson\stringbuffer.h"
#include "CocoStudio\Json\rapidjson\writer.h"
#include "GL\glew.h"
#include "GL\wglew.h"
#include <windows.h>
#include "CameraApi.h"
#include "CameraGrabber.h"
#include <ocidl.h>
#include "CameraImage.h"
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include <libavutil/parseutils.h>
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
}
#pragma comment(lib, "MVCAMSDK.lib")

using namespace std;
using namespace rapidjson;

USING_NS_CC;
USING_NS_CC_EXT;

#define FRONT 15
#define SIDE 16

#define PI 3.1415926535
#define LINEWIDTH 3
#define GRAVITY 9.8
#define VISIBLEW CCDirector::sharedDirector()->getVisibleSize().width
#define VISIBLEH CCDirector::sharedDirector()->getVisibleSize().height
#define BIANKUANG 20
#define LUODIANBILI 1.88
#define PAOWUBILI 2.016
#define BAXINBILI 5.2

extern int instenceTarget;
extern INT	Ext_cameraNum;
extern int Ext_VideoSize;
extern int Ext_VideoSleep;
extern int Ext_SerialThreshold;
extern int Ext_VideoGain;

extern int Ext_VideoExposureTime;
extern float Ext_ToPixels;

extern bool Ext_IsGolfXI;
extern bool Ext_IsResetGG;
extern bool Ext_IsThreadOn;
extern bool Ext_IsRecordBegin;
extern bool Ext_TiaoShi;
extern bool Ext_IsFrontCamera;
extern bool Ext_IsTurnCamera;
extern bool Ext_IsTurnEnd;

enum MENUTAG
{
    MENUTAG_FrontView = 1000,		//正面视图
    MENUTAG_FourView,				//4视图
    MENUTAG_SideView,				//侧面视图
    MENUTAG_FrontAndSide,			//正/侧面视图
	MENUTAG_FrontDemoView,
    MENUTAG_Back,					//返回
    MENUTAG_DataAnalysis,			//数据分析
    MENUTAG_PostureAnalysis,		//姿势分析
};
enum GENDER
{
    GENDER_MAN = 50,
    GENDER_WOMAN,
};
enum CUETYPE
{
    CUETYPE_YIHAOMU = 220,
    CUETYPE_MUGAN = 190,
    CUETYPE_TIEGAN = 140,
    CUETYPE_WAQIGAN = 110,
};
struct ColorPoint
{
    CCPoint pos;
    ccColor4B c4b;
};
struct ColorRect
{
    CCPoint pos1;
    CCPoint pos2;
    ccColor4B c4b;
    ColorRect()
    {
        pos2 = pos1;
    }
};
struct ColorAngle
{
	CCPoint pos1;
	CCPoint pos2;
	CCPoint pos3;
	CCLabelTTF* label;
	float angle;
	ccColor4B c4b;
};
struct ColorCircle
{
    ccColor4B c4b;
    CCPoint center;
    float radius;
    float angle;
    int segments;
    bool drawLineToCenter;
    ColorCircle()
    {
        radius = 0;
        angle = 360;
        segments = 32;
        drawLineToCenter = false;
    }
};
struct VideoRAW
{
	unsigned char* FrameData;
	tSdkFrameHead  FrameHead;
};
struct GolfData
{
	CUETYPE cuetype;
	GENDER gender;
	float target;
	float backspin;			//回旋
	float sidespin;			//侧旋

	float pitch;			//仰角
	float yaw;				//偏角
	float velocity;			//速度

	float cam_confidence;	//
};
class Sender
{
public:
	virtual void Record(bool isRecord) = 0;
	virtual void RecordOk() = 0;
};
class Reseaver
{
public:
	Sender* m_Delegate1 = NULL;
	Sender* m_Delegate2 = NULL;
	void setDelegate1(Sender* del)
	{
		m_Delegate1 = del;
	}
	void setDelegate2(Sender* del)
	{
		m_Delegate2 = del;
	}
};
inline float GetTime(void)
{
	static __int64 start = 0;
	static __int64 frequency = 0;

	if (start == 0)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		return 0.0f;
	}

	__int64 counter = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter);
	return (float)((counter - start) / double(frequency));

}
string GBKToUTF8(const string& strGBK);
bool readValue(const char* pszFileName, Document& value);
void saveValue(rapidjson::Value& root, const char* pszFileName);
