#include "StdAfx.h"
#include "HardwareOperation.h"
#include <C++\FoundationLib\FileSysLib\FileOperation.h>
#include <C++\FoundationLib\StringExtLib\StringExt.h>
#include <C++\FoundationLib\GuidLib\guid.h>
#include <C++\FoundationLib\DataStructLib\StringArrayExt.h>

#pragma comment(lib,"Setupapi.lib")

#define BUFF_SIZE 1024 

CHardwareOperation::CHardwareOperation(void)
	: m_hDevInfo(INVALID_HANDLE_VALUE)
{
	getDeviceInfoList();
	m_deviceInfoList.setSelfDestroy(TRUE);
}

CHardwareOperation::~CHardwareOperation(void)
{
	if(m_hDevInfo!=INVALID_HANDLE_VALUE)
		SetupDiDestroyDeviceInfoList(m_hDevInfo);
}

int CHardwareOperation::getUnknownDeviceIdAndCompatibleIdList(CPointerList<CStringArray *> &hwids)
{
	if(hwids.size()>0)
	{
		hwids.destroyAll();
		hwids.clear();
	}

	HDEVINFO hDevInfo = NULL;
	SP_DEVINFO_DATA DevInfoData;
	DWORD EnumPos = 0;
	CHAR buffer[BUFF_SIZE];
	memset(buffer,0x00,BUFF_SIZE);

	hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if(hDevInfo == INVALID_HANDLE_VALUE)
		return -1;

	DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	DWORD size=0;
	for(EnumPos=0; SetupDiEnumDeviceInfo(hDevInfo, EnumPos, &DevInfoData); EnumPos++)
	{
		// 获取设备属性（设备类）失败了，说明是未知设备
		if(!SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_CLASS, NULL, (PBYTE)buffer, BUFF_SIZE, NULL))
		{
			// 获取未知设备的属性（硬件id），如成功则添加到字符串列表中
			if(SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)buffer, BUFF_SIZE, &size))
			{
				CStringArray *varray=new CStringArray();
				CStringExt::Split(varray, buffer, size, 0);

				// 获取未知设备的属性（兼容硬件id），如成功则添加到字符串列表中
				memset(buffer,0x00,BUFF_SIZE);
				if(SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_COMPATIBLEIDS, NULL, (PBYTE)buffer, BUFF_SIZE, &size))
				{
					CStringArray *varray2=new CStringArray();
					CStringExt::Split(varray2, buffer, size, 0);

					for(int i=0;i<varray2->GetSize();i++)
					{
						varray->Add(varray2->GetAt(i));
					}

					varray2->RemoveAll();
					delete varray2;
				}

				hwids.push_back(varray);
			}
		}

	}

	if(hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);

	return 0;

}

// 获取指定条件下的已知设备的硬件id和硬件兼容id
// 返回值：
//  0：成功
// -1：调用 SetupDiGetClassDevs 失败
int CHardwareOperation::getDeviceIdAndCompatibleIdList(CPointerList<CStringArray *> &hwids, DWORD conditionFilterFlag, CString conditionString)
{
	if(conditionFilterFlag==-1)
		return -99;

	if(hwids.size()>0)
	{
		hwids.destroyAll();
		hwids.clear();
	}

	HDEVINFO hDevInfo = NULL;
	SP_DEVINFO_DATA DevInfoData;
	DWORD EnumPos = 0;
	CHAR buffer[BUFF_SIZE];
	memset(buffer,0x00,BUFF_SIZE);

	hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if(hDevInfo == INVALID_HANDLE_VALUE)
		return -1;

	DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	conditionString=conditionString.MakeLower();

	DWORD size=0;
	for(EnumPos=0; SetupDiEnumDeviceInfo(hDevInfo, EnumPos, &DevInfoData); EnumPos++)
	{
		// 获取设备属性（设备类）成功，那么
		if(SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_CLASS, NULL, (PBYTE)buffer, BUFF_SIZE, NULL))
		{
			// 获取硬件设备的条件项成功时，
			// 获取条件项失败，则不添加
			memset(buffer,0x00,BUFF_SIZE);
			if(SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, conditionFilterFlag, NULL, (PBYTE)buffer, BUFF_SIZE, NULL))
			{
				// 与条件项指定的字符串相同时，才需要添加
				CString got=buffer;
				got=got.MakeLower();
				if(conditionString==got)
				{
					// 获取硬件id
					memset(buffer,0x00,BUFF_SIZE);
					if(SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)buffer, BUFF_SIZE, &size))
					{
						CStringArray *varray=new CStringArray();
						CStringExt::Split(varray, buffer, size, 0);

						// 获取硬件兼容id
						memset(buffer,0x00,BUFF_SIZE);
						if(SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_COMPATIBLEIDS, NULL, (PBYTE)buffer, BUFF_SIZE, &size))
						{
							CStringArray *varray2=new CStringArray();
							CStringExt::Split(varray2, buffer, size, 0);

							for(int i=0;i<varray2->GetSize();i++)
							{
								varray->Add(varray2->GetAt(i));
							}

							varray2->RemoveAll();
							delete varray2;
						}

						hwids.push_back(varray);
					}
				}
			}
		}
	}

	if(hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);

	return 0;

}

