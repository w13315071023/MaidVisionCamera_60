#ifndef GOLF_SENSOR_INTERFACE
#define GOLF_SENSOR_INTERFACE

#include <windows.h>

#ifndef BOOL
#define BOOL int
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 0xFFFFFFFF
#endif

// Open & close library
BOOL OpenGolfSensorInterface(const char *libraryPath);
void CloseGolfSensorInterface(void);

// Constants

// Firmware applications
#define GSI_FA_UNDEFINED            0
#define GSI_FA_PRE_APP_ID           1
#define GSI_FA_BOOT_MAN             2
#define GSI_FA_FLIGHTSCOPE          3
#define GSI_FA_TBOX                 4
#define GSI_FA_TENNIS               5
#define GSI_FA_TENNIS_SIM           6
#define GSI_FA_CRICKET              7
#define GSI_FA_BASEBALL             8
#define GSI_FA_TILT_CAL             9
#define GSI_FA_PUTT_CAM            10
#define GSI_FA_TRAFFIC             11
#define GSI_FA_FLIGHTSCOPE_TOWARDS 12
#define GSI_FA_LINE_CALL           13
#define GSI_FA_SYNC_HUB            14
#define GSI_FA_TRACKER             15
#define GSI_FA_MILITARY            16
#define GSI_FA_ETHERNET            17
#define GSI_FA_ATHLETICS           18
#define GSI_FA_TBOX_2              19

// Sensor models
#define GSI_SM_UNKNOWN 0
#define GSI_SM_KUDU    1
#define GSI_SM_CHEETAH 2
#define GSI_SM_RHINO   3
#define GSI_SM_PUTT    4
#define GSI_SM_PRIME   5
#define GSI_SM_X1      6
#define GSI_SM_X2      7
#define GSI_SM_XI      8
#define GSI_SM_X1_TBOX 9
#define GSI_SM_X2_1    10
#define GSI_SM_X2_2    11

// Standard detection modes (FlightScope X1 and X2 sensors)
#define GSI_DM_OUTDOOR      8
#define GSI_DM_INDOOR       9
#define GSI_DM_LONG_INDOOR 11

// X1 TBox detection modes
#define GSI_DM_NORMAL         0
#define GSI_DM_CHIP_FAST_PUTT 1
#define GSI_DM_MEDIUM_PUTT    2
#define GSI_DM_SLOW_PUTT      3
#define GSI_DM_TEST_PUTT      4

// Club types
#define GSI_CT_UNSPECIFIED -1
#define GSI_CT_DRIVER       0
#define GSI_CT_IRON         1
#define GSI_CT_WEDGE        2

// Structures

typedef struct
{
  double X, Y, Z;
} TDVector3D;

typedef struct
{
  BOOL Open;
  BOOL Connected;
  BOOL Armed;
  BOOL Sleeping;
  BOOL Leveling;
} TGolfSensorStatus;

#define GSI_INTEROP_STRING_LENGTH 40
#define GSI_INTEROP_LONG_STRING_LENGTH 80

typedef struct
{
  char ServiceName[GSI_INTEROP_STRING_LENGTH];
  char ServiceVersion[GSI_INTEROP_STRING_LENGTH];
  char InstanceName[GSI_INTEROP_STRING_LENGTH];
  char Description[GSI_INTEROP_STRING_LENGTH];
  char Host[GSI_INTEROP_STRING_LENGTH];
  BOOL TCP;
  int Port;
  BOOL IsPublic;
} TGolfSensorDiscoverableServiceInfo;

typedef struct
{
  BOOL Open;
  BOOL Connected;
  BOOL Armed;
  BOOL Sleeping;
  BOOL Leveling;

  BOOL IsOnTCPConnection;

  char FirmwareVersion[GSI_INTEROP_STRING_LENGTH];
  int SensorModel;
  int FirmwareApplication;

  BOOL HasBattery;
  double BatteryPercentageLevel;
  BOOL ExternalPowerConnected;
  BOOL Charging;

  BOOL CanSleep;
  BOOL CanSelfLevel;

  BOOL HasCamera;
  char CameraModel[GSI_INTEROP_STRING_LENGTH];
  double CameraHFOVDeg;
  double CameraHBoresightDeg;
  double CameraVFOVDeg;
  double CameraVBoresightDeg;

  char HardwareID[GSI_INTEROP_STRING_LENGTH];
  int DetectionMode;
  TDVector3D TeePosition;
  BOOL TargetArmed;
  double Altitude;
  int ClubType;
} TGolfSensorExtendedStatus;

