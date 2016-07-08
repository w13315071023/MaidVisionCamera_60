#include "GolfXIMager.h"

GolfXIMager::GolfXIMager()
{
}
GolfXIMager::~GolfXIMager()
{
}
GolfXIMager* GolfXIMager::m_pInstence = NULL;
bool GolfXIMager::m_IsHitBall = false;
GolfXIMager* GolfXIMager::getInstence()
{
	if (m_pInstence == NULL)
	{
		m_pInstence = new GolfXIMager();
		if (!m_pInstence->init())
		{
			delete m_pInstence;
			m_pInstence = NULL;
		}
	}
	return m_pInstence;
}
bool GolfXIMager::init()
{
	count = 0;
	gsiInstance = 0;
	std::string fileName = "GolfSensorInterface_v4_7_0_alpha_1.dll";

	if (!OpenGolfSensorInterface(fileName.c_str()))
	{
		CCLog("无法打开雷达的接口信息！");
		return false;
	}
	//7	Creating a Library Instance
	
	gsiInstance = (GSINewInstance != NULL) ? GSINewInstance((int)this) : NULL;
	if (!gsiInstance)
	{
		CCLog("GSINewInstance:bad\n");
		return false;
	}

	//6	Verifying Library Version
	std::string Caption;
	Caption = "GolfSensorInterface Tester (DLL " + std::string(GSIFileProductVersion(gsiInstance, fileName.c_str())) + ")";
	CCLog(Caption.c_str());

	std::string version = std::string(GSIFileProductVersion(gsiInstance, fileName.c_str()));
	if (version == "")
	{
		CCLog("没有找到对应的雷达版本！");
		return false;
	}

	GSISetErrorCallback(gsiInstance, &GSIErrorCallback);
	GSISetStatusChangeCallback(gsiInstance, &GSIStatusChangeCallback);
	GSISetExtendedStatusCallback(gsiInstance, &GSIExtendedStatusCallback);
	GSISetTiltRollCallback(gsiInstance, &GSITiltRollCallback);

	GSISetTrackingStatusChangeCallback(gsiInstance, &GSITrackingStatusChangeCallback);
	GSISetResultCallback(gsiInstance, &GSIResultCallback);
	GSISetRealtimeResultCallback(gsiInstance, &GSIRealtimeResultCallback);

	GSISetAVRParamsWrittenCallback(gsiInstance, &GSIAVRParamsWrittenCallback);
	GSISetDSPParamsWrittenCallback(gsiInstance, &GSIDSPParamsWrittenCallback);

	GSISetSamplesAvailableForDownloadCallback(gsiInstance, &GSISamplesAvailableForDownloadCallback);
	GSISetSampleUploadOrDownloadProgressCallback(gsiInstance, &GSISampleUploadOrDownloadProgressCallback);
	GSISetSamplesUploadedCallback(gsiInstance, &GSISamplesUploadedCallback);
	GSISetSamplesDownloadedAndSavedCallback(gsiInstance, &GSISamplesDownloadedAndSavedCallback);

	GSISetUDPDiscoveryStartedCallback(gsiInstance, &GSIUDPDiscoveryStartedCallback);
	GSISetUDPDiscoveryServiceFoundCallback(gsiInstance, &GSIUDPDiscoveryServiceFoundCallback);

	int deviceCount = -1;
	deviceCount = GSIScanForCommsDevices(gsiInstance);

	if (deviceCount < 0)
	{
		return 0;
	}
	if (GSIOpenTCP(gsiInstance, "192.168.2.1", 5100))
	{
		Ext_IsGolfXI = true;
	}
	else
	{
		Ext_IsGolfXI = false;
	}
	return true;
}
void GolfXIMager::CloseXI()
{
	if (gsiInstance != 0)
	{
		//7、释放
		GSIDisposeInstance(gsiInstance);
		gsiInstance = 0;
	}
	CloseGolfSensorInterface();
}
void GolfXIMager::DeviceUpdate()
{
	if (true)
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	//消息处理
	if (this->hasCallbackData())
	{
		std::vector<std::map<std::string, std::string>> list;
		this->takeCallbackDataList(list);

		//记录雷达输出的必要信息

		for (unsigned int i = 0; i < list.size(); i++)
		{
			//分拣名称
			auto it = list[i].find("name");
			if (it != list[i].end())
			{
				//处理击球结果
				if (it->second == "hit_ball")
				{
					for (auto it2 = list[i].begin(); it2 != list[i].end(); it2++)
					{
						CCLog("-- %s %s\n", it2->first.c_str(), it2->second.c_str());
						if (it2->first == "oriented_speed")
						{
							std::vector<std::string> nameDataList;
							split(it2->second, nameDataList, ' ', true);

							m_curBallSpeed = atof(nameDataList[0].c_str())*Ext_ToPixels;
							m_curHAngle = atof(nameDataList[1].c_str());
							m_curVAngle = atof(nameDataList[2].c_str());

							m_curBallSpeed = m_curBallSpeed * 3.6;//公里每小时
							//球速 velocity = 6.78
							printf("球速 = %f\n", m_curBallSpeed);
							printf("仰角 = %f\n", m_curVAngle);
							printf("偏角 = %f\n", m_curHAngle);
						}
						if (it2->first == "angular_rpm")
						{
							std::vector<std::string> nameDataList;
							split(it2->second, nameDataList, ' ', true);
							m_curBackSpin = atof(nameDataList[1].c_str());
							m_curSideSpin = atof(nameDataList[2].c_str());

							printf("回旋 = %f\n", m_curBackSpin);
							printf("侧旋 = %f\n", m_curSideSpin);
						}
						if (it2->first == "club_msg")
						{
							std::vector<std::string> nameDataList;
							split(it2->second, nameDataList, ' ', true);

							m_curClubYaw = atof(nameDataList[0].c_str())* Ext_ToPixels;
							m_curClubSpeed = atof(nameDataList[1].c_str())* Ext_ToPixels;

							printf("杆速 = %f\n", m_curClubSpeed);
						}
					}
					m_IsHitBall = true;
				}
			}
		}
	}
}
void GolfXIMager::setClubType(int ClubType)
{
	if (Ext_IsGolfXI)
	{
		GSISetClubType(gsiInstance, GSI_CT_IRON);
		GSIRelevel(gsiInstance);
	}
}
bool GolfXIMager::RelevelXI()
{
	count++;
	if (count == 3)
	{
		GSIRelevel(gsiInstance);
	}
	else if (count == 310)
	{
		GSISetTargetArmed(gsiInstance, true);
	}
	else if (count == 420)
	{
		GSIRelevel(gsiInstance);
	}
	else if (count == 480)
	{
		GSISetDetectionMode(gsiInstance, GSI_DM_INDOOR);
	}
	else if (count > 485)
	{
		return true;
	}
	return false;
}
void GolfXIMager::addCallbackData(const std::map<std::string, std::string>& value)
{
	_callbackDataList.push_back(value);
	_callbackDataUpdated = true;
}