int CHardwareOperation::getDeviceInfoList()
{
	if(m_hDevInfo != INVALID_HANDLE_VALUE)
		return 0;

	if(m_deviceInfoList.size()>0)
	{
		m_deviceInfoList.destroyAll();
		m_deviceInfoList.clear();
	}

	SP_DEVINFO_DATA DevInfoData;
	DWORD EnumPos = 0;
	CHAR buffer[BUFF_SIZE];
	memset(buffer,0x00,BUFF_SIZE);

	m_hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if(m_hDevInfo == INVALID_HANDLE_VALUE)
		return -1;

	DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	DWORD size=0;
	for(EnumPos=0; SetupDiEnumDeviceInfo(m_hDevInfo, EnumPos, &DevInfoData); EnumPos++)
	{
		SP_DEVINFO_DATA *info=new SP_DEVINFO_DATA;
		memcpy(info, &DevInfoData, sizeof(SP_DEVINFO_DATA));
		m_deviceInfoList.push_back(info);
	}

	return 0;
}

int CHardwareOperation::getUnkownDeviceInfoList(CPointerList<SP_DEVINFO_DATA *> *unkownDeviceInfoList)
{
	if(!unkownDeviceInfoList)
		return -1;

	int ret=getDeviceInfoList();
	if(ret<0)
		return -2;

	unkownDeviceInfoList->clear();

	m_hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if(m_hDevInfo == INVALID_HANDLE_VALUE)
		return -3;

	for(int i=0;i<(int)m_deviceInfoList.size();i++)
	{
		SP_DEVINFO_DATA *devInfo=m_deviceInfoList.at(i);
		if(!devInfo)
			continue;

		CHAR buffer[BUFF_SIZE];
		memset(buffer,0x00,BUFF_SIZE);
		if(!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_CLASS, NULL, (PBYTE)buffer, BUFF_SIZE, NULL))
		{
			unkownDeviceInfoList->push_back(devInfo);
		}
	}

	return 0;
}