typedef struct
{
  int DeviceNumber;
  char DeviceName[GSI_INTEROP_LONG_STRING_LENGTH];
} TGolfSensorCommsDeviceInfo;

// The following two types are misnomers; the number of coefficients is reflected in the name, not the order which is one less
typedef double TD3rdOrderPolynomial[3]; // Parabola
typedef double TD5thOrderPolynomial[5];

#define MAX_CLUB_PRC_POINTS 80

typedef struct
{
  // Time
  double Time;
  double TrackTime;

  // Launch
  double LaunchSpeed;
  double LaunchAzimDeg;
  double LaunchElevDeg;
  TDVector3D StartPosition;

  // Flight & landing
  double CarryDistance;
  double FlightTime;
  double MaxHeight;
  TDVector3D LandingPosition;
  double BackspinRPM;
  double SidespinRPM;
  double RiflespinRPM;
  TDVector3D Reserved;
  TDVector3D LandingVelocity;
  double LandingElevDeg;

  // Roll (and bounce) + final distance
  double TotalDistance;
  double RollDistance;
  TDVector3D FinalPosition;

  // Club + launch
  double Smash;
  double DCOR;

  // Pre club
  double ClubheadSpeed;
  double ClubStrikeDirectionDeg;
  double ClubAttackAngleDeg;

  // Post club & advanced club
  double ClubheadSpeedPost;
  double ClubSwingPlaneTiltDeg;
  double ClubSwingPlaneRotationDeg;
  double ClubEffectiveLoftDeg;
  double ClubFaceAngleDeg;

  // Ball flight trajectory
  TD5thOrderPolynomial PolyX;
  TD5thOrderPolynomial PolyY;
  TD5thOrderPolynomial PolyZ;

  // Club trajectory
  double ClubStartTime;
  double ClubEndTime;
  TD3rdOrderPolynomial ClubPrePolyX; // StartTime..0
  TD3rdOrderPolynomial ClubPrePolyY; // StartTime..0
  TD3rdOrderPolynomial ClubPrePolyZ; // StartTime..0
  TD3rdOrderPolynomial ClubPostPolyX; // 0..EndTime
  TD3rdOrderPolynomial ClubPostPolyY; // 0..EndTime
  TD3rdOrderPolynomial ClubPostPolyZ; // 0..EndTime

  // Club speed profile (NOTE: contains UNFILTERED speed points)
  int ClubSpeedPointCount;
  double ClubSpeedTimes[MAX_CLUB_PRC_POINTS];
  double ClubSpeedValues[MAX_CLUB_PRC_POINTS];
} TDFlightResults2RH;

#define GSI_PARAM_COUNT 34

typedef int TGSIRadarParams[GSI_PARAM_COUNT];

// Callback definitons

// Standard recommended
typedef void (__stdcall *TGSINotifyCallback)(int tag);
typedef void (__stdcall *TGSINotifyGUIDCallback)(int tag, const char *guid);
typedef void (__stdcall *TGSINotifySuccessCallback)(int tag, BOOL successful);

typedef void (__stdcall *TGSIErrorCallback)(int tag, const char *text);
typedef void (__stdcall *TGSIStatusCallback)(int tag, TGolfSensorStatus *status);
typedef void (__stdcall *TGSIExtendedStatusCallback)(int tag, TGolfSensorExtendedStatus *status);
typedef void (__stdcall *TGSITiltRollCallback)(int tag, double tiltDeg, double rollDeg);

typedef void (__stdcall *TGSITrackingStatusCallback)(int tag, BOOL tracking, double triggerTime, const char *guid);
typedef void (__stdcall *TGSIResultCallback)(int tag, TDFlightResults2RH *result, const char *guid);

typedef void (__stdcall *TGSIDynamicParamReadCallback)(int tag, BOOL successful, int paramID, int intValue, double floatValue);

typedef void (__stdcall *TGSIUDPDiscoveryServiceFoundCallback)(int tag, TGolfSensorDiscoverableServiceInfo *serviceInfo,
  const char *discoveryServerIPv4Address);

// Advanced debug
typedef void (__stdcall *TGSISampleUploadOrDownloadProgressCallback)(int tag,
  float channelPercentage, int currentChannelIndex, int channelCount, const char *guid);
typedef void (__stdcall *TGSISamplesDownloadedAndSavedCallback)(int tag, BOOL successful, const char *guid);

// Library procedure definitions

// Standard recommended features
typedef char* (__stdcall *TGSIFileProductVersionProc)(int handle, const char *fileName);
typedef int (__stdcall *TGSINewInstanceProc)(int tag);
typedef void (__stdcall *TGSIDisposeInstanceProc)(int handle);
typedef void (__stdcall *TGSISetTagProc)(int handle, int tag);

