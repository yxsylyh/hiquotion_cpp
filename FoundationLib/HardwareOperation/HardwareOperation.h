#pragma once
#include <C++\FoundationLib\DataStructLib\PointerList.h>
#include <setupapi.h>
#include <devguid.h>

typedef struct tagDeviceInfo
{
	//设备友好名称
	CString szDeviceName;
	//设备类
	CString szDeviceClass;
	//设备显示名
	CString szDeviceDesc;
	//设备驱动
	CString szDriverName;
	//设备实例
	DWORD dwDevIns;
	//设备类标志
	GUID Guid;
	//按类名排序
	bool operator < (const tagDeviceInfo &tmp) const
	{
		if (tmp.szDeviceClass != szDeviceClass)
		{
			return tmp.szDeviceClass.CompareNoCase (szDeviceClass) > 0;
		}
		else
		{
			return tmp.szDeviceDesc.CompareNoCase (szDeviceDesc) > 0;
		}
	}
}DeviceInfo;

enum FilterType
{
	Class,
	Description,
	Devid,
};

// enum IncludeMode
// {
// 	All,
// 	Include,
// 	Exclude,
// };

enum FilterMode
{
	All,   // 全部硬件
	AllInClass,  // 指定分类下的全部硬件
	Include,   // 包含硬件id列表中的硬件（只过滤出操作系统中有的）
	ExcludeInAll,   // 在全部硬件中排除硬件id列表中的硬件
	ExcludeInClass  // 在指定Class中排除硬件id列表中的硬件
};

class CHardwareOperation
{
public:
	CHardwareOperation(void);
	~CHardwareOperation(void);

	// 获取设备信息列表
	// 参数 硬件分类的GUID（如果为NULL，则获取所有分类的设备。但不包括未知设备）；fileterFlag指定获取那个信息；获取到的硬件id 字符串列表；指定条件filgerFlag；指定条件字符串
	// 说明：只有满足条件filgerFlag的值为条件字符串的硬件filterFlag的值，才会添加到hwids列表中
	// 返回值：
	//  0：成功
	// -1：调用 SetupDiGetClassDevs 失败
	/*
	GUID 可以是如下的值（VS2010 devguid.h 中定义）
	GUID_DEVCLASS_1394
	GUID_DEVCLASS_1394DEBUG
	GUID_DEVCLASS_61883
	GUID_DEVCLASS_ADAPTER
	GUID_DEVCLASS_APMSUPPORT,
	GUID_DEVCLASS_AVC,
	GUID_DEVCLASS_BATTERY,
	GUID_DEVCLASS_BIOMETRIC,
	GUID_DEVCLASS_BLUETOOTH,
	GUID_DEVCLASS_CDROM          // 光驱
	GUID_DEVCLASS_COMPUTER       // 计算机
	GUID_DEVCLASS_DECODER,
	GUID_DEVCLASS_DISKDRIVE      // 磁盘驱动器
	GUID_DEVCLASS_DISPLAY        // 显示卡
	GUID_DEVCLASS_DOT4,
	GUID_DEVCLASS_DOT4PRINT,
	GUID_DEVCLASS_ENUM1394,
	GUID_DEVCLASS_FDC            // 软盘控制器
	GUID_DEVCLASS_FLOPPYDISK     // 软盘驱动器
	GUID_DEVCLASS_GPS,
	GUID_DEVCLASS_HDC            // IDE ATA/ATAPI 控制器
	GUID_DEVCLASS_HIDCLASS,
	GUID_DEVCLASS_IMAGE,
	GUID_DEVCLASS_INFINIBAND,
	GUID_DEVCLASS_INFRARED,
	GUID_DEVCLASS_KEYBOARD       // 键盘
	GUID_DEVCLASS_LEGACYDRIVER,
	GUID_DEVCLASS_MEDIA          // 声音、视频和游戏控制器
	GUID_DEVCLASS_MEDIUM_CHANGER,
	GUID_DEVCLASS_MODEM          // MODEM
	GUID_DEVCLASS_MONITOR        // 监视器
	GUID_DEVCLASS_MOUSE          // 鼠标和其他指针设备
	GUID_DEVCLASS_MTD,
	GUID_DEVCLASS_MULTIFUNCTION,
	GUID_DEVCLASS_MULTIPORTSERIAL,
	GUID_DEVCLASS_NET            // 网络设备器
	GUID_DEVCLASS_NETCLIENT,
	GUID_DEVCLASS_NETSERVICE,
	GUID_DEVCLASS_NETTRANS,
	GUID_DEVCLASS_NODRIVER,
	GUID_DEVCLASS_PCMCIA,
	GUID_DEVCLASS_PNPPRINTERS,
	GUID_DEVCLASS_PORTS          // 端口（COM 和 LPT）
	GUID_DEVCLASS_PRINTER,
	GUID_DEVCLASS_PRINTERUPGRADE,
	GUID_DEVCLASS_PROCESSOR,
	GUID_DEVCLASS_SBP2,
	GUID_DEVCLASS_SCSIADAPTER    // SCSI 和 RAID 控制器
	GUID_DEVCLASS_SECURITYACCELERATOR,
	GUID_DEVCLASS_SENSOR,
	GUID_DEVCLASS_SIDESHOW,
	GUID_DEVCLASS_SMARTCARDREADER,
	GUID_DEVCLASS_SOUND,
	GUID_DEVCLASS_SYSTEM         // 系统
	GUID_DEVCLASS_TAPEDRIVE,
	GUID_DEVCLASS_UNKNOWN        // 未知设备
	GUID_DEVCLASS_USB            // 通用串行总线控制器
	GUID_DEVCLASS_VOLUME,
	GUID_DEVCLASS_VOLUMESNAPSHOT,
	GUID_DEVCLASS_WCEUSBS,
	GUID_DEVCLASS_WPD,

	*/
	static int getUnknownDeviceIdAndCompatibleIdList(CPointerList<CStringArray *> &hwids);
	static int getDeviceIdAndCompatibleIdList(CPointerList<CStringArray *> &hwids, DWORD conditionFilgerFlag=-1, CString conditionString="");