int CHardwareOperation::getFilteredDeviceInfoList( FilterMode mode, CString catalog, CStringArray *devidArray, CPointerList<SP_DEVINFO_DATA *> *filteredDeviceInfoList )
{
	if(!filteredDeviceInfoList)
		return -1;

	int ret=getDeviceInfoList();
	if(ret<0)
		return -2;

	CHAR buffer[BUFF_SIZE];
	memset(buffer,0x00,BUFF_SIZE);

	DWORD size=0;
	for(int i=0;i<(int)m_deviceInfoList.size();i++)
	{
		SP_DEVINFO_DATA *devInfo=m_deviceInfoList.at(i);
		if(!devInfo)
			continue;

		memset(buffer,0x00,BUFF_SIZE);
		if(!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_CLASS, NULL, (PBYTE)buffer, BUFF_SIZE, NULL))
			continue;
		CString sclass=buffer;

		memset(buffer,0x00,BUFF_SIZE);
		if(!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_HARDWAREID, NULL, (PBYTE)buffer, BUFF_SIZE, &size))
			continue;
		CStringArray queryarray;
		CStringExt::Split(&queryarray, buffer, size, 0);

		switch((int)mode)
		{
		case All:
			filteredDeviceInfoList->push_back(devInfo);
			break;
		case AllInClass:
			if(catalog==sclass)
				filteredDeviceInfoList->push_back(devInfo);
			break;
		case Include:
			if(CStringArrayExt::intersect(devidArray, &queryarray))
				filteredDeviceInfoList->push_back(devInfo);
			break;
		case ExcludeInAll:
			if(!CStringArrayExt::intersect(devidArray, &queryarray))
				filteredDeviceInfoList->push_back(devInfo);
			break;
		case ExcludeInClass:
			if(!CStringArrayExt::intersect(devidArray, &queryarray))
			{
				if(catalog==sclass)
					filteredDeviceInfoList->push_back(devInfo);
			}
			break;
		}
	}

	return 0;
}

int CHardwareOperation::getFilteredDeviceInfoList( FilterType type, CString toMatchString, CPointerList<SP_DEVINFO_DATA *> *filteredDeviceInfoList )
{
	if(!filteredDeviceInfoList)
		return -1;

	int ret=getDeviceInfoList();
	if(ret<0)
		return -2;

	CHAR buffer[BUFF_SIZE];

	DWORD size=0;
	for(int i=0;i<(int)m_deviceInfoList.size();i++)
	{
		SP_DEVINFO_DATA *devInfo=m_deviceInfoList.at(i);
		if(!devInfo)
			continue;

		CString gotString;
		memset(buffer,0x00,BUFF_SIZE);
		switch(type)
		{
		case Class:
			if(!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_CLASS, NULL, (PBYTE)buffer, BUFF_SIZE, NULL))
				continue;
			gotString=buffer;
			break;

		case Description:
			if(!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_DEVICEDESC, NULL, (PBYTE)buffer, BUFF_SIZE, &size))
				continue;
			gotString=buffer;
			break;

		case Devid:
			if(!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_HARDWAREID, NULL, (PBYTE)buffer, BUFF_SIZE, &size))
				continue;
			break;

		default:
			gotString="";
			break;
		}

		if(type!=Devid)
		{
			if(gotString.GetLength()<=0)
				return -3;

			gotString=gotString.Trim();
			if(gotString.GetLength()<=0)
				return -4;

			toMatchString=toMatchString.Trim();
			if(toMatchString.GetLength()<=0)
				return -5;

			if(gotString==toMatchString)
				filteredDeviceInfoList->push_back(devInfo);
		}
		else
		{
			CStringArray queryarray;
			CStringExt::Split(&queryarray, buffer, size, 0);
			if(CStringArrayExt::isContain(&queryarray, toMatchString))
				filteredDeviceInfoList->push_back(devInfo);
		}
	}

	return 0;
}

CString CHardwareOperation::getDeviceDescription( SP_DEVINFO_DATA *devInfo )
{
	CHAR buffer[BUFF_SIZE];
	memset(buffer,0x00,BUFF_SIZE);
	DWORD size=0;
	if(!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_DEVICEDESC, NULL, (PBYTE)buffer, BUFF_SIZE, &size))
		return "";

	return buffer;
}

CString CHardwareOperation::getDeviceClass( SP_DEVINFO_DATA *devInfo )
{
	CHAR buffer[BUFF_SIZE];
	memset(buffer,0x00,BUFF_SIZE);
	DWORD size=0;
	if(!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_CLASS, NULL, (PBYTE)buffer, BUFF_SIZE, NULL))
		return "";

	return buffer;
}

