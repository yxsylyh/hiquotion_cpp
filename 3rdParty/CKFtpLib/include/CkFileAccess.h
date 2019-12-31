// CkFileAccess.h: interface for the CkFileAccess class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat v9.5.0

#ifndef _CkFileAccess_H
#define _CkFileAccess_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkMultiByteBase.h"

class CkByteData;
class CkBinData;
class CkDateTime;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkFileAccess
class CK_VISIBLE_PUBLIC CkFileAccess  : public CkMultiByteBase
{
    private:

	// Don't allow assignment or copying these objects.
	CkFileAccess(const CkFileAccess &);
	CkFileAccess &operator=(const CkFileAccess &);

    public:
	CkFileAccess(void);
	virtual ~CkFileAccess(void);

	static CkFileAccess *createNew(void);
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	

	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// The current working directory of the calling process.
	void get_CurrentDir(CkString &str);
	// The current working directory of the calling process.
	const char *currentDir(void);

	// Returns true if the current open file is at the end-of-file.
	bool get_EndOfFile(void);

	// This property is set by the following methods: FileOpen, OpenForRead,
	// OpenForWrite, OpenForReadWrite, and OpenForAppend. It provides an error code
	// indicating the failure reason. Possible values are:
	// 
	//     Success (No error)
	//     Access denied.
	//     File not found.
	//     General (non-specific) open error.
	//     File aleady exists.
	//     Path refers to a directory and the access requested involves writing.
	//     Too many symbolic links were encountered in resolving path.
	//     The process already has the maximum number of files open.
	//     Pathname is too long.
	//     The system limit on the total number of open files has been reached.
	//     Pathname refers to a device special file and no corresponding device exists.
	//     Insufficient kernel memory was available.
	//     Pathname was to be created but the device containing pathname has no room
	//     for the new file.
	//     A component used as a directory in pathname is not, in fact, a directory.
	//     Pathname refers to a regular file, too large to be opened (this would be a
	//     limitation of the underlying operating system, not a limitation imposed by
	//     Chilkat).
	//     Pathname refers to a file on a read-only filesystem and write access was
	//     requested.
	// 
	int get_FileOpenError(void);

	// The error message text associated with the FileOpenError code.
	void get_FileOpenErrorMsg(CkString &str);
	// The error message text associated with the FileOpenError code.
	const char *fileOpenErrorMsg(void);



	// ----------------------
	// Methods
	// ----------------------
	// Appends a string using the ANSI character encoding to the currently open file.
	bool AppendAnsi(const char *text);


	// Appends a string using the character encoding specified by str to the currently
	// open file.
	bool AppendText(const char *str, const char *charset);


	// Appends the 2-byte Unicode BOM (little endian) to the currently open file.
	bool AppendUnicodeBOM(void);


	// Appends the 3-byte utf-8 BOM to the currently open file.
	bool AppendUtf8BOM(void);


	// Same as DirEnsureExists, except the argument is a file path (the last part of
	// the path is a filename and not a directory). Creates all missing directories
	// such that dirPath may be created.
	bool DirAutoCreate(const char *dirPath);


	// Creates a new directory specified by dirPath.
	bool DirCreate(const char *dirPath);


	// Deletes the directory specified by dirPath.
	bool DirDelete(const char *dirPath);


	// Creates all directories necessary such that the entire filePath exists.
	bool DirEnsureExists(const char *filePath);


	// Closes the currently open file.
	void FileClose(void);


	// Compares the contents of two files and returns true if they are equal and
	// otherwise returns false. The actual contents of the files are only compared if
	// the sizes are equal. The files are not entirely loaded into memory. Instead,
	// they are compared chunk by chunk. This allows for any size files to be compared,
	// regardless of the memory capacity of the computer.
	bool FileContentsEqual(const char *filePath1, const char *filePath2);


	// Copys existingFilepath to newFilepath. If failIfExists is true and newFilepath already exists, then an error is
	// returned.
	bool FileCopy(const char *existingFilepath, const char *newFilepath, bool failIfExists);


	// Deletes the file specified by filePath.
	bool FileDelete(const char *filePath);


	// Returns true if filePath exists, otherwise returns false.
	bool FileExists(const char *filePath);


	// Returns 1 if the file exists, 0 if the file does not exist, and -1 if unable to
	// check because of directory permissions or some other error that prevents the
	// ability to obtain the information.
	int FileExists3(const char *path);


