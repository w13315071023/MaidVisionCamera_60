#include "golf_sensor_interface.h"

void *LibHandle = NULL;

// Library procedure pointers

TGSINewInstanceProc GSINewInstance;
TGSIDisposeInstanceProc GSIDisposeInstance;
TGSISetTagProc GSISetTag;
TGSIFileProductVersionProc GSIFileProductVersion;

TGSIScanForCommsDevicesProc GSIScanForCommsDevices;
TGSIGetCommsDeviceInfoProc GSIGetCommsDeviceInfo;

TGSISetErrorCallbackProc GSISetErrorCallback;
TGSISetStatusChangeCallbackProc GSISetStatusChangeCallback;
TGSISetExtendedStatusCallbackProc GSISetExtendedStatusCallback;
TGSISetTiltRollCallbackProc GSISetTiltRollCallback;

TGSISetTrackingStatusChangeCallbackProc GSISetTrackingStatusChangeCallback;
TGSISetRealtimeResultCallbackProc GSISetRealtimeResultCallback;
TGSISetResultCallbackProc GSISetResultCallback;

TGSISetAVRDynamicParamReadCallbackProc GSISetAVRDynamicParamReadCallback;
TGSISetAVRDynamicParamWrittenCallbackProc GSISetAVRDynamicParamWrittenCallback;
TGSISetDSPDynamicParamReadCallbackProc GSISetDSPDynamicParamReadCallback;
TGSISetDSPDynamicParamWrittenCallbackProc GSISetDSPDynamicParamWrittenCallback;

TGSIOpenUSBProc GSIOpenUSB;
TGSIOpenTCPProc GSIOpenTCP;
TGSICloseProc GSIClose;

TGSISetTargetArmedProc GSISetTargetArmed;

TGSISetDetectionModeProc GSISetDetectionMode;
TGSISetTeePositionProc GSISetTeePosition;
TGSISetAltitudeProc GSISetAltitude;
TGSISetClubTypeProc GSISetClubType;

TGSISleepProc GSISleep;
TGSIWakeUpProc GSIWakeUp;
TGSIRelevelProc GSIRelevel;

TGSISetTrajectoryProc GSISetTrajectory;
TGSIClearTrajectoryProc GSIClearTrajectory;
TGSIGetCurrentTrajectoryProc GSIGetCurrentTrajectory;

TSIStartRecordingProc GSIStartRecording;
TSIStopRecordingProc GSIStopRecording;
TSISCancelRecordingOrPlaybackProc GSICancelRecordingOrPlayback;
TSIPlaybackProc GSIPlayback;

TGSISetReprocessProc GSISetReprocess;
TGSISetExternalBufferSyncProc GSISetExternalBufferSync;
TGSISetSlowSwingSpeedProc GSISetSlowSwingSpeed; // Will soon be deprecated
TGSISetNoviceModeProc GSISetNoviceMode; // Beta

TGSISetAVRParamsWrittenCallbackProc GSISetAVRParamsWrittenCallback;
TGSISetDSPParamsWrittenCallbackProc GSISetDSPParamsWrittenCallback;

TGSIGetAVRParamsProc GSIGetAVRParams;
TGSISetAVRParamsProc GSISetAVRParams;
TGSIGetDSPParamsProc GSIGetDSPParams;
TGSISetDSPParamsProc GSISetDSPParams;

TGSISetSamplesAvailableForDownloadCallbackProc GSISetSamplesAvailableForDownloadCallback;
TGSISetSampleUploadOrDownloadProgressCallbackProc GSISetSampleUploadOrDownloadProgressCallback;
TGSISetSamplesDownloadedAndSavedCallbackProc GSISetSamplesDownloadedAndSavedCallback;
TGSISetSamplesUploadedCallbackProc GSISetSamplesUploadedCallback;

