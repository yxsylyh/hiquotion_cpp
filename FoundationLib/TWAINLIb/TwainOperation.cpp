#include "stdafx.h"
#include "TwainOperation.h"
#include <C++/FoundationLib/TWAINLIb/TWAINDSM/include/TwainString.h>
#include "DataEvent.h"

/**
* gloabals
*/
CTwainOperation* g_pTWAINApp = NULL;
extern bool gUSE_CALLBACKS;    // defined in TwainApp.cpp

//////////////////////////////////////////////////////////////////////////////
/**
* Callback funtion for DS.  This is a callback function that will be called by
* the source when it is ready for the application to start a scan. This
* callback needs to be registered with the DSM before it can be called.
* It is important that the application returns right away after recieving this
* message.  Set a flag and return.  Do not process the callback in this function.
*/
TW_UINT16 FAR PASCAL DSMCallback(pTW_IDENTITY _pOrigin,
	pTW_IDENTITY _pDest,
	TW_UINT32    _DG,
	TW_UINT16    _DAT,
	TW_UINT16    _MSG,
	TW_MEMREF    _pData)
{
	UNUSEDARG(_pDest);
	UNUSEDARG(_DG);
	UNUSEDARG(_DAT);
	UNUSEDARG(_pData);

	TW_UINT16 twrc = TWRC_FAILURE;
	// _pData stores the RefCon from the when the callback was registered
	// RefCon is a TW_INT32 and can not store a pointer for 64bit

	// we are only waiting for callbacks from our datasource, so validate
	// that the originator.
	if (0 != _pOrigin
		&& 0 != g_pTWAINApp
		&& g_pTWAINApp->getDataSource()
		&& _pOrigin->Id == g_pTWAINApp->getDataSource()->Id)
	{
		switch (_MSG)
		{
		case MSG_XFERREADY:
		case MSG_CLOSEDSREQ:
		case MSG_CLOSEDSOK:
		case MSG_NULL:
			g_pTWAINApp->m_DSMessage = _MSG;
			twrc = TWRC_SUCCESS;
			break;

		default:
			TRACE("Error - Unknown message in callback routine");
			g_pTWAINApp->m_DSMessage = MSG_NULL;
			twrc = TWRC_FAILURE;
			break;
		}
	}

	// Force a refresh, so that we process the message...
	HWND hwnd = g_pTWAINApp->getParent();
	if(hwnd)
		CWnd::FromHandle(hwnd)->RedrawWindow();

	// All done...
	return twrc;
}

CTwainOperation::CTwainOperation(HWND hwnd)
 	: TwainApp(hwnd),
	m_bKeepEnabled(FALSE)
{
	TW_IDENTITY* pAppID = getAppIdentity();

	pAppID->Version.MajorNum = 1;
	pAppID->Version.MinorNum = 0;
	pAppID->Version.Language = TWLG_ENGLISH_CANADIAN;
	pAppID->Version.Country = TWCY_CANADA;
	SSTRCPY(pAppID->Version.Info, sizeof(pAppID->Version.Info), "1.0");
	pAppID->ProtocolMajor = TWON_PROTOCOLMAJOR;
	pAppID->ProtocolMinor = TWON_PROTOCOLMINOR;
	pAppID->SupportedGroups = DF_APP2 | DG_IMAGE | DG_CONTROL;
	SSTRCPY(pAppID->Manufacturer, sizeof(pAppID->Manufacturer), "HIQ Studio");
	SSTRCPY(pAppID->ProductFamily, sizeof(pAppID->ProductFamily), "TWAIN Component");
	SSTRCPY(pAppID->ProductName, sizeof(pAppID->ProductName), "TWAIN Operation Wrapper Class");

	g_pTWAINApp = this;
}

CTwainOperation::~CTwainOperation()
{
	if (m_DSMState >= 4)
		disableDS();

	exit();
	disconnectDSM();
}

int CTwainOperation::getDataSourceCount()
{
	CStringArray dataSourceNames;
	return getDataSourceNames(dataSourceNames);
}

