/*
**	FILENAME			CSerialPort.h
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
#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#define WM_COMM_BREAK_DETECTED		(WM_APP + 1)	// A break was detected on input.
#define WM_COMM_CTS_DETECTED		(WM_APP + 2)	// The CTS (clear-to-send) signal changed state. 
#define WM_COMM_DSR_DETECTED		(WM_APP + 3)	// The DSR (data-set-ready) signal changed state. 
#define WM_COMM_ERR_DETECTED		(WM_APP + 4)	// A line-status error occurred. Line-statuserrors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
#define WM_COMM_RING_DETECTED		(WM_APP + 5)	// A ring indicator was detected. 
#define WM_COMM_RLSD_DETECTED		(WM_APP + 6)	// The RLSD (receive-line-signal-detect)signal changed state. 
#define WM_COMM_RXCHAR				(WM_APP + 7)	// A character was received and placed in theinput buffer. 
#define WM_COMM_RXFLAG_DETECTED		(WM_APP + 8)	// The event character was received and placed in the input buffer.  
#define WM_COMM_TXEMPTY_DETECTED	(WM_APP + 9)	// The last character in the output buffer was sent. 

#define	WM_COMM_RXCOMPLETE			(WM_APP + 10)	// Last deffered read completed
#define	WM_COMM_TXCOMPLETE			(WM_APP + 11)	// Last deffered write completed
#include <afxctl.h>


class CSerialPort
{													     
   
public:
	bool m_bDSRSensitive;
	bool m_bOutputXonXoff;
	bool m_bInputXonXoff;
	bool m_bCTSFlow;
	bool m_bRTSFlow;
	void SetOutputXonXoff(bool bState);
	void SetInputXonXoff(bool bState);
	void SetDSRSensetive(bool bState);
	void SetCTSFlow(bool bState);
	void SetRTSFlow(bool bState);
	bool m_bRTS;
	bool m_bDTR;
	bool m_bDSR;
	bool m_bCTS;
	bool m_bRLSD;
	bool m_bRING;

	bool GetRING();
	bool GetCTS();
	bool GetDSR();
	bool GetRLSD();
	bool GetDTR();
	bool GetRTS();
	bool SetDTR(bool bState);
	bool SetRTS(bool bState);

	// contruction and destruction
	CSerialPort();
	virtual ~CSerialPort();

	// port initialisation										     
  
	BOOL	InitPort(COleControl* pPortOwner
			, LPCTSTR szPort
			, LPCTSTR szMode
			, DWORD dwCommEvents = EV_RXCHAR | EV_CTS);

	// start/stop comm watching
	BOOL	StartMonitoring();
	BOOL	RestartMonitoring();
	BOOL	StopMonitoring();
	bool	m_bThreadAlive;

	
	DWORD	GetWriteBufferSize();
	DWORD	GetCommEvents();
	DCB	GetDCB();

	int	Read(LPCTSTR szBuff, int nCount);
	void	Write(LPCTSTR string, int nCount);

	void	ReadComplete();
	void	ResetRead();

	void	ReceiveChar();
	void	WriteChar();
	void	GetCommStatus();
	void	GetReadResult();
	void	GetWriteResult();
	void	GetCommStatusResult();
	void	ActionEvents();
	void	ProcessErrorMessage(char* ErrorText);

	HANDLE	m_hComm;
	HANDLE	m_hEventArray[6];

	DWORD	m_dwCommEvents;
	bool	m_bStatusPending;

	unsigned char	m_pRxBuff[1024];
	DWORD	m_nReadCount;
	DWORD	m_nRdInQueue;
	bool	m_bReadComplete;
	bool	m_bReadPending;

	LPCTSTR m_pWrBuff;
	bool	m_bWritePending;

protected:
	// protected memberfunctions

	// thread
	CWinThread*	m_Thread;

	// synchronisation objects
	CRITICAL_SECTION m_csCommunicationSync;

	// handles
	HANDLE	m_hShutdownEvent;
	HANDLE	m_hWriteEvent;
	HANDLE	m_hReadCompleteEvent;

	// structures
	OVERLAPPED	m_ov;
	OVERLAPPED	m_rov;
	OVERLAPPED	m_wov;

	COMMTIMEOUTS	m_CommTimeouts;
	DCB	m_dcb;

	// owner window
	COleControl*	m_pOwner;

	// misc
	char*	m_szWriteBuffer;
	UINT	m_nWriteCount;
	DWORD	m_nWriteBufferSize;
	CString m_strName;
private:
};

void CommThread(LPVOID pParam);

#endif __SERIALPORT_H__