	// This method should only be called on Windows operating systems. It's arguments
	// are similar to the Windows Platform SDK function named CreateFile. For Linux,
	// MAC OS X, and other operating system, use the OpenForRead, OpenForWrite,
	// OpenForReadWrite, and OpenForAppend methods.
	// 
	// Opens a file for reading or writing. The arguments mirror the Windows CreateFile
	// function:
	// Access Modes:
	// GENERIC_READ	(0x80000000)
	// GENERIC_WRITE (0x40000000)
	// 
	// Share Modes:
	// FILE_SHARE_READ(0x00000001)
	// FILE_SHARE_WRITE(0x00000002)
	// 
	// Create Dispositions
	// CREATE_NEW          1
	// CREATE_ALWAYS       2
	// OPEN_EXISTING       3
	// OPEN_ALWAYS         4
	// TRUNCATE_EXISTING   5
	// 
	// // Attributes:
	// FILE_ATTRIBUTE_READONLY         0x00000001
	// FILE_ATTRIBUTE_HIDDEN           0x00000002
	// FILE_ATTRIBUTE_SYSTEM           0x00000004
	// FILE_ATTRIBUTE_DIRECTORY        0x00000010
	// FILE_ATTRIBUTE_ARCHIVE          0x00000020
	// FILE_ATTRIBUTE_NORMAL           0x00000080
	// FILE_ATTRIBUTE_TEMPORARY	   0x00000100
	// 
	bool FileOpen(const char *filePath, unsigned long accessMode, unsigned long shareMode, unsigned long createDisposition, unsigned long attributes);


	// Reads bytes from the currently open file. maxNumBytes specifies the maximum number of
	// bytes to read. Returns an empty byte array on error.
	bool FileRead(int maxNumBytes, CkByteData &outBytes);


	// Reads bytes from the currently open file. maxNumBytes specifies the maximum number of
	// bytes to read. Appends the bytes to the binData.
	bool FileReadBd(int maxNumBytes, CkBinData &binData);


	// Renames a file from existingFilepath to newFilepath.
	bool FileRename(const char *existingFilepath, const char *newFilepath);


	// Sets the file pointer for the currently open file. The offset is an offset in
	// bytes from the origin. The origin can be one of the following:
	// 0 = Offset is from beginning of file.
	// 1 = Offset is from current position of file pointer.
	// 2 = Offset is from the end-of-file (offset may be negative).
	bool FileSeek(int offset, int origin);


	// Returns the size, in bytes, of a file. Returns -1 for failure.
	int FileSize(const char *filePath);


	// Writes bytes to the currently open file.
	bool FileWrite(CkByteData &data);


	// Writes the contents of binData to the currently open file. To specify the entire
	// contents of binData, set both offset and numBytes equal to 0. To write all remaining data
	// starting at offset, then set numBytes equal to 0.
	bool FileWriteBd(CkBinData &binData, int offset, int numBytes);


	// This is purely a utility/convenience method -- initially created to help with
	// block file uploads to Azure Blob storage. It generates a block ID string that is
	// the decimal representation of the index in length chars, and then encoded according
	// to encoding (which can be an encoding such as "base64", "hex", "ascii", etc.) For
	// example, if index = 8, length = 12, and encoding = "base64", then the string "00000012"
	// is returned base64 encoded.
	bool GenBlockId(int index, int length, const char *encoding, CkString &outStr);

	// This is purely a utility/convenience method -- initially created to help with
	// block file uploads to Azure Blob storage. It generates a block ID string that is
	// the decimal representation of the index in length chars, and then encoded according
	// to encoding (which can be an encoding such as "base64", "hex", "ascii", etc.) For
	// example, if index = 8, length = 12, and encoding = "base64", then the string "00000012"
	// is returned base64 encoded.
	const char *genBlockId(int index, int length, const char *encoding);

	// Returns the directory information for the specified path string.
	bool GetDirectoryName(const char *path, CkString &outStr);

	// Returns the directory information for the specified path string.
	const char *getDirectoryName(const char *path);
	// Returns the directory information for the specified path string.
	const char *directoryName(const char *path);


	// Returns the extension of the specified path string.
	bool GetExtension(const char *path, CkString &outStr);

	// Returns the extension of the specified path string.
	const char *getExtension(const char *path);
	// Returns the extension of the specified path string.
	const char *extension(const char *path);


	// Returns the file name and extension of the specified path string.
	bool GetFileName(const char *path, CkString &outStr);

	// Returns the file name and extension of the specified path string.
	const char *getFileName(const char *path);
	// Returns the file name and extension of the specified path string.
	const char *fileName(const char *path);


	// Returns the file name of the specified path string without the extension.
	bool GetFileNameWithoutExtension(const char *path, CkString &outStr);

	// Returns the file name of the specified path string without the extension.
	const char *getFileNameWithoutExtension(const char *path);
	// Returns the file name of the specified path string without the extension.
	const char *fileNameWithoutExtension(const char *path);


	// Returns the number of blocks in the currently open file. The number of bytes per
	// block is specified by blockSize. The number of blocks is the file size divided by the
	// blockSize, plus 1 if the file size is not evenly divisible by blockSize. For example, if
	// the currently open file is 60500 bytes, and if the blockSize is 1000 bytes, then this
	// method returns a count of 61 blocks.
	// 
	// Returns -1 if no file is open. Return 0 if the file is completely empty (0
	// bytes).
	// 
	int GetNumBlocks(int blockSize);


	// Creates a temporary filepath of the form dirPath\prefix_xxxx.TMP Where "xxxx" are
	// random alpha-numeric chars. The returned filepath is guaranteed to not already
	// exist.
	bool GetTempFilename(const char *dirPath, const char *prefix, CkString &outStr);