void GolfXIMager::takeCallbackDataList(std::vector< std::map<std::string, std::string> >& dataList)
{
	dataList.swap(_callbackDataList);
	_callbackDataUpdated = false;
}
void GolfXIMager::clearCallbackData()
{
	_callbackDataList.clear();
}
bool GolfXIMager::hasCallbackData() const
{
	return _callbackDataUpdated;
}
void GolfXIMager::split(const std::string& src, std::vector<std::string>& slist, char sep, bool ignoreEmpty)
{
	if (src.empty()) return;

	std::string::size_type start = src.find_first_not_of(sep);
	while (start != std::string::npos)
	{
		std::string::size_type end = src.find_first_of(sep, start);
		if (end != std::string::npos)
		{
			slist.push_back(std::string(src, start, end - start));
			if (ignoreEmpty) start = src.find_first_not_of(sep, end);
			else start = end + 1;
		}
		else
		{
			slist.push_back(std::string(src, start, src.size() - start));
			start = end;
		}
	}
}

void __stdcall GSIErrorCallback(int tag, const char *text)
{
	std::cout << "Error text: " << text << std::endl;
	std::cout << "" << std::endl;
}

void PrintGolfSensorStatus(std::string &memoLines, TGolfSensorStatus *status, bool finalNewLine)
{
	std::cout << "Open: " << BoolToStr(status->Open) << std::endl;
	std::cout << "Connected: " << BoolToStr(status->Connected) << std::endl;
	std::cout << "Armed: " << BoolToStr(status->Armed) << std::endl;
	std::cout << "Sleeping: " << BoolToStr(status->Sleeping) << std::endl;
	std::cout << "Leveling: " << BoolToStr(status->Leveling) << std::endl;
	if (finalNewLine)
		std::cout << " " << std::endl;
}

