/*
**	FILENAME			CSerialPort.cpp
**
**	PURPOSE 			This class can read, write and watch one serial port.
**						It sends messages to its owner when something happends on the
port
**						The class creates a thread for reading and writing so the
main
**						program is not blocked.
**
**	CREATION DATE		15-09-1997
**	LAST MODIFICATION	24-11-1998
**
**	AUTHOR				Remon Spekreijse
**	MODIFIED BY			Brian Koh Sze Hsian
**
*/

#include "stdafx.h"
#include "SerialPort.h"

#include <assert.h>
 
//
// Constructor
//
CSerialPort::CSerialPort()
{
	m_hComm = NULL;

	// initialize overlapped structure members to zero
	m_ov.Offset = 0;
	m_ov.OffsetHigh = 0;

	// create events
	m_ov.hEvent = NULL;
	m_rov.hEvent = NULL;
	m_wov.hEvent = NULL;
	m_hWriteEvent = NULL;
	m_hShutdownEvent = NULL;
	m_hReadCompleteEvent = NULL;

	m_szWriteBuffer = NULL;
	m_nWriteCount = 0;

	m_bThreadAlive = FALSE;

	m_bStatusPending = FALSE;
	m_bReadPending = FALSE;
	m_bWritePending = FALSE;

	m_bReadComplete = TRUE;
	m_nReadCount = 0;

}

//
// Delete dynamic memory
//
CSerialPort::~CSerialPort()
{
	do
	{
		SetEvent(m_hShutdownEvent);
	} while (m_bThreadAlive);

	// if the port is still opened: close it
	if (m_hComm != NULL)
	{
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}

	TRACE("Thread ended\n");

	delete [] m_szWriteBuffer;

}