typedef int (__stdcall *TGSIScanForCommsDevicesProc)(int handle);
typedef BOOL (__stdcall *TGSIGetCommsDeviceInfoProc)(int handle, TGolfSensorCommsDeviceInfo *deviceInfo, int deviceIndex);

typedef void (__stdcall *TGSISetErrorCallbackProc)(int handle, TGSIErrorCallback callback);
typedef void (__stdcall *TGSISetStatusChangeCallbackProc)(int handle, TGSIStatusCallback callback);
typedef void (__stdcall *TGSISetExtendedStatusCallbackProc)(int handle, TGSIExtendedStatusCallback callback);
typedef void (__stdcall *TGSISetTiltRollCallbackProc)(int handle, TGSITiltRollCallback callback);

typedef void (__stdcall *TGSISetTrackingStatusChangeCallbackProc)(int handle, TGSITrackingStatusCallback callback);
typedef void (__stdcall *TGSISetRealtimeResultCallbackProc)(int handle, TGSIResultCallback callback);
typedef void (__stdcall *TGSISetResultCallbackProc)(int handle, TGSIResultCallback callback);

typedef void (__stdcall *TGSISetAVRDynamicParamReadCallbackProc)(int handle, TGSIDynamicParamReadCallback callback);
typedef void (__stdcall *TGSISetAVRDynamicParamWrittenCallbackProc)(int handle, TGSINotifySuccessCallback callback);
typedef void (__stdcall *TGSISetDSPDynamicParamReadCallbackProc)(int handle, TGSIDynamicParamReadCallback callback);
typedef void (__stdcall *TGSISetDSPDynamicParamWrittenCallbackProc)(int handle, TGSINotifySuccessCallback callback);

typedef void (__stdcall *TGSISetUDPDiscoveryStartedCallbackProc)(int handle, TGSINotifyCallback callback);
typedef void (__stdcall *TGSISetUDPDiscoveryServiceFoundCallbackProc)(int handle, TGSIUDPDiscoveryServiceFoundCallback callback);

typedef BOOL (__stdcall *TGSIOpenUSBProc)(int handle, int deviceNumber);
typedef BOOL (__stdcall *TGSIOpenTCPProc)(int handle, const char *address, unsigned short port);
typedef void (__stdcall *TGSICloseProc)(int handle);

typedef void (__stdcall *TGSISetTargetArmedProc)(int handle, BOOL targetArmed);

typedef void (__stdcall *TGSISetDetectionModeProc)(int handle, int detectionMode);
typedef void (__stdcall *TGSISetTeePositionProc)(int handle, TDVector3D *teePosition);
typedef void (__stdcall *TGSISetAltitudeProc)(int handle, double altitude);
typedef void (__stdcall *TGSISetClubTypeProc)(int handle, int clubType);
typedef void (__stdcall *TGSISetSlowSwingSpeedProc)(int handle, BOOL slowSwingSpeed); // Will soon be deprecated
typedef void (__stdcall *TGSISetNoviceModeProc)(int handle, BOOL slowSwingSpeed); // Beta

typedef void (__stdcall *TGSISleepProc)(int handle);
typedef void (__stdcall *TGSIWakeUpProc)(int handle);
typedef void (__stdcall *TGSIRelevelProc)(int handle);

typedef void (__stdcall *TGSISetTrajectoryProc)(int handle,
  TD5thOrderPolynomial polyX, TD5thOrderPolynomial polyY, TD5thOrderPolynomial polyZ, double flightTime,
  double currentTime);
typedef void (__stdcall *TGSIClearTrajectoryProc)(int handle);
typedef void (__stdcall *TGSIGetCurrentTrajectoryProc)(int handle,
  TD5thOrderPolynomial polyX, TD5thOrderPolynomial polyY, TD5thOrderPolynomial polyZ, double *flightTime,
  double currentTime);

// Debug features
typedef void (__stdcall *TSIStartRecordingProc)(int handle, BOOL waitForTrigger);
typedef void (__stdcall *TSIStopRecordingProc)(int handle, const char *fileName);
typedef void (__stdcall *TSISCancelRecordingOrPlaybackProc)(int handle);
typedef BOOL (__stdcall *TSIPlaybackProc)(int handle, const char *fileName);

// Advanced debug features
typedef void (__stdcall *TGSISetReprocessProc)(int handle, BOOL reprocess);
typedef void (__stdcall *TGSISetExternalBufferSyncProc)(int handle, BOOL externalBufferSync);