void CHardwareOperation::getDeviceIds( SP_DEVINFO_DATA *devInfo, CStringArray *strArray )
{
	CHAR buffer[BUFF_SIZE];
	memset(buffer,0x00,BUFF_SIZE);
	DWORD size=0;
	if(!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_HARDWAREID, NULL, (PBYTE)buffer, BUFF_SIZE, &size))
		return;

	CStringExt::Split(strArray, buffer, size, 0);
}

int CHardwareOperation::toDeviceInfoStructList( CPointerList<SP_DEVINFO_DATA *> *deviceInfoList, CPointerList<DeviceInfo *> *deviceInfoStructList )
{
	if(!deviceInfoList || !deviceInfoStructList)
		return -1;

	if(deviceInfoList->size()<=0)
		return 0;

	deviceInfoStructList->destroyAll();
	deviceInfoStructList->clear();

	for(int i=0;i<(int)deviceInfoList->size();i++)
	{
		SP_DEVINFO_DATA *devInfo=deviceInfoList->at(i);
		if(!devInfo)
			continue;

		DeviceInfo *info=new DeviceInfo;

		TCHAR szClassBuf[MAX_PATH] = { 0 };
		TCHAR szDescBuf[MAX_PATH] = { 0 };
		TCHAR szDriver[MAX_PATH] = { 0 };
		TCHAR szFriName[MAX_PATH] = { 0 };

		// 获取类名  
		if (!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_CLASS, NULL, (PBYTE)szClassBuf, MAX_PATH - 1, NULL))         
		{
			///*continue*/;
			delete info;
			//PrintError ("Get szClassBuf Name ERR!");
			return -2;
		}

		info->szDeviceClass = szClassBuf;

		//获取设备描述信息
		if (!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_DEVICEDESC, NULL, (PBYTE)szDescBuf, MAX_PATH - 1, NULL))         
		{
			delete info;
			///*continue*/;
			//PrintError ("Get szDescBuf Name ERR!");
			return -2;
		}

		info->szDeviceDesc = szDescBuf;

		//获取设备驱动名
		if (!SetupDiGetDeviceRegistryProperty(m_hDevInfo, devInfo, SPDRP_DRIVER, NULL, (PBYTE)szDriver, MAX_PATH - 1, NULL))         
		{
			delete info;
			///*continue*/;
			//PrintError ("Get szDriver Name ERR!");
			return -2;
		}

		info->szDriverName = szDriver;

		//获取设备友好名
// 		if (!SetupDiGetDeviceRegistryProperty(hDevInfo, devInfo, SPDRP_FRIENDLYNAME, NULL, (PBYTE)szFriName, MAX_PATH - 1, NULL))         
// 		{
// 			delete info;
// 			///*continue*/;
// 			//PrintError ("Get Friend Name ERR!");
// 			return -2;
// 		}
// 		//ERROR_INSUFFICIENT_BUFFER
// 
// 		info->szDeviceName = szFriName;

		info->dwDevIns = devInfo->DevInst;
		info->Guid = devInfo->ClassGuid;

		deviceInfoStructList->push_back (info);
	}

	return 0;
}


//设置设备状态(启用/停用),1为启用,0为停用
BOOL CHardwareOperation::SetDeviceStatus(DeviceInfo *theDevice,BOOL bStatusFlag)
// BOOL CHardwareOperation::SetDeviceStatus(SP_DEVINFO_DATA *theDevice,BOOL bStatusFlag)
{
	BOOL bFlag = TRUE;

	SP_DEVINFO_DATA DeviceInfoData;//*DeviceInfoData=theDevice;
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA); 

	//判断是否有这个设备
	bFlag = FALSE;
	int index = 0;
	while (SetupDiEnumDeviceInfo(m_hDevInfo, index ++, &DeviceInfoData))
	{
		if (DeviceInfoData.ClassGuid == theDevice->Guid && DeviceInfoData.DevInst == theDevice->dwDevIns)
		{
			bFlag = TRUE;
			break;
		}
	}
	if (!bFlag)
	{
		return bFlag;
	}

	//初始化属性
	SP_PROPCHANGE_PARAMS propChange;
	propChange.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
	propChange.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
	propChange.Scope = DICS_FLAG_GLOBAL;