//
// Initialize the port. This can be port 1 to 4.
//
BOOL CSerialPort::InitPort(COleControl* pPortOwner
			   , LPCTSTR szPort
			   , LPCTSTR szMode
			   , DWORD dwCommEvents)
{
	if (pPortOwner == NULL)
	    return FALSE;

	// if the thread is alive: Kill
	if (m_bThreadAlive)
	{
	    SetEvent(m_hShutdownEvent);
	}

	// create events
	if (m_ov.hEvent != NULL)
	{
	    ResetEvent(m_ov.hEvent);
	    CloseHandle(m_ov.hEvent);
	}
	m_ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_rov.hEvent != NULL)
	{
	    ResetEvent(m_rov.hEvent);
	    CloseHandle(m_rov.hEvent);
	}
	m_rov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_wov.hEvent != NULL)
	{
	    ResetEvent(m_wov.hEvent);
	    CloseHandle(m_wov.hEvent);
	}
	m_wov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_hWriteEvent != NULL)
	{
	    ResetEvent(m_hWriteEvent);
	    CloseHandle(m_hWriteEvent);
	}
	m_hWriteEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	if (m_hShutdownEvent != NULL)
	{
	    ResetEvent(m_hShutdownEvent);
	    CloseHandle(m_hShutdownEvent);
	}
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_hReadCompleteEvent != NULL)
	{
	    ResetEvent(m_hReadCompleteEvent);
	    CloseHandle(m_hReadCompleteEvent);
	}
	m_hReadCompleteEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// initialize the event objects
	m_hEventArray[0] = m_hShutdownEvent;	// highest priority
	m_hEventArray[1] = m_hReadCompleteEvent;
	m_hEventArray[2] = m_hWriteEvent;
	m_hEventArray[3] = m_rov.hEvent;
	m_hEventArray[4] = m_wov.hEvent;
	m_hEventArray[5] = m_ov.hEvent;

	// set buffersize for writing and save the owner
	m_pOwner = pPortOwner;
	m_dwCommEvents = dwCommEvents;

	BOOL bResult = FALSE;

	// if the port is already opened: close it
	if (m_hComm != NULL)
	{
	    CloseHandle(m_hComm);
	    m_hComm = NULL;
	}

	// get a handle to the port
	m_hComm = CreateFile(szPort			    // communication port string (COMX)
			    , GENERIC_READ | GENERIC_WRITE  // read/write types
			    , 0 			    // comm devices must be opened with exclusive access
			    , NULL			    // no security attributes
			    , OPEN_EXISTING		    // comm devices must use OPEN_EXISTING
			    , FILE_FLAG_OVERLAPPED	    // Async I/O
			    , 0);			    // template must be 0 for comm devices

	if (m_hComm == INVALID_HANDLE_VALUE)
	{
	    // port not found
	    return FALSE;
	}

	m_strName = szPort;

	// set the timeout values
	m_CommTimeouts.ReadIntervalTimeout = MAXDWORD;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	m_CommTimeouts.ReadTotalTimeoutConstant = 0;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.WriteTotalTimeoutConstant = 1000;

	// configure
	if (!SetCommTimeouts(m_hComm, &m_CommTimeouts))
	{						   
	    ProcessErrorMessage("SetCommTimeouts()");
	}

	if (!GetCommState(m_hComm, &m_dcb))
	{
	    ProcessErrorMessage("GetCommState()");
	}

	if (!BuildCommDCB(szMode, &m_dcb))
	{
	    ProcessErrorMessage("BuildCommDCB()");
	}

	// Set initial state for modem controls
	m_dcb.fRtsControl = RTS_CONTROL_DISABLE;
	m_dcb.fDtrControl = DTR_CONTROL_DISABLE;
	m_dcb.fInX = FALSE;
	m_dcb.fOutX = FALSE;
	m_dcb.fOutxCtsFlow = FALSE;
	m_dcb.fOutxDsrFlow = FALSE;
	m_dcb.fBinary = TRUE;
	m_dcb.fDsrSensitivity = FALSE;

	m_bRTSFlow = FALSE;
	m_bCTSFlow = FALSE;
	m_bInputXonXoff = FALSE;
	m_bOutputXonXoff = FALSE;
	m_bDSRSensitive = FALSE;

	m_bDTR = FALSE;
	m_bRTS = FALSE;
	m_bDSR = FALSE;
	m_bCTS = FALSE;
	m_bRLSD = FALSE;
	m_bRING = FALSE;

	if (!SetCommState(m_hComm, &m_dcb))
	{
	    ProcessErrorMessage("SetCommState()");
	}

	// flush the port
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);


	TRACE("Initialisation for communicationport %s completed.\nUse Startmonitor to communicate.\n", szPort);
	
	// Now check to see if any modem i/p lines are already on...
	DWORD dwModemStat;
	GetCommModemStatus(m_hComm, &dwModemStat);	// Get modem status
	
	if ((dwModemStat & MS_RLSD_ON) == MS_RLSD_ON)	// If DCD (sorry! RLSD)
	    m_pOwner->SendMessage(WM_COMM_RLSD_DETECTED // Inform parent
				, (WPARAM) TRUE
				, (LPARAM) this);

	if ((dwModemStat & MS_DSR_ON) == MS_DSR_ON) // If DSR on
	    m_pOwner->SendMessage(WM_COMM_DSR_DETECTED // Inform user
				, (WPARAM) TRUE
				, (LPARAM) this);
	
	if ((dwModemStat & MS_CTS_ON) == MS_CTS_ON) // If CTS on...
	    m_pOwner->SendMessage(WM_COMM_CTS_DETECTED // Inform parent
				, (WPARAM) TRUE
				, (LPARAM) this);
	
	if ((dwModemStat & MS_RING_ON) == MS_RING_ON)	// If RING indicate...
	    m_pOwner->SendMessage(WM_COMM_RING_DETECTED // Inform parent
				, (WPARAM) TRUE
				, (LPARAM) this);

	return TRUE;
}

//
//	The CommThread Function.
//
void	CommThread(LPVOID pParam)
{
	CSerialPort *port = (CSerialPort*) pParam;  // Get serial device
	
	port->m_bThreadAlive = TRUE; 	    // Flag thread running
		
	DWORD Event = 0;
	DWORD dwError = 0;

	// Set COM mask for desired notifiction
	if (!SetCommMask(port->m_hComm, port->m_dwCommEvents))
	{
	    port->ProcessErrorMessage("SetCommMask()");
	}
	
	while (TRUE) 
	{
						    // Wait for work
	    int nEventNumb = WaitForMultipleObjects(6
						    , port->m_hEventArray
						    , FALSE
						    , 1000);
	    
	    if (nEventNumb == WAIT_TIMEOUT)	    // Timed out ?
	    {
		port->GetCommStatus();		    // Go request a status check
		continue;			    // Return to wait
	    }

	    switch (nEventNumb - WAIT_OBJECT_0)     // Branch on event
	    {
	    case 0:				    // Termination event
		port->m_bThreadAlive = FALSE;	    // Clear running flag
		AfxEndThread(0);		    // .. exit thread

	    case 1:				    // User completed a read...
		port->ResetRead();		    // Go prepare for next read
		break;

	    case 2:				    // User requested a write
		port->WriteChar();		    // Go start write operation
		break;
	    
	    case 3:				    // Read completed
		port->GetReadResult();		    // Go post results to user
		break;

	    case 4:				    // Write completed
		port->GetWriteResult();		    // Go post results to user
		break;

	    case 5:				    // WaitCommStatus completed...
		port->GetCommStatusResult();     // Go action current status
		port->GetCommStatus();		    // Fire off another 
		break;

	    }

	} // close forever loop

}