int CTwainOperation::getDataSourceNames(CStringArray& dataSourceNames)
{
	pTW_IDENTITY pID = NULL;
	int   i = 0;
	int   index = 0;
	int   nDefault = -1;

	bool ret = connectDSM();
	if (!ret)
		return -1;

	while (NULL != (pID = getDataSource((TW_INT16)i)))
	{
		index = dataSourceNames.Add(pID->ProductName);
		if (-1 == index)
		{
			break;
		}

		i++;
	}

	exit();
	disconnectDSM();

	return i;
}

BOOL CTwainOperation::showUI(HWND parent, int dsIndex)
{
	if (!parent)
	{
		setErrMsg("参数有误！父窗口为空。");
		return FALSE;
	}

	if (m_DSMState > 4)
	{
		setErrMsg("");
		return TRUE; // Already Enabled
	}

	bool ret = connectDSM();
	if (!ret)
		return FALSE;

	pTW_IDENTITY pID = NULL;
	pID = getDataSource((TW_INT16)dsIndex);
	if (!pID)
	{
		setErrMsg(PrintCMDMessage("不存在索引为 %d 的设备。", dsIndex));
		return FALSE;
	}

	ret = loadDS(pID->Id);
	if (!ret)
		return FALSE;

// 	if (m_DSMState < 4)
// 		return FALSE;

	m_DSMessage = (TW_UINT16)-1;

	// -Enable the data source. This puts us in state 5 which means that we
	// have to wait for the data source to tell us to move to state 6 and
	// start the transfer.  Once in state 5, no more set ops can be done on the
	// caps, only get ops.
	// -The scan will not start until the source calls the callback function
	// that was registered earlier.
	if (!enableDS(parent, /* m_bShowUI */ FALSE))
	{
		exit();
		disconnectDSM();
		m_bBusy = false;
		return FALSE;
	}

	do // If showing UI and KeepUIOpen is Enabled then we will loop here until cancle
	{

		// now we have to wait until we hear something back from the DS.
		while ((TW_UINT16)-1 == m_DSMessage)
		{

			// If we are using callbacks, there is nothing to do here except sleep
			// and wait for our callback from the DS.  If we are not using them, 
			// then we have to poll the DSM.
			MSG Msg;

			if (!GetMessage((LPMSG)& Msg, NULL, 0, 0))
			{
				break;//WM_QUIT
			}
			TW_EVENT twEvent = { 0 };
			twEvent.pEvent = (TW_MEMREF)& Msg;
			twEvent.TWMessage = MSG_NULL;
			TW_UINT16  twRC = TWRC_NOTDSEVENT;
			twRC = _DSM_Entry(getAppIdentity(),
				m_pDataSource,
				DG_CONTROL,
				DAT_EVENT,
				MSG_PROCESSEVENT,
				(TW_MEMREF)& twEvent);

			if (!gUSE_CALLBACKS && twRC == TWRC_DSEVENT)
			{
				// check for message from Source
				switch (twEvent.TWMessage)
				{
				case MSG_XFERREADY:
				case MSG_CLOSEDSREQ:
				case MSG_NULL:
					m_DSMessage = twEvent.TWMessage;
					break;

				case MSG_CLOSEDSOK:
// 					TRACE("\nError - MSG_CLOSEDSOK in MSG_PROCESSEVENT loop for Scan\n");
					break;

				default:
// 					TRACE("\nError - Unknown message in MSG_PROCESSEVENT loop for Scan\n");
					break;
				}
			}
			if (twRC != TWRC_DSEVENT)
			{
				TranslateMessage((LPMSG)& Msg);
				DispatchMessage((LPMSG)& Msg);
			}
		}

		// At this point the source has sent us a callback saying that it is ready to
		// transfer the image.

		if (m_DSMessage == MSG_XFERREADY)
		{
			// move to state 6 as a result of the data source. We can start a scan now.
			m_DSMState = 6;
			updateIMAGEINFO();
			StartScan();
			m_DSMessage = (TW_UINT16)-1;
		}
	} while (/* m_bShowUI && */ m_bKeepEnabled && m_DSMessage != MSG_CLOSEDSREQ);

	// Scan is done, disable the ds, thus moving us back to state 4 where we
	// can negotiate caps again.
	disableDS();
	exit();
	disconnectDSM();

	m_bBusy = false;

	return TRUE;
}