void __stdcall GSIStatusChangeCallback(int tag, TGolfSensorStatus *status)
{
	// Because the first couple of fields of TGolfSensorStatus and TGolfSensorExtendedStatus are identical,
	// we simply copy over using a cast trick
	//*(TGolfSensorStatus*)(&mainForm->extendedStatus) = *status;
	*(TGolfSensorStatus*)(&GolfXIMager::getInstence()->extendedStatus) = *status;
	std::string lines;
	PrintGolfSensorStatus(lines, status, true);
}

void __stdcall GSIExtendedStatusCallback(int tag, TGolfSensorExtendedStatus *status)
{
	GolfXIMager::getInstence()->extendedStatus = *status;
	std::string memoLines;
	PrintGolfSensorStatus(memoLines, (TGolfSensorStatus*)status, false);

	std::cout << "IsOnTCPConnection: " << status->IsOnTCPConnection << std::endl;
	std::cout << "FirmwareVersion: " << status->FirmwareVersion << std::endl;
	std::cout << "SensorModel: " << status->SensorModel << std::endl;
	std::cout << "FirmwareApplication: " << status->FirmwareApplication << std::endl;
	std::cout << "HasBattery: " << BoolToStr(status->HasBattery) << std::endl;
	std::cout << "BatteryPercentageLevel: " << status->BatteryPercentageLevel << std::endl;
	std::cout << "ExternalPowerConnected: " << BoolToStr(status->ExternalPowerConnected) << std::endl;
	std::cout << "Charging: " << BoolToStr(status->Charging) << std::endl;
	std::cout << "CanSleep: " << BoolToStr(status->CanSleep) << std::endl;
	std::cout << "CanSelfLevel: " << BoolToStr(status->CanSelfLevel) << std::endl;
	std::cout << "HasCamera: " << BoolToStr(status->HasCamera) << std::endl;
	std::cout << "CameraModel: " << status->CameraModel << std::endl;
	std::cout << "CameraHFOVDeg: " << status->CameraHFOVDeg << std::endl;
	std::cout << "CameraHBoresightDeg: " << status->CameraHBoresightDeg << std::endl;
	std::cout << "CameraVFOVDeg: " << status->CameraVFOVDeg << std::endl;
	std::cout << "CameraVBoresightDeg: " << status->CameraVBoresightDeg << std::endl;
	std::cout << "HardwareID: " << status->HardwareID << std::endl;
	std::cout << "DetectionMode: " << status->DetectionMode << std::endl;
	std::cout << "TeePosition: "
		<< status->TeePosition.X << ", "
		<< status->TeePosition.Y << ", "
		<< status->TeePosition.Z << std::endl;
	std::cout << "TargetArmed: " << BoolToStr(status->TargetArmed) << std::endl;
	std::cout << "Altitude: " << status->Altitude << std::endl;
	std::cout << "ClubType: " << status->ClubType << std::endl;
	std::cout << "" << std::endl;
}

void __stdcall GSITiltRollCallback(int tag, double tilt, double roll)
{
	return;
}

void __stdcall GSITrackingStatusChangeCallback(int tag, BOOL tracking, double triggerTime, const char *guid)
{
	if (tracking)
	{
		std::cout << "Tracking: " << tracking << " ("
			<< triggerTime << ") - " << guid << std::endl; //tracking, true)
	}
	else
		std::cout << "Tracking: " << tracking << " - " << guid << std::endl;
	std::cout << " " << std::endl;
}

void __stdcall GSIRealtimeResultCallback(int tag, TDFlightResults2RH *result, const char *guid)
{
	std::cout << "Realtime result: Time = " << result->Time << " s - " << guid << std::endl;
	std::cout << "Realtime result: FlightTime = " << result->FlightTime << " s" << std::endl;
	//其他信息
	std::cout << "Realtime Result: 球速 " << result->LaunchSpeed << std::endl;
	std::cout << "Realtime Result: 杆速 " << result->ClubheadSpeed << std::endl;
	std::cout << "Realtime Result: 杆角度 " << result->ClubFaceAngleDeg << std::endl;
}