//
// start comm watching
//
BOOL CSerialPort::StartMonitoring()
{
	if (!(m_Thread = AfxBeginThread((AFX_THREADPROC) CommThread, (LPVOID) this)))
	    return FALSE;
	TRACE("Thread started\n");
	return TRUE;	
}

//
// Restart the comm thread
//
BOOL CSerialPort::RestartMonitoring()
{
	TRACE("Thread resumed\n");
	m_Thread->ResumeThread();
	return TRUE;	
}


//
// Suspend the comm thread
//
BOOL CSerialPort::StopMonitoring()
{
	TRACE("Thread suspended\n");
	do
	{
		SetEvent(m_hShutdownEvent);
	} while (m_bThreadAlive);

	// if the port is still opened: close it
	if (m_hComm != NULL)
	{
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}

	TRACE("Thread ended\n");

	delete [] m_szWriteBuffer;


	return TRUE;	
}


//
// If there is a error, give the right message
//
void CSerialPort::ProcessErrorMessage(char* ErrorText)
{
	char *Temp = new char[200];
	
	LPVOID lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	sprintf(Temp
		, "WARNING:  %s Failed with the following error: \n%s\nPort: %s\n"
		, (char*)ErrorText
		, lpMsgBuf
		, (LPCTSTR) m_strName); 

	MessageBox(NULL, Temp, "Application Error", MB_ICONSTOP);

	LocalFree(lpMsgBuf);
	delete[] Temp;
}

//
// Write a character.
//
void CSerialPort::WriteChar()
{
	BOOL bWrite = TRUE;
	BOOL bResult = TRUE;

	DWORD BytesSent = 0;

	ResetEvent(m_hWriteEvent);

	if (m_nWriteCount == 0) 		    // If No chars to write
	{
	    m_pOwner->SendMessage(WM_COMM_TXEMPTY_DETECTED // Inform user again
				, (WPARAM) 0
				, (LPARAM) this);
	    return;
	}
	
	// Initailize variables
	m_wov.Offset = 0;
	m_wov.OffsetHigh = 0;

	bResult = WriteFile(m_hComm		    // Handle to COMM Port
			    , m_pWrBuff 	    // Pointer to message buffer in calling finction
			    , m_nWriteCount	    // Length of message to send
			    , &BytesSent	    // Where to store the number of bytes sent
			    , &m_wov);		    // Overlapped structure

	m_bWritePending = FALSE;		    // Assume immediate completion
	if (!bResult)				    // If failure
	{
	    int nError; 			    // Temp for error code

	    if ((nError = GetLastError()) != ERROR_IO_PENDING) // If not deffered
	    {
		ProcessErrorMessage("WriteFile()");
	    }
	    else
	    {
		m_bWritePending = TRUE;
	    }
	} 
	else
	{
		    SetCommMask(m_hComm, m_dwCommEvents);   // Re-enable Tx ready notification
	    ResetEvent(m_wov.hEvent);		    // Reset write complete event
	    if (m_pOwner->m_hWnd != NULL)
		m_pOwner->SendMessage(WM_COMM_TXCOMPLETE // Inform parent
				    , (WPARAM) BytesSent
				    , (LPARAM) this);

	}

}

//
// Character received. Inform the owner
//
void CSerialPort::ReceiveChar()
{
	BOOL  bResult;
	DWORD dwError;
	COMSTAT comstat;

	if (m_bReadComplete)			    // If last read complete
	{ 
	    bResult = ClearCommError(m_hComm, &dwError, &comstat); // Get current comm status

	    m_nRdInQueue = comstat.cbInQue;	    // Save chars in i/p queue
	    if (m_nRdInQueue == 0)		    // If nothing...
		return; 			    // .. end here
						
	    m_bReadComplete = FALSE;		    // Flag read incomplete
	    if (m_pOwner->m_hWnd != NULL)
		m_pOwner->SendMessage(WM_COMM_RXCHAR    // Inform parent
				    , (WPARAM) m_nRdInQueue
				    , (LPARAM) this);
	}
}