	// 获取设备信息列表（SP_DEVINFO_DATA结构列表）
	int getDeviceInfoList();

	// 获取未知设备列表（未知设备的SP_DEVINFO_DATA结构列表
	int getUnkownDeviceInfoList(CPointerList<SP_DEVINFO_DATA *> *unkownDeviceInfoList);

	// 从系统中获取指定类别、指定过滤设备id、指定过滤模式的设备列表（SP_DEVINFO_DATA结构列表）
	// catalog：设备类别
	// devidArray：设备id列表
	// filterMode：过滤模式（参看 FilterMode 结构体）
	// filteredDeviceInfoList：最终得到的设备列表
	int getFilteredDeviceInfoList(FilterMode mode, CString catalog, CStringArray *devidArray, CPointerList<SP_DEVINFO_DATA *> *filteredDeviceInfoList);


	// 从系统中获取指定过滤类型、指定包含类型的 toMatchString 字符串的设备信息到的设备信息列表（SP_DEVINFO_DATA结构列表）
	// type：过滤类型，包括全部、指定类、指定描述和指定设备id
	// toMatchString：待匹配字符串，如果type是类，则表示类名，如果是描述，则表示描述，如果是设备id，则表示设备id
	// filteredDeviceInfoList：获取到的设备信息列表
	int getFilteredDeviceInfoList(FilterType type, CString toMatchString, CPointerList<SP_DEVINFO_DATA *> *filteredDeviceInfoList);

	CString getDeviceDescription(SP_DEVINFO_DATA *devInfo);
	CString getDeviceClass(SP_DEVINFO_DATA *devInfo);
	void getDeviceIds(SP_DEVINFO_DATA *devInfo, CStringArray *strArray);

	//设置设备状态(启用/停用),1为启用,0为停用
	BOOL SetDeviceStatus(DeviceInfo *theDevice,BOOL bStatusFlag);
	BOOL SetDeviceStatus(SP_DEVINFO_DATA *theDevice,BOOL bStatusFlag);

	// 从设备信息的SP_DEVINFO_DATA结构列表转换成DeviceInfo结构列表
	int toDeviceInfoStructList(CPointerList<SP_DEVINFO_DATA *> *deviceInfoList, CPointerList<DeviceInfo *> *deviceInfoStructList);

protected:
	CPointerList<SP_DEVINFO_DATA *> m_deviceInfoList;
	HDEVINFO m_hDevInfo;
};
