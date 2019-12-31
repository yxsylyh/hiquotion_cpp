// Hardware.cpp : Implementation of CHardware
#include "StdAfx.h"
// #include "NetCA_HARDWARE.h"
#include "Hardware.h"

#define UnknownDevice TEXT("<Unknown Device>")

#pragma comment(lib,"Setupapi.lib")

/////////////////////////////////////////////////////////////////////////////
// CHardware

CHardware::CHardware(void)
	: DrvID(NULL), TIndex(-1)
{
}


CHardware::~CHardware(void)
{
}

/*************************************************

    parameter:	DriverID[in]--unique ID of the device in registry
				pVal[out,retval]--，return 0 if succeed，return 1 if fail
     2002－6－21

**********************************************************/
HRESULT CHardware::Disable(BSTR DriverID, long *pVal)
{
	BOOL ShowHidden = 0;
	HDEVINFO hDevInfo = 0;
	long len;
	//init the value
	TIndex = -1;
	len = wcstombs(NULL,DriverID,wcslen(DriverID));
	len = len + 1;
	DrvID = (char *)malloc(len);
	memset(DrvID,0,len+1);
	wcstombs(DrvID,DriverID,wcslen(DriverID));

	hDevInfo = SetupDiGetClassDevs(NULL,NULL,NULL,DIGCF_PRESENT|DIGCF_ALLCLASSES);
	if (INVALID_HANDLE_VALUE == hDevInfo)
	{
		*pVal = -1;
		return S_OK;
	}

	//get the index of drv in the set
	EnumAddDevices(ShowHidden,hDevInfo);
	if(TIndex==-1)
	{
		*pVal = -1;
		return S_OK;
	}

	//disable the drv
       
	// if ((IsDisableable(TIndex,hDevInfo))&&(!(TIndex==-1)))
	if (!IsDisabled(TIndex,hDevInfo)) 
		if (IsDisableable(TIndex,hDevInfo))
			if (StateChange(DICS_DISABLE,TIndex,hDevInfo))
				*pVal = 0;
			else
				*pVal = -1;
		else
			*pVal = 1;
	else 
		*pVal = 0;

	if(hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);

	return S_OK;
}

BOOL CHardware::EnumAddDevices(BOOL ShowHidden, HDEVINFO hDevInfo)
{
	DWORD i, Status, Problem;

    LPTSTR IOName=NULL;
	DWORD len=0;
    SP_DEVINFO_DATA DeviceInfoData = {sizeof(SP_DEVINFO_DATA)};

    //
    // Enumerate though all the devices.
    //
    for (i=0;SetupDiEnumDeviceInfo(hDevInfo,i,&DeviceInfoData);i++)
    {
        //
        // Should we display this device, or move onto the next one.
        //
        if (CR_SUCCESS != CM_Get_DevNode_Status(&Status, &Problem, DeviceInfoData.DevInst,0))
        {
            continue;
        }

        if (!(ShowHidden || !((Status & DN_NO_SHOW_IN_DM) || IsClassHidden(&DeviceInfoData.ClassGuid))))
            continue;

        //
        // Get a friendly name for the device.
        //
        ConstructDeviceName(hDevInfo,&DeviceInfoData, &IOName, (PULONG)&len);
		if (strcmp(IOName,DrvID) == 0)
		{
			TIndex = i;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CHardware::IsClassHidden(GUID *ClassGuid)
{
	BOOL bHidden = FALSE;
    HKEY hKeyClass;

    //
    // If the devices class has the NoDisplayClass value then
    // don't display this device.
    //
    if (hKeyClass = SetupDiOpenClassRegKey(ClassGuid,KEY_READ))
    {
        bHidden = (RegQueryValueEx(hKeyClass, REGSTR_VAL_NODISPLAYCLASS, NULL, NULL, NULL, NULL) == ERROR_SUCCESS);
        RegCloseKey(hKeyClass);
    }                                 

    return bHidden;
}

BOOL CHardware::ConstructDeviceName(HDEVINFO DeviceInfoSet, PSP_DEVINFO_DATA DeviceInfoData, PVOID Buffer, PULONG Length)
{
// 	if (!GetRegistryProperty(DeviceInfoSet, DeviceInfoData, SPDRP_DRIVER , Buffer, Length))
//     {
//         if (!GetRegistryProperty(DeviceInfoSet, DeviceInfoData, SPDRP_DEVICEDESC, Buffer, Length))
//         {
//             if (!GetRegistryProperty(DeviceInfoSet, DeviceInfoData, SPDRP_CLASS, Buffer, Length))
//             {
                if (!GetRegistryProperty(DeviceInfoSet, DeviceInfoData, SPDRP_CLASSGUID, Buffer, Length))
                {
                     *Length = (_tcslen(UnknownDevice)+1)*sizeof(TCHAR);
                     Buffer =(char *)malloc(*Length);
                     _tcscpy(*(LPTSTR *)Buffer, UnknownDevice);
                }
//             }
//         }
//     }

	return TRUE;
}

BOOL CHardware::GetRegistryProperty(HDEVINFO DeviceInfoSet, PSP_DEVINFO_DATA DeviceInfoData, ULONG Property, PVOID Buffer, PULONG Length)
{
	while (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet, DeviceInfoData, Property, NULL, (BYTE *)*(TCHAR **)Buffer, *Length, Length))
    {
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            //
            // We need to change the buffer size.
            //
            if (*(LPTSTR *)Buffer)
				LocalFree(*(LPTSTR *)Buffer);

            *(LPTSTR *)Buffer = (PCHAR)LocalAlloc(LPTR,*Length);
        }
        else
        {
            //
            // Unknown Failure.
            //
            return FALSE;
        }            
    }

    return (*(LPTSTR *)Buffer)[0];
}

BOOL CHardware::StateChange(DWORD NewState, DWORD SelectedItem, HDEVINFO hDevInfo)
{
	SP_PROPCHANGE_PARAMS PropChangeParams = {sizeof(SP_CLASSINSTALL_HEADER)};
    SP_DEVINFO_DATA DeviceInfoData = {sizeof(SP_DEVINFO_DATA)};
    
    //
    // Get a handle to the Selected Item.
    //
    if (!SetupDiEnumDeviceInfo(hDevInfo,SelectedItem,&DeviceInfoData))
    {
        return FALSE;
    }

    //
    // Set the PropChangeParams structure.
    //
    PropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
    PropChangeParams.Scope = DICS_FLAG_GLOBAL;
    PropChangeParams.StateChange = NewState; 

    if (!SetupDiSetClassInstallParams(hDevInfo, &DeviceInfoData, (SP_CLASSINSTALL_HEADER *)&PropChangeParams, sizeof(PropChangeParams)))
    {
		DWORD ret=GetLastError();
        return FALSE;
    }

    //
    // Call the ClassInstaller and perform the change.
    //
    if (!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &DeviceInfoData))
    {
		DWORD ret=GetLastError();
		// 0xE0000235  32位程序操作64位驱动，必须编译成64位的程序运行才能成功
		//          5  拒绝访问，            必须以管理员身份运行才能成功
        return FALSE;
    }
    
    return TRUE;
}