typedef void (__stdcall *TGSISetAVRParamsWrittenCallbackProc)(int handle, TGSINotifySuccessCallback callback);
typedef void (__stdcall *TGSISetDSPParamsWrittenCallbackProc)(int handle, TGSINotifySuccessCallback callback);

typedef BOOL (__stdcall *TGSIGetAVRParamsProc)(int handle, TGSIRadarParams *params);
typedef BOOL (__stdcall *TGSISetAVRParamsProc)(int handle, TGSIRadarParams *params);
typedef BOOL (__stdcall *TGSIGetDSPParamsProc)(int handle, TGSIRadarParams *params);
typedef BOOL (__stdcall *TGSISetDSPParamsProc)(int handle, TGSIRadarParams *params);

typedef void (__stdcall *TGSISetSamplesAvailableForDownloadCallbackProc)(int handle, TGSINotifyGUIDCallback callback);
typedef void (__stdcall *TGSISetSampleUploadOrDownloadProgressCallbackProc)(int handle, TGSISampleUploadOrDownloadProgressCallback callback);
typedef void (__stdcall *TGSISetSamplesDownloadedAndSavedCallbackProc)(int handle, TGSISamplesDownloadedAndSavedCallback callback);
typedef void (__stdcall *TGSISetSamplesUploadedCallbackProc)(int handle, TGSINotifySuccessCallback callback);

typedef BOOL (__stdcall *TGSISavePrcInfoToFileProc)(int handle, const char *fileName);
typedef BOOL (__stdcall *TGSISaveClubPrcInfoToFileProc)(int handle, const char *fileName);
typedef BOOL (__stdcall *TGSIDownloadSampleInfoAndSaveToFileProc)(int handle, const char *fileName);
typedef BOOL (__stdcall *TGSIDisarmDownloadSampleInfoAndSaveToFileProc)(int handle, const char *fileName);
typedef BOOL (__stdcall *TGSIUploadSampleInfoProc)(int handle, const char *fileName);
typedef BOOL (__stdcall *TGSICancelUploadOrDownloadProc)(int handle);

// UDP features
typedef BOOL (__stdcall *TGSIUDPDiscoveryStartProc)(int handle, int udpDiscoveryPort);
typedef void (__stdcall *TGSIUDPDiscoveryAddAdvertisedTCPServiceProc)(int handle, const char *serviceName, const char *serviceVersion, int servicePort);
typedef void (__stdcall *TGSIUDPDiscoveryClearAdvertisedServicesProc)(int handle);
typedef BOOL (__stdcall *TGSIUDPDiscoveryFindServicesWithNameProc)(int handle, const char *serviceName);
typedef int (__stdcall *TGSIUDPDiscoveryFoundServiceCountProc)(int handle);
typedef void (__stdcall *TGSIUDPDiscoveryGetServiceInfoProc)(int handle, TGolfSensorDiscoverableServiceInfo *serviceInfo, int serviceIndex);
typedef void (__stdcall *TGSIUDPDiscoveryStopProc)(int handle);

// Library procedure pointer prototypes (declarations in golf_sensor_interface.c)

// Standard recommended features
extern TGSINewInstanceProc GSINewInstance;
extern TGSIDisposeInstanceProc GSIDisposeInstance;
extern TGSISetTagProc GSISetTag;
extern TGSIFileProductVersionProc GSIFileProductVersion;

extern TGSIScanForCommsDevicesProc GSIScanForCommsDevices;
extern TGSIGetCommsDeviceInfoProc GSIGetCommsDeviceInfo;

extern TGSISetErrorCallbackProc GSISetErrorCallback;
extern TGSISetStatusChangeCallbackProc GSISetStatusChangeCallback;
extern TGSISetExtendedStatusCallbackProc GSISetExtendedStatusCallback;
extern TGSISetTiltRollCallbackProc GSISetTiltRollCallback;

extern TGSISetTrackingStatusChangeCallbackProc GSISetTrackingStatusChangeCallback;
extern TGSISetRealtimeResultCallbackProc GSISetRealtimeResultCallback;
extern TGSISetResultCallbackProc GSISetResultCallback;

extern TGSISetAVRDynamicParamReadCallbackProc GSISetAVRDynamicParamReadCallback;
extern TGSISetAVRDynamicParamWrittenCallbackProc GSISetAVRDynamicParamWrittenCallback;
extern TGSISetDSPDynamicParamReadCallbackProc GSISetDSPDynamicParamReadCallback;
extern TGSISetDSPDynamicParamWrittenCallbackProc GSISetDSPDynamicParamWrittenCallback;