void CTwainOperation::StartScan()
{
	TW_UINT32       mech;
	TW_CAPABILITY   Cap;

	Cap.Cap = ICAP_XFERMECH;
	Cap.hContainer = 0;

	if (TWCC_SUCCESS != get_CAP(Cap, MSG_GETCURRENT)
		|| !getCurrent(&Cap, mech))
	{
		TRACE("Error: could not get the transfer mechanism");
		return;
	}

	if (Cap.hContainer)
	{
		_DSM_Free(Cap.hContainer);
	}

	switch ((TW_UINT16)mech)
	{
	case TWSX_NATIVE:
	case TWSX_FILE:
	case TWSX_MEMORY:
		Transfer();
		break;

// 	case TWSX_NATIVE:
// 		initiateTransfer_Native();
// 		break;
// 
// 	case TWSX_FILE:
// 	{
// 		TW_UINT32 fileformat = TWFF_TIFF;
// 		Cap.Cap = ICAP_IMAGEFILEFORMAT;
// 		Cap.hContainer = 0;
// 
// 		if (TWCC_SUCCESS == get_CAP(Cap, MSG_GETCURRENT))
// 		{
// 			getCurrent(&Cap, fileformat);
// 		}
// 
// 		if (Cap.hContainer)
// 		{
// 			_DSM_Free(Cap.hContainer);
// 		}
// 
// 		initiateTransfer_File((TW_UINT16)fileformat);
// 	}
// 	break;
// 
// 	case TWSX_MEMORY:
// 		initiateTransfer_Memory();
// 		break;
	}

	return;
}

