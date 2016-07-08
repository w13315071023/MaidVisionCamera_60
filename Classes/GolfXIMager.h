#pragma once
#include "Tools.h"
extern "C"
{
#include "golf_sensor_interface.h"
}

static void sendHitResultCommand(TDFlightResults2RH *result);
float RadToDeg(float Angle);
std::string BoolToStr(bool boolTag);
void __stdcall GSIErrorCallback(int tag, const char *text);
void PrintGolfSensorStatus(std::string &memoLines, TGolfSensorStatus *status, bool finalNewLine);
void __stdcall GSIStatusChangeCallback(int tag, TGolfSensorStatus *status);
void __stdcall GSIExtendedStatusCallback(int tag, TGolfSensorExtendedStatus *status);
void __stdcall GSITiltRollCallback(int tag, double tilt, double roll);
void __stdcall GSITrackingStatusChangeCallback(int tag, BOOL tracking, double triggerTime, const char *guid);
void __stdcall GSIRealtimeResultCallback(int tag, TDFlightResults2RH *result, const char *guid);
static double g_Carry;
void __stdcall GSIResultCallback(int tag, TDFlightResults2RH *result, const char *guid);
void __stdcall GSIAVRParamsWrittenCallback(int tag, BOOL successful);
void __stdcall GSIDSPParamsWrittenCallback(int tag, BOOL successful);
void __stdcall GSISamplesAvailableForDownloadCallback(int tag, const char *guid);
void __stdcall GSISampleUploadOrDownloadProgressCallback(int tag,
	float channelPercentage, int currentChannelIndex, int channelCount, const char *guid);
void __stdcall GSISamplesUploadedCallback(int tag, BOOL successful);
void __stdcall GSISamplesDownloadedAndSavedCallback(int tag, BOOL successful, const char *guid);
void __stdcall GSIUDPDiscoveryStartedCallback(int tag);
void __stdcall GSIUDPDiscoveryServiceFoundCallback(int tag, TGolfSensorDiscoverableServiceInfo *serviceInfo,
	const char *discoveryServerIPv4Address);
class GolfXIMager
{
private:
	static GolfXIMager* m_pInstence;
	GolfXIMager();
public:
	int count;
	int gsiInstance;
	bool _callbackDataUpdated;
	float m_curBallSpeed;
	float m_curClubSpeed;
	float m_curVAngle;
	float m_curHAngle;
	float m_curBackSpin;
	float m_curClubYaw;//¸ËÍ·½Ç¶È
	float m_curSideSpin;
	WSADATA data;
	SOCKET sclient;
	static bool m_IsHitBall;
	TGolfSensorExtendedStatus extendedStatus;
	std::vector< std::map<std::string, std::string> > _callbackDataList;
public:
	static GolfXIMager* getInstence();
	~GolfXIMager();
	bool init();
	bool RelevelXI();
	void CloseXI();
	void setClubType(int ClubType);
	void DeviceUpdate();
	void addCallbackData(const std::map<std::string, std::string>& value);
	void takeCallbackDataList(std::vector< std::map<std::string, std::string> >& dataList);
	void clearCallbackData();
	bool hasCallbackData() const;
	void split(const std::string& src, std::vector<std::string>& slist, char sep, bool ignoreEmpty);
};