TGSISavePrcInfoToFileProc GSISavePrcInfoToFile;
TGSISaveClubPrcInfoToFileProc GSISaveClubPrcInfoToFile;
TGSIDownloadSampleInfoAndSaveToFileProc GSIDownloadSampleInfoAndSaveToFile;
TGSIDisarmDownloadSampleInfoAndSaveToFileProc GSIDisarmDownloadSampleInfoAndSaveToFile;
TGSIUploadSampleInfoProc GSIUploadSampleInfo;
TGSICancelUploadOrDownloadProc GSICancelUploadOrDownload;

TGSIUDPDiscoveryStartProc GSIUDPDiscoveryStart;
TGSIUDPDiscoveryAddAdvertisedTCPServiceProc GSIUDPDiscoveryAddAdvertisedTCPService;
TGSIUDPDiscoveryClearAdvertisedServicesProc GSIUDPDiscoveryClearAdvertisedServices;
TGSIUDPDiscoveryFindServicesWithNameProc GSIUDPDiscoveryFindServicesWithName;
TGSIUDPDiscoveryFoundServiceCountProc GSIUDPDiscoveryFoundServiceCount;
TGSIUDPDiscoveryGetServiceInfoProc GSIUDPDiscoveryGetServiceInfo;
TGSIUDPDiscoveryStopProc GSIUDPDiscoveryStop;

TGSISetUDPDiscoveryStartedCallbackProc GSISetUDPDiscoveryStartedCallback;
TGSISetUDPDiscoveryServiceFoundCallbackProc GSISetUDPDiscoveryServiceFoundCallback;