int CSerialPort::Read(LPCTSTR szBuff, int nCount)
{
	BOOL  bResult;

	if (nCount <= 0)			    // Illegal read value
	    return 0;

	int nToRead = min(m_nRdInQueue, (DWORD) nCount);    // Calc read length
	    
	m_rov.Offset = 0;
	m_rov.OffsetHigh = 0;

	bResult = ReadFile(m_hComm		    // Go start off the read
			, (void *) szBuff
			, nToRead
			, &m_nReadCount
			, &m_rov);

	m_bReadPending = FALSE; 		    // Assume immediate completion

	if (!bResult)				    // If failure
	{ 
	    if (GetLastError() != ERROR_IO_PENDING) // If not read pending
	    {
		ProcessErrorMessage("ReadFile()");
		if (m_pOwner->m_hWnd != NULL)
		    m_pOwner->SendMessage(WM_COMM_ERR_DETECTED
					    , (WPARAM) 0
					    , (LPARAM) this);
		return -2;				// Return error
	    }
	    else
	    {
		m_bReadPending = TRUE;		    // Flag pending read
		return -1;			    // Flag deferred read
	    }
	}

	
	ResetEvent(m_rov.hEvent);		    // Reset read complete event
	return m_nReadCount;			    // Return actual bytes read
}


void	CSerialPort::GetReadResult()
{
	if (!m_bReadPending)			    // No read pending ?
	    return;				    // .. end here

	GetOverlappedResult(m_hComm		    // Get result of last read request
			    , &m_rov
			    , &m_nReadCount
			    , TRUE);

	ResetEvent(m_rov.hEvent);		    // Reset read completion event
	m_bReadPending = FALSE; 		    // A read is no longer pending
	m_bReadComplete = FALSE;		    // .. but user not complete yet

	if (m_pOwner->m_hWnd != NULL)
	    m_pOwner->SendMessage(WM_COMM_RXCOMPLETE    // Inform parent
				, (WPARAM) m_nReadCount
				, (LPARAM) this);
}

void CSerialPort::GetWriteResult()
{
	if (!m_bWritePending)			    // If no deferred write pending
	    return;				    // .. end here

	DWORD nCount;				    // Temp for bytes written

	GetOverlappedResult(m_hComm		    // Get write result
			    , &m_wov
			    , &nCount
			    , TRUE);
	
	ResetEvent(m_wov.hEvent);		    // Reset write complete event
	m_bWritePending = FALSE;		    // Flag no deferred write pending

	SetCommMask(m_hComm, m_dwCommEvents);	    // Enable full notification

	if (m_pOwner->m_hWnd != NULL)
	    m_pOwner->SendMessage(WM_COMM_TXCOMPLETE    // Inform parent
				, (WPARAM) nCount
				, (LPARAM) this);

}