BOOL CHardware::IsDisabled(DWORD SelectedItem, HDEVINFO hDevInfo)
{
SP_DEVINFO_DATA DeviceInfoData = {sizeof(SP_DEVINFO_DATA)};
    DWORD Status, Problem;

    //
    // Get a handle to the Selected Item.
    //
    if (!SetupDiEnumDeviceInfo(hDevInfo,SelectedItem,&DeviceInfoData))
    {

        return FALSE;
    }

    if (CR_SUCCESS != CM_Get_DevNode_Status(&Status, &Problem,
                DeviceInfoData.DevInst,0))
    {

        return FALSE;
    }

    return ((Status & DN_HAS_PROBLEM) && (CM_PROB_DISABLED == Problem)) ;
}

BOOL CHardware::IsDisableable(DWORD SelectedItem, HDEVINFO hDevInfo)
{
	SP_DEVINFO_DATA DeviceInfoData = {sizeof(SP_DEVINFO_DATA)};
    DWORD Status, Problem;

    //
    // Get a handle to the Selected Item.
    //
    if (!SetupDiEnumDeviceInfo(hDevInfo,SelectedItem,&DeviceInfoData))
    {
        return FALSE;
    }

    if (CR_SUCCESS != CM_Get_DevNode_Status(&Status, &Problem, DeviceInfoData.DevInst,0))
    {
        return FALSE;
    }

    return ((Status & DN_DISABLEABLE) && 
        (CM_PROB_HARDWARE_DISABLED != Problem));
}

HRESULT CHardware::Enable(BSTR DriverID, long *pVal)
{
	BOOL ShowHidden = 0;
	HDEVINFO hDevInfo = 0;
	long len;
	//init the value
	TIndex = -1;
	len = wcstombs(NULL,DriverID,wcslen(DriverID));
	len = len + 1;
	DrvID = (char *)malloc(len);
	memset(DrvID,0,len+1);
	wcstombs(DrvID,DriverID,wcslen(DriverID));

	if (INVALID_HANDLE_VALUE == (hDevInfo =  SetupDiGetClassDevs(NULL,NULL,NULL,DIGCF_PRESENT|DIGCF_ALLCLASSES)))
	{
		*pVal = -1;
		return S_OK;
	}

	//get the index of drv in the set
	EnumAddDevices(ShowHidden,hDevInfo);

	//disable the drv
       
	if (IsDisabled(TIndex,hDevInfo))
		if (StateChange(DICS_ENABLE,TIndex,hDevInfo))
			*pVal = 0;
		else
			*pVal = -1;
	else
		*pVal = 0;
  
	if(hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);

	return S_OK;
}