BOOL OpenGolfSensorInterface(const char *libraryPath)
{
  BOOL successful = FALSE;

  LibHandle = LoadLibraryA(libraryPath);

  if (LibHandle == NULL)
    return FALSE;

  do
  {
    // Instance creation and file version
    GSINewInstance = (TGSINewInstanceProc)GetProcAddress(LibHandle, "NewInstance");
    GSIDisposeInstance = (TGSIDisposeInstanceProc)GetProcAddress(LibHandle, "DisposeInstance");
    GSISetTag = (TGSISetTagProc)GetProcAddress(LibHandle, "SetTag");
    GSIFileProductVersion = (TGSIFileProductVersionProc)GetProcAddress(LibHandle, "FileProductVersion");
    if ((GSINewInstance == NULL) || (GSIDisposeInstance == NULL) || (GSISetTag == NULL))
      break;

    // Listing USB comms devices
    GSIScanForCommsDevices = (TGSIScanForCommsDevicesProc)GetProcAddress(LibHandle, "ScanForCommsDevices");
    GSIGetCommsDeviceInfo = (TGSIGetCommsDeviceInfoProc)GetProcAddress(LibHandle, "GetCommsDeviceInfo");
    if ((GSIScanForCommsDevices == NULL) || (GSIGetCommsDeviceInfo == NULL))
      break;

    // Setting general callbacks
    GSISetErrorCallback = (TGSISetErrorCallbackProc)GetProcAddress(LibHandle, "SetErrorCallback");
    GSISetStatusChangeCallback = (TGSISetStatusChangeCallbackProc)GetProcAddress(LibHandle, "SetStatusChangeCallback");
    GSISetExtendedStatusCallback = (TGSISetExtendedStatusCallbackProc)GetProcAddress(LibHandle, "SetExtendedStatusCallback");
    GSISetTiltRollCallback = (TGSISetTiltRollCallbackProc)GetProcAddress(LibHandle, "SetTiltRollCallback");
    if ((GSISetErrorCallback == NULL) || (GSISetStatusChangeCallback == NULL)
      || (GSISetExtendedStatusCallback == NULL) || (GSISetTiltRollCallback == NULL))
    {
      break;
    }

    // Setting trigger & result callbacks
    GSISetTrackingStatusChangeCallback = (TGSISetTrackingStatusChangeCallbackProc)GetProcAddress(LibHandle, "SetTrackingStatusChangeCallback");
    GSISetRealtimeResultCallback = (TGSISetRealtimeResultCallbackProc)GetProcAddress(LibHandle, "SetRealtimeResultCallback");
    GSISetResultCallback = (TGSISetResultCallbackProc)GetProcAddress(LibHandle, "SetResultCallback");
    if ((GSISetTrackingStatusChangeCallback == NULL) || (GSISetRealtimeResultCallback == NULL) || (GSISetResultCallback == NULL))
      break;

    // Setting dynamic parameter callbacks
    GSISetAVRDynamicParamReadCallback = (TGSISetAVRDynamicParamReadCallbackProc)GetProcAddress(LibHandle, "SetAVRDynamicParamReadCallback");
    GSISetAVRDynamicParamWrittenCallback = (TGSISetAVRDynamicParamWrittenCallbackProc)GetProcAddress(LibHandle, "SetAVRDynamicParamWrittenCallback");
    GSISetDSPDynamicParamReadCallback = (TGSISetDSPDynamicParamReadCallbackProc)GetProcAddress(LibHandle, "SetDSPDynamicParamReadCallback");
    GSISetDSPDynamicParamWrittenCallback = (TGSISetDSPDynamicParamWrittenCallbackProc)GetProcAddress(LibHandle, "SetDSPDynamicParamWrittenCallback");
    if ((GSISetAVRDynamicParamReadCallback == NULL) || (GSISetAVRDynamicParamWrittenCallback == NULL)
      || (GSISetDSPDynamicParamReadCallback == NULL) || (GSISetDSPDynamicParamWrittenCallback == NULL))
    {
      break;
    }

    // Opening and closing connections
    GSIOpenUSB = (TGSIOpenUSBProc)GetProcAddress(LibHandle, "OpenUSB");
    GSIOpenTCP = (TGSIOpenTCPProc)GetProcAddress(LibHandle, "OpenTCP");
    GSIClose = (TGSICloseProc)GetProcAddress(LibHandle, "Close");
    if ((GSIOpenUSB == NULL) || (GSIOpenTCP == NULL) || (GSIClose == NULL))
      break;

    // Target armed
    GSISetTargetArmed = (TGSISetTargetArmedProc)GetProcAddress(LibHandle, "SetTargetArmed");
    if (GSISetTargetArmed == NULL)
      break;

    // Setup
    GSISetDetectionMode = (TGSISetDetectionModeProc)GetProcAddress(LibHandle, "SetDetectionMode");
    GSISetTeePosition = (TGSISetTeePositionProc)GetProcAddress(LibHandle, "SetTeePosition");
    GSISetAltitude = (TGSISetAltitudeProc)GetProcAddress(LibHandle, "SetAltitude");
    GSISetClubType = (TGSISetClubTypeProc)GetProcAddress(LibHandle, "SetClubType");
    if ((GSISetDetectionMode == NULL) || (GSISetTeePosition == NULL)
      || (GSISetAltitude == NULL) || (GSISetClubType == NULL))
    {
      break;
    }

    // Sleep, wake up, relevel
    GSISleep = (TGSISleepProc)GetProcAddress(LibHandle, "Sleep");
    GSIWakeUp = (TGSIWakeUpProc)GetProcAddress(LibHandle, "WakeUp");
    GSIRelevel = (TGSIRelevelProc)GetProcAddress(LibHandle, "Relevel");
    if ((GSISleep == NULL) || (GSIWakeUp == NULL) || (GSIRelevel == NULL))
    {
      break;
    }

    GSISetTrajectory = (TGSISetTrajectoryProc)GetProcAddress(LibHandle, "SetTrajectory");
    GSIClearTrajectory = (TGSIClearTrajectoryProc)GetProcAddress(LibHandle, "ClearTrajectory");
    GSIGetCurrentTrajectory = (TGSIGetCurrentTrajectoryProc)GetProcAddress(LibHandle, "GetCurrentTrajectory");
    if ((GSISetTrajectory == NULL) || (GSIClearTrajectory == NULL) || (GSIGetCurrentTrajectory == NULL))
    {
      break;
    }

    // Debug features
    GSIStartRecording = (TSIStartRecordingProc)GetProcAddress(LibHandle, "StartRecording");
    GSIStopRecording = (TSIStopRecordingProc)GetProcAddress(LibHandle, "StopRecording");
    GSICancelRecordingOrPlayback = (TSISCancelRecordingOrPlaybackProc)GetProcAddress(LibHandle, "CancelRecordingOrPlayback");
    GSIPlayback = (TSIPlaybackProc)GetProcAddress(LibHandle, "Playback");
    if ((GSIStartRecording == NULL) || (GSIStopRecording == NULL)
      || (GSICancelRecordingOrPlayback == NULL) || (GSIPlayback == NULL))
    {
      break;
    }

    // Advanced debug features
    GSISetReprocess = (TGSISetReprocessProc)GetProcAddress(LibHandle, "SetReprocess");
    GSISetExternalBufferSync = (TGSISetExternalBufferSyncProc)GetProcAddress(LibHandle, "SetExternalBufferSync");
    GSISetSlowSwingSpeed = (TGSISetSlowSwingSpeedProc)GetProcAddress(LibHandle, "SetSlowSwingSpeed");
    GSISetNoviceMode = (TGSISetNoviceModeProc)GetProcAddress(LibHandle, "SetNoviceMode");
    if ((GSISetReprocess == NULL) || (GSISetExternalBufferSync == NULL)
      || (GSISetSlowSwingSpeed == NULL) || GSISetNoviceMode == NULL)
      break;

    GSISetAVRParamsWrittenCallback = (TGSISetAVRParamsWrittenCallbackProc)GetProcAddress(LibHandle, "SetAVRParamsWrittenCallback");
    GSISetDSPParamsWrittenCallback = (TGSISetDSPParamsWrittenCallbackProc)GetProcAddress(LibHandle, "SetDSPParamsWrittenCallback");
    if ((GSISetAVRParamsWrittenCallback == NULL) || (GSISetDSPParamsWrittenCallback == NULL))
      break;

    GSIGetAVRParams = (TGSIGetAVRParamsProc)GetProcAddress(LibHandle, "GetAVRParams");
    GSISetAVRParams = (TGSISetAVRParamsProc)GetProcAddress(LibHandle, "SetAVRParams");
    GSIGetDSPParams = (TGSIGetDSPParamsProc)GetProcAddress(LibHandle, "GetDSPParams");
    GSISetDSPParams = (TGSISetDSPParamsProc)GetProcAddress(LibHandle, "SetDSPParams");
    if ((GSIGetAVRParams == NULL) || (GSISetAVRParams == NULL)
      || (GSIGetDSPParams == NULL) || (GSISetDSPParams == NULL))
    {
      break;
    }

    GSISetSamplesAvailableForDownloadCallback = (TGSISetSamplesAvailableForDownloadCallbackProc)GetProcAddress(LibHandle, "SetSamplesAvailableForDownloadCallback");
    GSISetSampleUploadOrDownloadProgressCallback = (TGSISetSampleUploadOrDownloadProgressCallbackProc)GetProcAddress(LibHandle, "SetSampleUploadOrDownloadProgressCallback");
    GSISetSamplesDownloadedAndSavedCallback = (TGSISetSamplesDownloadedAndSavedCallbackProc)GetProcAddress(LibHandle, "SetSamplesDownloadedAndSavedCallback");
    GSISetSamplesUploadedCallback = (TGSISetSamplesUploadedCallbackProc)GetProcAddress(LibHandle, "SetSamplesUploadedCallback");
    if ((GSISetSamplesAvailableForDownloadCallback == NULL) || (GSISetSampleUploadOrDownloadProgressCallback == NULL)
      || (GSISetSamplesDownloadedAndSavedCallback == NULL) || (GSISetSamplesUploadedCallback == NULL))
    {
      break;
    }

    GSISavePrcInfoToFile = (TGSISavePrcInfoToFileProc)GetProcAddress(LibHandle, "SavePrcInfoToFile");
    GSISaveClubPrcInfoToFile = (TGSISaveClubPrcInfoToFileProc)GetProcAddress(LibHandle, "SaveClubPrcInfoToFile");
    GSIDownloadSampleInfoAndSaveToFile = (TGSIDownloadSampleInfoAndSaveToFileProc)GetProcAddress(LibHandle, "DownloadSampleInfoAndSaveToFile");
    GSIDisarmDownloadSampleInfoAndSaveToFile = (TGSIDisarmDownloadSampleInfoAndSaveToFileProc)GetProcAddress(LibHandle, "DisarmDownloadSampleInfoAndSaveToFile");
    GSIUploadSampleInfo = (TGSIUploadSampleInfoProc)GetProcAddress(LibHandle, "UploadSampleInfo");
    GSICancelUploadOrDownload = (TGSICancelUploadOrDownloadProc)GetProcAddress(LibHandle, "CancelUploadOrDownload");
    if ((GSISavePrcInfoToFile == NULL) || (GSISaveClubPrcInfoToFile == NULL) || (GSIDownloadSampleInfoAndSaveToFile == NULL)
      || (GSIDisarmDownloadSampleInfoAndSaveToFile == NULL))
    {
      break;
    }

    // UDP features
    GSIUDPDiscoveryStart = (TGSIUDPDiscoveryStartProc)GetProcAddress(LibHandle, "UDPDiscoveryStart");
    GSIUDPDiscoveryAddAdvertisedTCPService = (TGSIUDPDiscoveryAddAdvertisedTCPServiceProc)GetProcAddress(LibHandle,
      "UDPDiscoveryAddAdvertisedTCPService");
    GSIUDPDiscoveryClearAdvertisedServices = (TGSIUDPDiscoveryClearAdvertisedServicesProc)GetProcAddress(LibHandle,
      "UDPDiscoveryClearAdvertisedServices");
    GSIUDPDiscoveryFindServicesWithName = (TGSIUDPDiscoveryFindServicesWithNameProc)GetProcAddress(LibHandle, "UDPDiscoveryFindServicesWithName");
    GSIUDPDiscoveryFoundServiceCount = (TGSIUDPDiscoveryFoundServiceCountProc)GetProcAddress(LibHandle, "UDPDiscoveryFoundServiceCount");
    GSIUDPDiscoveryGetServiceInfo = (TGSIUDPDiscoveryGetServiceInfoProc)GetProcAddress(LibHandle, "UDPDiscoveryGetServiceInfo");
    GSIUDPDiscoveryStop = (TGSIUDPDiscoveryStopProc)GetProcAddress(LibHandle, "UDPDiscoveryStop");
    GSISetUDPDiscoveryStartedCallback = (TGSISetUDPDiscoveryStartedCallbackProc)GetProcAddress(LibHandle,
      "SetUDPDiscoveryStartedCallback");
    GSISetUDPDiscoveryServiceFoundCallback = (TGSISetUDPDiscoveryServiceFoundCallbackProc)GetProcAddress(LibHandle,
      "SetUDPDiscoveryServiceFoundCallback");

    if ((GSIUDPDiscoveryStart == NULL)
      || (GSIUDPDiscoveryAddAdvertisedTCPService == NULL)
      || (GSIUDPDiscoveryClearAdvertisedServices == NULL)
      || (GSIUDPDiscoveryFindServicesWithName == NULL)
      || (GSIUDPDiscoveryFoundServiceCount == NULL)
      || (GSIUDPDiscoveryGetServiceInfo == NULL)
      || (GSIUDPDiscoveryStop == NULL)
      || (GSISetUDPDiscoveryStartedCallback == NULL)
      || (GSISetUDPDiscoveryServiceFoundCallback == NULL))
    {
      break;
    }

    successful = TRUE;

  } while (FALSE);

  if (!successful)
    CloseGolfSensorInterface();

  return successful;
}

void CloseGolfSensorInterface(void)
{
  if (LibHandle != NULL)
  {
    FreeLibrary(LibHandle);
    LibHandle = NULL;
  }
}

double Poly3Eval(TD3rdOrderPolynomial poly, double t)
{
  return poly[0] + t * (poly[1] + t * poly[2]);
}

double Poly5Eval(TD5thOrderPolynomial poly, double t)
{
  return poly[0] + t * (poly[1] + t * (poly[2] + t * (poly[3] + t * poly[4])));
}