void CTwainOperation::Transfer()
{
	PrintCMDMessage("app: Starting a TWSX_NATIVE transfer...\n");

	TW_STR255   szOutFileName;
	bool        bPendingXfers = true;
	TW_UINT16   twrc = TWRC_SUCCESS;
	string      strPath = m_strSavePath;

// 	if (strlen(strPath.c_str()))
// 	{
// 		if (strPath[strlen(strPath.c_str()) - 1] != PATH_SEPERATOR)
// 		{
// 			strPath += PATH_SEPERATOR;
// 		}
// 	}

	while (bPendingXfers)
	{
		m_nXferNum++;
		memset(szOutFileName, 0, sizeof(szOutFileName));

		if (!updateIMAGEINFO())
		{
			break;
		}
		// The data returned by ImageInfo can be used to determine if this image is wanted.
		// If it is not then DG_CONTROL / DAT_PENDINGXFERS / MSG_ENDXFER can be 
		// used to skip to the next image.

		TW_MEMREF hImg = 0;

		PrintCMDMessage("app: Starting the transfer...\n");
		twrc = DSM_Entry(DG_IMAGE, DAT_IMAGENATIVEXFER, MSG_GET, (TW_MEMREF)& hImg);

		if (TWRC_XFERDONE == twrc)
		{
			// -Here we get a handle to a DIB. Save it to disk as a bmp. 
			// -After saving it to disk, I could open it up again using FreeImage
			// if I wanted to do more transforms on it or save it as a different format.
			PBITMAPINFOHEADER pDIB = (PBITMAPINFOHEADER)_DSM_LockMemory(hImg);

			if (0 == pDIB)
			{
				setErrMsg(printErrorMsg(m_pDataSource, "App: Unable to lock memory, transfer failed"));
				break;
			}

			// Set the filename to save to
// 			SSNPRINTF(szOutFileName, sizeof(szOutFileName), sizeof(szOutFileName), "%sFROM_SCANNER_%06dN.bmp", strPath.c_str(), m_nXferNum);

			// Save the image to disk
// 			FILE* pFile;
// 			FOPEN(pFile, szOutFileName, "wb");
// 			if (pFile == 0)
// 			{
// 				perror("fopen");
// 			}
// 			else
// 			{
				DWORD dwPaletteSize = 0;

				switch (pDIB->biBitCount)
				{
				case 1:
					dwPaletteSize = 2;
					break;
				case 8:
					dwPaletteSize = 256;
					break;
				case 24:
					break;
				default:
					assert(0); //Not going to work!
					break;
				}

				// If the driver did not fill in the biSizeImage field, then compute it
				// Each scan line of the image is aligned on a DWORD (32bit) boundary
				if (pDIB->biSizeImage == 0)
				{
					pDIB->biSizeImage = ((((pDIB->biWidth * pDIB->biBitCount) + 31) & ~31) / 8) * pDIB->biHeight;

					// If a compression scheme is used the result may infact be larger
					// Increase the size to account for this.
					if (pDIB->biCompression != 0)
					{
						pDIB->biSizeImage = (pDIB->biSizeImage * 3) / 2;
					}
				}

				int nImageSize = pDIB->biSizeImage + (sizeof(RGBQUAD) * dwPaletteSize) + sizeof(BITMAPINFOHEADER);

				BITMAPFILEHEADER bmpFIH = { 0 };
				bmpFIH.bfType = ((WORD)('M' << 8) | 'B');
				bmpFIH.bfSize = nImageSize + sizeof(BITMAPFILEHEADER);
				bmpFIH.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * dwPaletteSize);

				char* imgData = new char[bmpFIH.bfSize];
				memcpy(imgData, &bmpFIH, sizeof(BITMAPFILEHEADER));
				memcpy(imgData + sizeof(BITMAPFILEHEADER), pDIB, nImageSize);

				CDataEvent evt(this, "DataGot", imgData, bmpFIH.bfSize);
				DataGot.raiseEvent(this, &evt);

				delete imgData;

// 				fwrite(&bmpFIH, 1, sizeof(BITMAPFILEHEADER), pFile);
// 				fwrite(pDIB, 1, nImageSize, pFile);
// 				fclose(pFile);
//  				pFile = 0;

// 				PrintCMDMessage("app: File \"%s\" saved...\n", szOutFileName);
// #ifdef _WINDOWS
// 				ShellExecute(m_Parent, "open", szOutFileName, NULL, NULL, SW_SHOWNORMAL);
// #endif
// 			}

			_DSM_UnlockMemory(hImg);
			_DSM_Free(hImg);
			pDIB = 0;

			updateEXTIMAGEINFO();

			// see if there are any more transfers to do
			PrintCMDMessage("app: Checking to see if there are more images to transfer...\n");
			TW_PENDINGXFERS pendxfers;
			memset(&pendxfers, 0, sizeof(pendxfers));

			twrc = DSM_Entry(DG_CONTROL, DAT_PENDINGXFERS, MSG_ENDXFER, (TW_MEMREF)& pendxfers);

			if (TWRC_SUCCESS == twrc)
			{
				PrintCMDMessage("app: Remaining images to transfer: %u\n", pendxfers.Count);

				if (0 == pendxfers.Count)
				{
					// nothing left to transfer, finished.
					bPendingXfers = false;
				}
			}
			else
			{
				setErrMsg(printErrorMsg(m_pDataSource, "failed to properly end the transfer"));
				bPendingXfers = false;
			}
		}
		else if (TWRC_CANCEL == twrc)
		{
		printError(m_pDataSource, "Canceled transfer image");
			break;
		}
		else if (TWRC_FAILURE == twrc)
		{
		setErrMsg(printErrorMsg(m_pDataSource, "Failed to transfer image"));
			break;
		}
	}

	// Check to see if we left the scan loop before we were actualy done scanning
	// This will hapen if we had an error.  Need to let the DS know we are not going 
	// to transfer more images
	if (bPendingXfers == true)
	{
		twrc = DoAbortXfer();
	}

	// adjust our state now that the scanning session is done
	m_DSMState = 5;

	PrintCMDMessage("app: DONE!\n");

	setErrMsg("");
	return;
}
