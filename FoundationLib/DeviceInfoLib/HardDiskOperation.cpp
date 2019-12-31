// HardDiskOperation.cpp: implementation of the CHardDiskOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HardDiskOperation.h"

// #include <sstream>

#include "DeviceInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHardDiskOperation::CHardDiskOperation()
{

}

CHardDiskOperation::~CHardDiskOperation()
{

}

std::string CHardDiskOperation::getFysicalSn(int index)
{
	long diskId=getHardDriveComputerID(index);

// 	std::stringstream ss;
// 	ss<<diskId;
// 
// 	std::string did=ss.str();
// 	return did;

	return getHardDistSn();
}