extern TGSIOpenUSBProc GSIOpenUSB;
extern TGSIOpenTCPProc GSIOpenTCP;
extern TGSICloseProc GSIClose;

extern TGSISetTargetArmedProc GSISetTargetArmed;

extern TGSISetDetectionModeProc GSISetDetectionMode;
extern TGSISetTeePositionProc GSISetTeePosition;
extern TGSISetAltitudeProc GSISetAltitude;
extern TGSISetClubTypeProc GSISetClubType;
extern TGSISetSlowSwingSpeedProc GSISetSlowSwingSpeed; // Will soon be deprecated
extern TGSISetNoviceModeProc GSISetNoviceMode; // Beta

extern TGSISleepProc GSISleep;
extern TGSIWakeUpProc GSIWakeUp;
extern TGSIRelevelProc GSIRelevel;

extern TGSISetTrajectoryProc GSISetTrajectory;
extern TGSIClearTrajectoryProc GSIClearTrajectory;
extern TGSIGetCurrentTrajectoryProc GSIGetCurrentTrajectory;

// Standard debug features
extern TSIStartRecordingProc GSIStartRecording;
extern TSIStopRecordingProc GSIStopRecording;
extern TSISCancelRecordingOrPlaybackProc GSICancelRecordingOrPlayback;
extern TSIPlaybackProc GSIPlayback;

// Advanced debug features
extern TGSISetReprocessProc GSISetReprocess;
extern TGSISetExternalBufferSyncProc GSISetExternalBufferSync;

extern TGSISetAVRParamsWrittenCallbackProc GSISetAVRParamsWrittenCallback;
extern TGSISetDSPParamsWrittenCallbackProc GSISetDSPParamsWrittenCallback;

extern TGSIGetAVRParamsProc GSIGetAVRParams;
extern TGSISetAVRParamsProc GSISetAVRParams;
extern TGSIGetDSPParamsProc GSIGetDSPParams;
extern TGSISetDSPParamsProc GSISetDSPParams;

extern TGSISetSamplesAvailableForDownloadCallbackProc GSISetSamplesAvailableForDownloadCallback;
extern TGSISetSampleUploadOrDownloadProgressCallbackProc GSISetSampleUploadOrDownloadProgressCallback;
extern TGSISetSamplesDownloadedAndSavedCallbackProc GSISetSamplesDownloadedAndSavedCallback;
extern TGSISetSamplesUploadedCallbackProc GSISetSamplesUploadedCallback;

extern TGSISavePrcInfoToFileProc GSISavePrcInfoToFile;                                         // Must be used inside GSISetSamplesAvailableForDownloadCallback
extern TGSISaveClubPrcInfoToFileProc GSISaveClubPrcInfoToFile;                                 // Must be used inside GSISetSamplesAvailableForDownloadCallback
extern TGSIDownloadSampleInfoAndSaveToFileProc GSIDownloadSampleInfoAndSaveToFile;             // Must be used inside GSISetSamplesAvailableForDownloadCallback
extern TGSIDisarmDownloadSampleInfoAndSaveToFileProc GSIDisarmDownloadSampleInfoAndSaveToFile; // Can be used any time when armed
extern TGSIUploadSampleInfoProc GSIUploadSampleInfo;
extern TGSICancelUploadOrDownloadProc GSICancelUploadOrDownload;

// UDP features
extern TGSIUDPDiscoveryStartProc GSIUDPDiscoveryStart;
extern TGSIUDPDiscoveryAddAdvertisedTCPServiceProc GSIUDPDiscoveryAddAdvertisedTCPService;
extern TGSIUDPDiscoveryClearAdvertisedServicesProc GSIUDPDiscoveryClearAdvertisedServices;
extern TGSIUDPDiscoveryFindServicesWithNameProc GSIUDPDiscoveryFindServicesWithName;
extern TGSIUDPDiscoveryFoundServiceCountProc GSIUDPDiscoveryFoundServiceCount;
extern TGSIUDPDiscoveryGetServiceInfoProc GSIUDPDiscoveryGetServiceInfo;
extern TGSIUDPDiscoveryStopProc GSIUDPDiscoveryStop;
extern TGSISetUDPDiscoveryStartedCallbackProc GSISetUDPDiscoveryStartedCallback;
extern TGSISetUDPDiscoveryServiceFoundCallbackProc GSISetUDPDiscoveryServiceFoundCallback;

double Poly3Eval(TD3rdOrderPolynomial poly, double t);
double Poly5Eval(TD5thOrderPolynomial poly, double t);

#endif // #ifndef GOLF_SENSOR_INTERFACE