// #define DICS_ENABLE      0x00000001
// #define DICS_DISABLE     0x00000002
// #define DICS_PROPCHANGE  0x00000003
// #define DICS_START       0x00000004
// #define DICS_STOP        0x00000005
// 	propChange.StateChange = (DWORD)bStatusFlag ? DICS_START: DICS_STOP;
	propChange.StateChange = (DWORD)bStatusFlag ? DICS_ENABLE: DICS_DISABLE;
	propChange.HwProfile = 0;  // 0 means use current profile

	if (SetupDiSetClassInstallParams(m_hDevInfo, &DeviceInfoData, (SP_CLASSINSTALL_HEADER *)&propChange, sizeof(propChange)))
	{
// 		if (!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, m_hDevInfo, &DeviceInfoData))
// 		{
// 			DWORD eno=GetLastError();
// 			CString sno;
// 			sno.Format("%d", eno);
// 			MessageBox(NULL, sno, "", MB_OK);
// 			bFlag = FALSE;
// 		}

		if (!SetupDiChangeState(m_hDevInfo, &DeviceInfoData))
		{
			DWORD eno=GetLastError();
			CString sno;
			sno.Format("%d", eno);
// 			MessageBox(NULL, sno, "", MB_OK);
			bFlag = FALSE;
		}
	}
	else
	{
		DWORD eno=GetLastError();
		CString sno;
		sno.Format("%d", eno);
// 		MessageBox(NULL, sno, "", MB_OK);
		bFlag = FALSE;
	}

	return bFlag;
}

BOOL CHardwareOperation::SetDeviceStatus( SP_DEVINFO_DATA *theDevice,BOOL bStatusFlag )
{
	BOOL bFlag = TRUE;

	SP_DEVINFO_DATA DeviceInfoData;//*DeviceInfoData=theDevice;
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA); 

	//判断是否有这个设备
	bFlag = FALSE;
	int index = 0;
	while (SetupDiEnumDeviceInfo(m_hDevInfo, index ++, &DeviceInfoData))
	{
		if (DeviceInfoData.ClassGuid == theDevice->ClassGuid && DeviceInfoData.DevInst == theDevice->DevInst)
		{
			bFlag = TRUE;
			break;
		}
	}
	if (!bFlag)
	{
		return bFlag;
	}

	//初始化属性
	SP_PROPCHANGE_PARAMS propChange;
	propChange.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
	propChange.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
	propChange.Scope = DICS_FLAG_GLOBAL;
// #define DICS_ENABLE      0x00000001
// #define DICS_DISABLE     0x00000002
// #define DICS_PROPCHANGE  0x00000003
// #define DICS_START       0x00000004
// #define DICS_STOP        0x00000005
// 	propChange.StateChange = (DWORD)bStatusFlag ? DICS_START: DICS_STOP;
	propChange.StateChange = (DWORD)bStatusFlag ? DICS_ENABLE: DICS_DISABLE;
	propChange.HwProfile = 0;  // 0 means use current profile

	if (SetupDiSetClassInstallParams(m_hDevInfo, &DeviceInfoData, (SP_CLASSINSTALL_HEADER *)&propChange, sizeof(propChange)))
	{
// 		if (!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &DeviceInfoData))
// 		{
// 			DWORD eno=GetLastError();
// 			CString sno;
// 			sno.Format("%d", eno);
// 	//		MessageBox(NULL, sno, "", MB_OK);
// 			bFlag = FALSE;
// 		}

		if (!SetupDiChangeState(m_hDevInfo, &DeviceInfoData))
		{
			DWORD eno=GetLastError();
			CString sno;
			sno.Format("%d", eno);
// 			MessageBox(NULL, sno, "", MB_OK);
			bFlag = FALSE;
		}
	}
	else
	{
		DWORD eno=GetLastError();
		CString sno;
		sno.Format("%d", eno);
// 		MessageBox(NULL, sno, "", MB_OK);
		bFlag = FALSE;
	}

	return bFlag;
}