void CSerialPort::ActionEvents()
{
	COMSTAT comstat;
	DWORD dwError;
	bool bTemp;

	ClearCommError(m_hComm, &dwError, &comstat); // Get current comm status

	if (comstat.cbOutQue == 0)		    // Space in output queue ?
	{
	    m_pOwner->SendMessage(WM_COMM_TXEMPTY_DETECTED // Inform parent
				, (WPARAM) 0
				, (LPARAM) this);

	    SetCommMask(m_hComm, m_dwCommEvents & ~EV_TXEMPTY); // Don't request TXREADY
	}

	if (dwError & CE_BREAK)			    // If break detected
	    m_pOwner->SendMessage(WM_COMM_BREAK_DETECTED // Inform parent
				, (WPARAM) 0
				, (LPARAM) this);

						    // If error
	if (dwError & (CE_FRAME|CE_RXPARITY|CE_IOE|CE_RXOVER|CE_OVERRUN|CE_TXFULL))
	    m_pOwner->SendMessage(WM_COMM_ERR_DETECTED // Inform parent
				, (WPARAM) 0
				, (LPARAM) this);

	
	DWORD dwModemStat;			    // Temp for modem status
	GetCommModemStatus(m_hComm, &dwModemStat);	// Go get status
	
						    // If change in CTS
	if ((bTemp = ((dwModemStat & MS_DSR_ON) == MS_DSR_ON)) != m_bCTS )
	{
	    m_bCTS = bTemp;			    // Set new CTS state
	    m_pOwner->SendMessage(WM_COMM_CTS_DETECTED // Inform parent
				, (WPARAM) bTemp
				, (LPARAM) this);
	}
						    // If change in DSR
	if ((bTemp = ((dwModemStat & MS_DSR_ON) == MS_DSR_ON)) != m_bDSR )
	{
	    m_bDSR = bTemp;			    // Set new DSR state
	    m_pOwner->SendMessage(WM_COMM_DSR_DETECTED // Inform user
				, (WPARAM) bTemp
				, (LPARAM) this);
	}
						    // If change in RLSD
	if ((bTemp = ((dwModemStat & MS_RLSD_ON) == MS_RLSD_ON)) != m_bRLSD)
	{
	    m_bRLSD = bTemp;			    // Set new state
	    m_pOwner->SendMessage(WM_COMM_RLSD_DETECTED // Inform parent
				, (WPARAM) bTemp
				, (LPARAM) this);
	}
						    // If ring ind changed
	if ((bTemp = ((dwModemStat & MS_RING_ON) == MS_RING_ON)) != m_bRING)
	{
	    m_bRING = bTemp;			    // Set new RING state
	    m_pOwner->SendMessage(WM_COMM_RING_DETECTED // Inform parent
				, (WPARAM) bTemp
				, (LPARAM) this);
	}
		    
	if (comstat.cbInQue > 0 && m_bReadComplete) // In data to read & last read complete
	    ReceiveChar();			    // Notify parent

}

void CSerialPort::GetCommStatusResult()
{
	DWORD nEvent = 0;

	GetOverlappedResult(m_hComm		    // Get status result
			    , &m_ov
			    , &nEvent
			    , TRUE);

	ResetEvent(m_ov.hEvent);		    // Reset status completed event
	m_bStatusPending = FALSE;		    // Clear pending flag

	COMSTAT comstat;
	DWORD dwError;
	    ClearCommError(m_hComm, &dwError, &comstat); // Get current comm status
	if (m_pOwner->m_hWnd != NULL)
	    ActionEvents();			    // Go action events
}

void CSerialPort::Write(LPCTSTR string, int nCount)
{		
	assert(m_hComm != 0);

	if (nCount > 0)				    // If bytes to write
	{
	    m_pWrBuff = string; 		    // Save user string
	    m_nWriteCount = nCount;		    // .. and byte count

	    // set event for write
	    SetEvent(m_hWriteEvent);		    // Set write request event
	}
}

void CSerialPort::ReadComplete()
{		
	SetEvent(m_hReadCompleteEvent); 	    // Set user completed read event
}

void CSerialPort::ResetRead()
{		
	m_bReadComplete = TRUE; 		    // Set completed flag
	ResetEvent(m_hReadCompleteEvent);	    // Reset read complete event
}


//
// Return the device control block
//
DCB CSerialPort::GetDCB()
{
	return m_dcb;
}

//
// Return the communication event masks
//
DWORD CSerialPort::GetCommEvents()
{
	return m_dwCommEvents;
}

//
// Return the output buffer size
//
DWORD CSerialPort::GetWriteBufferSize()
{
	return m_nWriteBufferSize;
}

void CSerialPort::GetCommStatus()
{

    if (m_bStatusPending)			    // If prev status request pending
	return; 				    // .. end here

    DWORD Event = 0;

    if (WaitCommEvent(m_hComm, &Event, &m_ov))	    // Request status
	{
	if (m_pOwner->m_hWnd != NULL)
	    ActionEvents();			    // Action events
	}
	else					    // Got deferred...
	{
	    if (GetLastError() != ERROR_IO_PENDING)
	    ProcessErrorMessage("WaitCommEvent()");
	else
	    m_bStatusPending = TRUE;
	}

}

