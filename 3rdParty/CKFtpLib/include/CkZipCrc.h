// CkZipCrc.h: interface for the CkZipCrc class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat v9.5.0

#ifndef _CkZipCrc_H
#define _CkZipCrc_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkClassWithCallbacks.h"

class CkByteData;
class CkTask;
class CkBaseProgress;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkZipCrc
class CK_VISIBLE_PUBLIC CkZipCrc  : public CkClassWithCallbacks
{
    private:

	// Don't allow assignment or copying these objects.
	CkZipCrc(const CkZipCrc &);
	CkZipCrc &operator=(const CkZipCrc &);

    public:
	CkZipCrc(void);
	virtual ~CkZipCrc(void);

	static CkZipCrc *createNew(void);
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	CkBaseProgress *get_EventCallbackObject(void) const;
	void put_EventCallbackObject(CkBaseProgress *progress);


	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------


	// ----------------------
	// Methods
	// ----------------------
	// Provides a way to calculate a CRC by streaming the data a chunk at a time. An
	// application would start by calling BeginStream. Then it would add data by
	// calling MoreData for each additional chunk. After the last chunk has been
	// processed, the EndStream method is called to return the CRC.
	void BeginStream(void);


	// Calculates a 32-bit CRC for in-memory byte data. This is the 32-bit CRC that
	// would be found in a Zip file header if a file containing the data was added to a
	// zip archive.
	unsigned long CalculateCrc(CkByteData &data);


	// Finalizes and returns the Zip CRC value calculated by calling BeginStream
	// followed by multiple calls to MoreData.
	unsigned long EndStream(void);


	// Adds additional data to the CRC currently being calculated. (See BeginStream for
	// more information.)
	unsigned long FileCrc(const char *path);

	// Adds additional data to the CRC currently being calculated. (See BeginStream for
	// more information.)
	CkTask *FileCrcAsync(const char *path);


	// Converts a 32-bit integer to a hexidecimal string.
	void MoreData(CkByteData &data);


	// Converts a 32-bit integer to a hexidecimal string.
	bool ToHex(int crc, CkString &outStr);

	// Converts a 32-bit integer to a hexidecimal string.
	const char *toHex(int crc);





	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