void __stdcall GSIResultCallback(int tag, TDFlightResults2RH *result, const char *guid)
{
	std::cout << "Result: Time = " << result->Time << " s - " << guid << std::endl;
	std::cout << "Result: FlightTime = " << result->FlightTime << " s" << std::endl;
	std::cout << "Result: Carry = " << result->CarryDistance << " m" << std::endl;
	g_Carry = result->CarryDistance;

	//if(!(result->BackspinRPM) && !(result->SidespinRPM))
	{
		std::cout << "BackspinRPM is " << result->BackspinRPM << " SidespinRPM is " << result->SidespinRPM << std::endl;

		std::cout << "Result: Total spin = " << sqrt((result->BackspinRPM*result->BackspinRPM) + (result->SidespinRPM*result->SidespinRPM))
			<< " rpm" << std::endl;
		std::cout << "Result: Spin axis = " << RadToDeg(atan2(result->SidespinRPM, result->BackspinRPM))
			<< "?);" << std::endl;
	}
	std::cout << "Result: ClubSpeedPointCount = " << result->ClubSpeedPointCount << std::endl;
	std::cout << " " << std::endl;

	//其他信息
	std::cout << "Result: 球速 " << result->LaunchSpeed << std::endl;
	std::cout << "Result: 杆速 " << result->ClubheadSpeed << std::endl;
	std::cout << "Result: 杆角度 " << result->ClubFaceAngleDeg << std::endl;

	sendHitResultCommand(result);
}

void __stdcall GSIAVRParamsWrittenCallback(int tag, BOOL successful)
{
	if (successful)
		std::cout << "AVR params successfully written" << std::endl;
	else
		std::cout << "AVR params write failed" << std::endl;
	std::cout << "" << std::endl;
}

void __stdcall GSIDSPParamsWrittenCallback(int tag, BOOL successful)
{
	if (successful)
		std::cout << "DSP params successfully written" << std::endl;
	else
		std::cout << "DSP params write failed" << std::endl;
	std::cout << "" << std::endl;
}

void __stdcall GSISamplesAvailableForDownloadCallback(int tag, const char *guid)
{
	std::cout << "调用 GSISamplesAvailableForDownloadCallback " << std::endl;
}

void __stdcall GSISampleUploadOrDownloadProgressCallback(int tag,
	float channelPercentage, int currentChannelIndex, int channelCount, const char *guid)
{
	std::cout << "调用 GSISamplesUploadedCallback 刷新？ ProgressForm->Hide() " << std::endl;
}

void __stdcall GSISamplesUploadedCallback(int tag, BOOL successful)
{
	std::cout << "调用 GSISamplesUploadedCallback 刷新？ ProgressForm->Hide() " << std::endl;
}

void __stdcall GSISamplesDownloadedAndSavedCallback(int tag, BOOL successful, const char *guid)
{
	std::cout << "调用 GSISamplesDownloadedAndSavedCallback 刷新？ ProgressForm->Hide() " << std::endl;
}

void __stdcall GSIUDPDiscoveryStartedCallback(int tag)
{
	std::cout << "调用 GSIUDPDiscoveryStartedCallback" << std::endl;
}

void __stdcall GSIUDPDiscoveryServiceFoundCallback(int tag, TGolfSensorDiscoverableServiceInfo *serviceInfo,
	const char *discoveryServerIPv4Address)
{
	std::cout << "调用 GSIUDPDiscoveryServiceFoundCallback" << std::endl;
}

void sendHitResultCommand(TDFlightResults2RH *result)
{
	std::map<std::string, std::string> jsonData;
	jsonData["name"] = "hit_ball";

	std::stringstream ss;
	ss << result->LaunchSpeed << " " << result->LaunchAzimDeg//-inDegrees(r->HorzAngle)
		<< " " << result->LaunchElevDeg;//inDegrees(r->VertAngle);
	jsonData["oriented_speed"] = ss.str();

	ss.str("");
	ss << "0.0 " << result->BackspinRPM << " " << result->SidespinRPM;
	jsonData["angular_rpm"] = ss.str();

	ss.str("");
	ss << result->ClubStrikeDirectionDeg << " " << result->ClubheadSpeed << " " << "0.0";
	jsonData["club_msg"] = ss.str();

	if (GolfXIMager::getInstence())
		GolfXIMager::getInstence()->addCallbackData(jsonData);
}

float RadToDeg(float Angle)
{
	return (Angle * 180) / PI;
}

std::string BoolToStr(bool boolTag)
{
	if (boolTag)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}