bool CSerialPort::SetRTS(bool bState)
{
	if (m_bRTSFlow == TRUE) 		    // If RTS flow enabled
	return m_bRTS;				    // Return current state of RTS (means nothing now...)

    if (bState == m_bRTS)			    // If already in requested state
	return m_bRTS;				    // Just return RTS state

    if (bState)					    // If request to turn on...
	{
	EscapeCommFunction(m_hComm, SETRTS);	    // .. turn on RTS
	m_dcb.fRtsControl = RTS_CONTROL_ENABLE;     // ..reflect it in DCB
	}
	else
	{
	EscapeCommFunction(m_hComm, CLRRTS);	    // .. else turn off
	m_dcb.fRtsControl = RTS_CONTROL_DISABLE;    // .. 
	}

    return !(m_bRTS = bState);			    // Return prev RTS state
}

bool CSerialPort::SetDTR(bool bState)
{
	if (bState == m_bDTR)			    // If DTR already in req'd state
	return m_bDTR;				    // .. just return current state

    if (bState)					    // If requste to turn on...
	{
	EscapeCommFunction(m_hComm, SETDTR);	    // .. turn on DTR
	m_dcb.fDtrControl = DTR_CONTROL_ENABLE;
	}
	else
	{
	EscapeCommFunction(m_hComm, CLRDTR);	    // .. else turn off
	m_dcb.fDtrControl = DTR_CONTROL_DISABLE;
	}

    return !(m_bDTR = bState);

}

bool CSerialPort::GetRTS()
{
	return m_bRTS;				    // Current RTS state
}

bool CSerialPort::GetDTR()
{
	return m_bDTR;				    // Current DTR state
}

bool CSerialPort::GetRLSD()
{
	DWORD dwModemStat;

    GetCommModemStatus(m_hComm, &dwModemStat);
	return (dwModemStat & MS_RLSD_ON) == MS_RLSD_ON;
}

bool CSerialPort::GetDSR()
{
	DWORD dwModemStat;

    GetCommModemStatus(m_hComm, &dwModemStat);
	return (dwModemStat & MS_DSR_ON) == MS_DSR_ON;
}

bool CSerialPort::GetCTS()
{
	DWORD dwModemStat;

    GetCommModemStatus(m_hComm, &dwModemStat);
	return (dwModemStat & MS_CTS_ON) == MS_CTS_ON;
}

bool CSerialPort::GetRING()
{
	DWORD dwModemStat;

    GetCommModemStatus(m_hComm, &dwModemStat);
	return (dwModemStat & MS_RING_ON) == MS_RING_ON;
}

void CSerialPort::SetRTSFlow(bool bState)
{
	if ((m_bRTSFlow = bState) == TRUE)
	{
	m_bRTS = FALSE;
	m_dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	}
	else
	{
	m_bRTS = FALSE;
	m_dcb.fRtsControl = RTS_CONTROL_DISABLE;
	}
	
	if (!SetCommState(m_hComm, &m_dcb))
	{
	    ProcessErrorMessage("SetCommState()");
	}
}

void CSerialPort::SetCTSFlow(bool bState)
{
	if ((m_bCTSFlow = bState) == TRUE)
	{
	m_dcb.fOutxCtsFlow = TRUE;
	}
	else
	{
	m_dcb.fOutxCtsFlow = FALSE;
	}

    if (!SetCommState(m_hComm, &m_dcb))
	{
	    ProcessErrorMessage("SetCommState()");
	}
}

void CSerialPort::SetDSRSensetive(bool bState)
{
	if ((m_bDSRSensitive = bState) == TRUE)
	{
	m_dcb.fDsrSensitivity = TRUE;
	}
	else
	{
	m_dcb.fDsrSensitivity = FALSE;
	}

    if (!SetCommState(m_hComm, &m_dcb))
	{
	    ProcessErrorMessage("SetCommState()");
	}

}

void CSerialPort::SetInputXonXoff(bool bState)
{
	if ((m_bInputXonXoff = bState) == TRUE)
	{
	m_dcb.fInX = TRUE;
	}
	else
	{
	m_dcb.fInX = FALSE;
	}

    if (!SetCommState(m_hComm, &m_dcb))
	{
	    ProcessErrorMessage("SetCommState()");
	}

}

void CSerialPort::SetOutputXonXoff(bool bState)
{
	if ((m_bOutputXonXoff = bState) == TRUE)
	{
	m_dcb.fOutX = TRUE;
	}
	else
	{
	m_dcb.fOutX = FALSE;
	}

    if (!SetCommState(m_hComm, &m_dcb))
	{
	    ProcessErrorMessage("SetCommState()");
	}

}
