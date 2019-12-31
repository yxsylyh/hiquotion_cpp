#pragma once
#include <setupapi.h>
#include <devguid.h>
#include <cfg.h>
#include <cfgmgr32.h>
#include <regstr.h>   // Extract Registry Strings

class CHardware
{
public:
	CHardware(void);
	~CHardware(void);
	HRESULT Disable(BSTR DriverID, long *pVal);
	BOOL EnumAddDevices(BOOL ShowHidden, HDEVINFO hDevInfo);
	BOOL IsClassHidden(GUID *ClassGuid);
	BOOL ConstructDeviceName(HDEVINFO DeviceInfoSet, PSP_DEVINFO_DATA DeviceInfoData, PVOID Buffer, PULONG Length);
	BOOL GetRegistryProperty(HDEVINFO DeviceInfoSet, PSP_DEVINFO_DATA DeviceInfoData, ULONG Property, PVOID Buffer, PULONG Length);
	BOOL StateChange(DWORD NewState, DWORD SelectedItem, HDEVINFO hDevInfo);
	BOOL IsDisabled(DWORD SelectedItem, HDEVINFO hDevInfo);
	BOOL IsDisableable(DWORD SelectedItem, HDEVINFO hDevInfo);
	HRESULT Enable(BSTR DriverID, long *pVal);

private:
	DWORD TIndex;
	char *DrvID;
};