	// Creates a temporary filepath of the form dirPath\prefix_xxxx.TMP Where "xxxx" are
	// random alpha-numeric chars. The returned filepath is guaranteed to not already
	// exist.
	const char *getTempFilename(const char *dirPath, const char *prefix);
	// Creates a temporary filepath of the form dirPath\prefix_xxxx.TMP Where "xxxx" are
	// random alpha-numeric chars. The returned filepath is guaranteed to not already
	// exist.
	const char *tempFilename(const char *dirPath, const char *prefix);


	// Opens a file for appending. If filePath did not already exists, it is created. When
	// an existing file is opened with this method, the contents will not be
	// overwritten and the file pointer is positioned at the end of the file.
	// 
	// If the open/create failed, then error information will be available in the
	// FileOpenError and FileOpenErrorMsg properties.
	// 
	bool OpenForAppend(const char *filePath);


	// Opens a file for reading. The file may contain any type of data (binary or text)
	// and it must already exist. If the open failed, then error information will be
	// available in the FileOpenError and FileOpenErrorMsg properties.
	bool OpenForRead(const char *filePath);


	// Opens a file for reading/writing. If filePath did not already exists, it is created.
	// When an existing file is opened with this method, the contents will not be
	// overwritten, but the file pointer is positioned at the beginning of the file.
	// 
	// If the open/create failed, then error information will be available in the
	// FileOpenError and FileOpenErrorMsg properties.
	// 
	bool OpenForReadWrite(const char *filePath);


	// Opens a file for writing. If filePath did not already exists, it is created. When an
	// existing file is opened with this method, the contents will be overwritten. (For
	// example, calling OpenForWrite on an existing file and then immediately closing
	// the file will result in an empty file.) If the open/create failed, then error
	// information will be available in the FileOpenError and FileOpenErrorMsg
	// properties.
	bool OpenForWrite(const char *filePath);


	// Reads the entire contents of a binary file and returns it as an encoded string
	// (using an encoding such as Base64, Hex, etc.) The encoding may be one of the
	// following strings: base64, hex, qp, or url.
	bool ReadBinaryToEncoded(const char *filePath, const char *encoding, CkString &outStr);

	// Reads the entire contents of a binary file and returns it as an encoded string
	// (using an encoding such as Base64, Hex, etc.) The encoding may be one of the
	// following strings: base64, hex, qp, or url.
	const char *readBinaryToEncoded(const char *filePath, const char *encoding);

	// Reads the Nth block of a file, where the size of each block is specified by
	// blockSize. The first block is at blockIndex 0. If the block to be read is the last in the
	// file and there is not enough data to fill an entire block, then the partial
	// block is returned.
	bool ReadBlock(int blockIndex, int blockSize, CkByteData &outBytes);


	// Reads the entire contents of a binary file and returns the data.
	bool ReadEntireFile(const char *filePath, CkByteData &outBytes);


	// Reads the entire contents of a text file, interprets the bytes according to the
	// character encoding specified by charset, and returns the text file as a string.
	bool ReadEntireTextFile(const char *filePath, const char *charset, CkString &outStrFileContents);

	// Reads the entire contents of a text file, interprets the bytes according to the
	// character encoding specified by charset, and returns the text file as a string.
	const char *readEntireTextFile(const char *filePath, const char *charset);

	// Reassembles a file previously split by the SplitFile method.
	bool ReassembleFile(const char *partsDirPath, const char *partPrefix, const char *partExtension, const char *reassembledFilename);


	// Replaces all occurrences of existingString with replacementString in a file. The character encoding,
	// such as utf-8, ansi, etc. is specified by charset.
	int ReplaceStrings(const char *filePath, const char *charset, const char *existingString, const char *replacementString);


	// Sets the current working directory for the calling process to dirPath.
	bool SetCurrentDir(const char *dirPath);


	// Sets the create date/time, the last-access date/time, and the last-modified
	// date/time for a file. For non-Windows filesystems where create times are not
	// implemented, the createTime is ignored.
	bool SetFileTimes(const char *filePath, CkDateTime &createTime, CkDateTime &lastAccessTime, CkDateTime &lastModTime);


	// Sets the last-modified date/time for a file.
	bool SetLastModified(const char *filePath, CkDateTime &lastModified);


	// Splits a file into chunks. Please refer to the example below:
	bool SplitFile(const char *fileToSplit, const char *partPrefix, const char *partExtension, int partSize, const char *destDir);


	// Deletes an entire directory tree (all files and sub-directories).
	bool TreeDelete(const char *path);


	// Opens/creates filePath, writes fileData, and closes the file.
	bool WriteEntireFile(const char *filePath, CkByteData &fileData);


	// Opens filePath, writes textData using the character encoding specified by charset, and
	// closes the file. If includedPreamble is true and the charset is Unicode or utf-8, then the
	// BOM is included at the beginning of the file.
	bool WriteEntireTextFile(const char *filePath, const char *textData, const char *charset, bool includedPreamble);






	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
