// WinCamDlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "WinCam.h"
#include "WinCamDlg.h"
#include "configdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de diálogo de CWinCamDlg



CWinCamDlg::CWinCamDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CWinCamDlg::IDD, pParent)
	, m_strDisplay(_T("00"))
	, m_bFlash(false)
	, m_bConectado(false)
	, m_strPuerto(_T("COM1"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bFlash=FALSE;
}

void CWinCamDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ARRIBA, m_stArriba);
	DDX_Control(pDX, IDC_ARRIBADRCHA, m_stArribaDrcha);
	DDX_Control(pDX, IDC_DERECHA, m_stDerecha);
	DDX_Control(pDX, IDC_ABAJODRCHA, m_stAbajoDrcha);
	DDX_Control(pDX, IDC_ABAJO, m_stAbajo);
	DDX_Control(pDX, IDC_ABAJOIZDA, m_stAbajoIzda);
	DDX_Control(pDX, IDC_IZQUIERDA, m_stIzquierda);
	DDX_Control(pDX, IDC_ARRIBAIZDA, m_stArribaIzda);
	DDX_Control(pDX, IDC_DISPLAY, m_display);
	DDX_Control(pDX, IDC_TECLA1, m_stTecla1);
	DDX_Control(pDX, IDC_TECLA2, m_stTecla2);
	DDX_Control(pDX, IDC_TECLA3, m_stTecla3);
	DDX_Control(pDX, IDC_TECLA4, m_stTecla4);
	DDX_Control(pDX, IDC_TECLA5, m_stTecla5);
	DDX_Control(pDX, IDC_TECLA6, m_stTecla6);
	DDX_Control(pDX, IDC_TECLA7, m_stTecla7);
	DDX_Control(pDX, IDC_TECLA8, m_stTecla8);
	DDX_Control(pDX, IDC_TECLA9, m_stTecla9);
	DDX_Control(pDX, IDC_TECLA10, m_stTeclaAst);
	DDX_Control(pDX, IDC_TECLA11, m_stTecla0);
	DDX_Control(pDX, IDC_TECLA12, m_stTeclaAlm);
	DDX_Control(pDX, IDC_FOCOMAS, m_stFocoMas);
	DDX_Control(pDX, IDC_FOCOMENOS, m_stFocoMenos);
	DDX_Control(pDX, IDC_ZOOMMAS, m_stZoomMas);
	DDX_Control(pDX, IDC_ZOOMMENOS, m_stZoomMenos);
	DDX_Control(pDX, IDC_CONFIG, m_config);
	DDX_Control(pDX, IDC_CONECTAR, m_conectar);
	DDX_Control(pDX, IDC_LEDOFF, m_stLed);
}

BEGIN_MESSAGE_MAP(CWinCamDlg, CBitmapDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_ABAJO, OnStnClickedAbajo)
	ON_STN_CLICKED(IDC_ABAJODRCHA, OnStnClickedAbajodrcha)
	ON_STN_CLICKED(IDC_ABAJOIZDA, OnStnClickedAbajoizda)
	ON_STN_CLICKED(IDC_ARRIBA, OnStnClickedArriba)
	ON_STN_CLICKED(IDC_ARRIBADRCHA, OnStnClickedArribadrcha)
	ON_STN_CLICKED(IDC_ARRIBAIZDA, OnStnClickedArribaizda)
	ON_STN_CLICKED(IDC_DERECHA, OnStnClickedDerecha)
	ON_STN_CLICKED(IDC_IZQUIERDA, OnStnClickedIzquierda)

	ON_NOTIFY (WM_LBUTTONUP, IDC_ABAJO, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_ARRIBA, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_DERECHA, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_IZQUIERDA, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_ABAJOIZDA, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_ABAJODRCHA, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_ARRIBAIZDA, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_ARRIBADRCHA, OnAbajoLButtonUp)

	ON_NOTIFY (WM_LBUTTONUP, IDC_FOCOMAS, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_FOCOMENOS, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_ZOOMMAS, OnAbajoLButtonUp)
	ON_NOTIFY (WM_LBUTTONUP, IDC_ZOOMMENOS, OnAbajoLButtonUp)

	ON_MESSAGE(WM_COMM_RXCHAR, OnRxChar)
	ON_STN_CLICKED(IDC_TECLA1, OnStnClickedTecla1)
	ON_STN_CLICKED(IDC_TECLA10, OnStnClickedTeclaAst)
	ON_STN_CLICKED(IDC_TECLA11, OnStnClickedTecla0)
	ON_STN_CLICKED(IDC_TECLA12, OnStnClickedTeclaAlm)
	ON_STN_CLICKED(IDC_TECLA9, OnStnClickedTecla9)
	ON_STN_CLICKED(IDC_TECLA8, OnStnClickedTecla8)
	ON_STN_CLICKED(IDC_TECLA7, OnStnClickedTecla7)
	ON_STN_CLICKED(IDC_TECLA5, OnStnClickedTecla5)
	ON_STN_CLICKED(IDC_TECLA6, OnStnClickedTecla6)
	ON_STN_CLICKED(IDC_TECLA4, OnStnClickedTecla4)
	ON_STN_CLICKED(IDC_TECLA3, OnStnClickedTecla3)
	ON_STN_CLICKED(IDC_TECLA2, OnStnClickedTecla2)
//	ON_WM_CHAR()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_TIMER()
ON_STN_CLICKED(IDC_ZOOMMAS, OnStnClickedZoommas)
ON_STN_CLICKED(IDC_ZOOMMENOS, OnStnClickedZoommenos)
ON_STN_CLICKED(IDC_FOCOMAS, OnStnClickedFocomas)
ON_STN_CLICKED(IDC_FOCOMENOS, OnStnClickedFocomenos)
ON_BN_CLICKED(IDC_CONFIG, OnBnClickedConfig)
ON_BN_CLICKED(IDC_CONECTAR, OnBnClickedConectar)
END_MESSAGE_MAP()


// Controladores de mensaje de CWinCamDlg

BOOL CWinCamDlg::OnInitDialog()
{
	m_hAccel = ::LoadAccelerators(AfxGetResourceHandle(),
             MAKEINTRESOURCE(IDR_ACCELERATOR1));

	if (!m_hAccel)
	MessageBox("The accelerator table was not loaded");

	SetBitmap (IDB_FONDO);

	m_config.LoadBitmaps (IDB_CONFIG1,IDB_CONFIG2,IDB_CONFIG2,IDB_CONFIG1);
	m_conectar.LoadBitmaps (IDB_CONECTAR,IDB_CONECTAR2,IDB_CONECTAR2,IDB_CONECTAR);

	m_stAbajo.LoadButtonBitmaps (IDB_ABAJO,IDB_ABAJO,IDB_ABAJOP);
	m_stDerecha.LoadButtonBitmaps (IDB_DERECHA,IDB_DERECHA,IDB_DERECHAP);
	m_stIzquierda.LoadButtonBitmaps (IDB_IZQUIERDA,IDB_IZQUIERDA,IDB_IZQUIERDAP);
	m_stArriba.LoadButtonBitmaps (IDB_ARRIBA,IDB_ARRIBA,IDB_ARRIBAP);

	m_stArribaDrcha.LoadButtonBitmaps (IDB_ARRIBADRCHA,IDB_ARRIBADRCHA,IDB_ARRIBADRCHAP);
	m_stArribaIzda.LoadButtonBitmaps (IDB_ARRIBAIZDA,IDB_ARRIBAIZDA,IDB_ARRIBAIZDAP);

	m_stAbajoDrcha.LoadButtonBitmaps (IDB_ABAJODRCHA,IDB_ABAJODRCHA,IDB_ABAJODRCHAP);
	m_stAbajoIzda.LoadButtonBitmaps (IDB_ABAJOIZDA,IDB_ABAJOIZDA,IDB_ABAJOIZDAP);

	m_stFocoMas.LoadButtonBitmaps (IDB_MAS,IDB_MAS,IDB_MASP);
	m_stFocoMenos.LoadButtonBitmaps (IDB_MENOS,IDB_MENOS,IDB_MENOSP);
	m_stZoomMas.LoadButtonBitmaps (IDB_MAS,IDB_MAS,IDB_MASP);
	m_stZoomMenos.LoadButtonBitmaps (IDB_MENOS,IDB_MENOS,IDB_MENOSP);

	m_stTecla0.LoadButtonBitmaps (IDB_TECLA0,IDB_TECLA0,IDB_TECLA0P);
	m_stTecla1.LoadButtonBitmaps (IDB_TECLA1,IDB_TECLA1,IDB_TECLA1P);
	m_stTecla2.LoadButtonBitmaps (IDB_TECLA2,IDB_TECLA2,IDB_TECLA2P);
	m_stTecla3.LoadButtonBitmaps (IDB_TECLA3,IDB_TECLA3,IDB_TECLA3P);
	m_stTecla4.LoadButtonBitmaps (IDB_TECLA4,IDB_TECLA4,IDB_TECLA4P);
	m_stTecla5.LoadButtonBitmaps (IDB_TECLA5,IDB_TECLA5,IDB_TECLA5P);
	m_stTecla6.LoadButtonBitmaps (IDB_TECLA6,IDB_TECLA6,IDB_TECLA6P);
	m_stTecla7.LoadButtonBitmaps (IDB_TECLA7,IDB_TECLA7,IDB_TECLA7P);
	m_stTecla8.LoadButtonBitmaps (IDB_TECLA8,IDB_TECLA8,IDB_TECLA8P);
	m_stTecla9.LoadButtonBitmaps (IDB_TECLA9,IDB_TECLA9,IDB_TECLA9P);
	m_stTeclaAst.LoadButtonBitmaps (IDB_TECLAAST,IDB_TECLAAST,IDB_TECLAASTP);
	m_stTeclaAlm.LoadButtonBitmaps (IDB_TECLAALM,IDB_TECLAALM,IDB_TECLAALMP);

	CBitmapDialog::OnInitDialog();
	CMenu* pSysMenu = GetSystemMenu(FALSE);

	m_display.SetText(m_strDisplay); 
	m_display.SetColor( RGB(100,100,100), RGB(0,255,0) );
	m_display.SetBackColor( RGB(80,80,80) );
	m_display.ModifyDigiStyle(0, CDigistring::DS_SMOOTH);

	// Establecer el icono para este cuadro de diálogo. El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional
	
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono. Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CWinCamDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBitmapDialog::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CWinCamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWinCamDlg::OnStnClickedZoommas()
{
	OnKeyDown (VK_HOME,NULL,NULL);
}
void CWinCamDlg::OnStnClickedZoommenos()
{
	OnKeyDown (VK_END,NULL,NULL);
}
void CWinCamDlg::OnStnClickedFocomas()
{
	OnKeyDown (VK_PRIOR,NULL,NULL);
}
void CWinCamDlg::OnStnClickedFocomenos()
{
	OnKeyDown (VK_NEXT,NULL,NULL);
}

void CWinCamDlg::OnStnClickedAbajo()
{
	OnKeyDown (VK_DOWN,NULL,NULL);
}

void CWinCamDlg::OnAbajoLButtonUp (NMHDR* pNMHDR, LRESULT* pResult)
{
	static CString buffer;
	buffer.Format ("S%s00",m_strDisplay);
	m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
	Sleep(50);
	buffer.ReleaseBuffer();
}


void CWinCamDlg::OnStnClickedAbajodrcha()
{
	OnKeyDown (VK_DOWN,NULL,NULL);
	OnKeyDown (VK_RIGHT,NULL,NULL);
}

void CWinCamDlg::OnStnClickedAbajoizda()
{
	OnKeyDown (VK_DOWN,NULL,NULL);
	OnKeyDown (VK_LEFT,NULL,NULL);
}

void CWinCamDlg::OnStnClickedArriba()
{
	OnKeyDown (VK_UP,NULL,NULL);
}

void CWinCamDlg::OnStnClickedArribadrcha()
{
	OnKeyDown (VK_UP,NULL,NULL);
	OnKeyDown (VK_RIGHT,NULL,NULL);
}

void CWinCamDlg::OnStnClickedArribaizda()
{
	OnKeyDown (VK_UP,NULL,NULL);
	OnKeyDown (VK_LEFT,NULL,NULL);
}

void CWinCamDlg::OnStnClickedDerecha()
{
	OnKeyDown (VK_RIGHT,NULL,NULL);
}

void CWinCamDlg::OnStnClickedIzquierda()
{
	OnKeyDown (VK_LEFT,NULL,NULL);
}

LONG CWinCamDlg::OnRxChar(WPARAM ch, LPARAM port)
{
	unsigned char buff[1];

	while (m_serial.Read ((const char *)buff,1))
	{
	}
	return 0;
}

void CWinCamDlg::InsertDisplay (char digit)
{
	char *buffer;
	if (!m_bFlash)
	{
		m_strDisplay = "00";
		SetTimer (100,500,NULL);
	}

	m_bFlash=TRUE;

	buffer = m_strDisplay.GetBuffer();
	buffer[0]=buffer[1];
	buffer[1]=digit;
	m_strDisplay.ReleaseBuffer();
	m_display.SetText(m_strDisplay);
}
void CWinCamDlg::OnStnClickedTecla1()
{
	InsertDisplay ('1');
	OnKeyDown ('1',NULL,NULL);
}

void CWinCamDlg::OnStnClickedTeclaAst()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
}

void CWinCamDlg::OnStnClickedTecla0()
{
	InsertDisplay ('0');
	OnKeyDown ('0',NULL,NULL);
}

void CWinCamDlg::OnStnClickedTeclaAlm()
{
}

void CWinCamDlg::OnStnClickedTecla9()
{
	InsertDisplay ('9');
	OnKeyDown ('9',NULL,NULL);
}

void CWinCamDlg::OnStnClickedTecla8()
{
	InsertDisplay ('8');
	OnKeyDown ('8',NULL,NULL);
}

void CWinCamDlg::OnStnClickedTecla7()
{
	InsertDisplay ('7');
	OnKeyDown ('7',NULL,NULL);
}

void CWinCamDlg::OnStnClickedTecla5()
{
	InsertDisplay ('5');
	OnKeyDown ('5',NULL,NULL);
}

void CWinCamDlg::OnStnClickedTecla6()
{
	InsertDisplay ('6');
	OnKeyDown ('6',NULL,NULL);
}

void CWinCamDlg::OnStnClickedTecla4()
{
	InsertDisplay ('4');
	OnKeyDown ('4',NULL,NULL);
}

void CWinCamDlg::OnStnClickedTecla3()
{
	InsertDisplay ('3');
	OnKeyDown ('3',NULL,NULL);
}	

void CWinCamDlg::OnStnClickedTecla2()
{
	InsertDisplay ('2');
	OnKeyDown ('2',NULL,NULL);
}

BOOL CWinCamDlg::PreTranslateMessage(MSG* pMsg)
{
if (WM_KEYFIRST <= pMsg->message && pMsg->message
                <= WM_KEYLAST)
  if (m_hAccel && ::TranslateAccelerator
     (m_hWnd, m_hAccel, pMsg))
	return TRUE;

if (pMsg->message==WM_KEYDOWN)
	OnKeyDown (pMsg->wParam,NULL,NULL);

if (pMsg->message==WM_KEYUP)
	OnKeyUp (pMsg->wParam,NULL,NULL);
return CBitmapDialog::PreTranslateMessage (pMsg);
}

void CWinCamDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TRACE1 ("%d\n",nChar);
	static CString buffer;
	switch (nChar)
	{
		case VK_HOME:	//Zoom mas
			m_bFlash=FALSE;
			KillTimer (100);
			buffer.Format ("S%s03",m_strDisplay);
			m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
			Sleep(50);
			buffer.ReleaseBuffer();
		break;

		case VK_END:	//Zoom menos
			m_bFlash=FALSE;
			KillTimer (100);
			buffer.Format ("S%s04",m_strDisplay);
			m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
			Sleep(50);
			buffer.ReleaseBuffer();
		break;

		case VK_PRIOR:	//Foco mas
			m_bFlash=FALSE;
			KillTimer (100);
			buffer.Format ("S%s03",m_strDisplay);
			m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
			Sleep(50);
			buffer.ReleaseBuffer();
		break;

		case VK_NEXT:	//Foco menos
			m_bFlash=FALSE;
			KillTimer (100);
			buffer.Format ("S%s04",m_strDisplay);
			m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
			Sleep(50);
			buffer.ReleaseBuffer();
		break;

		case VK_DOWN:
			m_bFlash=FALSE;
			KillTimer (100);
			m_display.SetColor( RGB(100,100,100), RGB(0,255,0) );

//			m_stAbajo.SendMessage (WM_LBUTTONDOWN);
			buffer.Format ("S%s08",m_strDisplay);
			m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
			Sleep(50);
			buffer.ReleaseBuffer();
		break;

		case VK_RIGHT:
			m_bFlash=FALSE;
			KillTimer (100);
			m_display.SetColor( RGB(100,100,100), RGB(0,255,0) );

//			m_stDerecha.SendMessage (WM_LBUTTONDOWN);
			buffer.Format ("S%s05",m_strDisplay);
			m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
			Sleep(50);
			buffer.ReleaseBuffer();
		break;
		
		case VK_LEFT:
			m_bFlash=FALSE;
			KillTimer (100);
			m_display.SetColor( RGB(100,100,100), RGB(0,255,0) );

//			m_stIzquierda.SendMessage (WM_LBUTTONDOWN);
			buffer.Format ("S%s06",m_strDisplay);
			m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
			Sleep(50);
			buffer.ReleaseBuffer();
		break;

		case VK_UP:
			m_bFlash=FALSE;
			KillTimer (100);
			m_display.SetColor( RGB(100,100,100), RGB(0,255,0) );

//			m_stArriba.SendMessage (WM_LBUTTONDOWN);
			buffer.Format ("S%s04",m_strDisplay);
			m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
			Sleep(50);
			buffer.ReleaseBuffer();
		break;

		default:
			if (!m_bFlash)
			{
				m_display.SetColor( RGB(100,100,100), RGB(0,255,0) );
			}
		break;
	}
	CBitmapDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
#include "WINDOWS.H"
void CWinCamDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar==VK_DOWN || nChar==VK_RIGHT || nChar == VK_LEFT || nChar == VK_UP || nChar==36 ||
		nChar==VK_HOME||nChar==VK_END ||nChar==VK_PRIOR ||nChar==VK_NEXT)
	{
		static CString buffer;
		buffer.Format ("S%s00",m_strDisplay);
		m_serial.Write (buffer.GetBuffer(),buffer.GetLength());
		Sleep(50);
		buffer.ReleaseBuffer();
	}

	if (nChar == 36)
		m_stZoomMenos.SendMessage (WM_LBUTTONUP);

	if (nChar == 35)
		m_stZoomMas.SendMessage (WM_LBUTTONUP);

	if (nChar == VK_DOWN)
		m_stAbajo.SendMessage (WM_LBUTTONUP);
    if (nChar == VK_RIGHT)
		m_stDerecha.SendMessage (WM_LBUTTONUP);
    if (nChar == VK_LEFT)
		m_stIzquierda.SendMessage (WM_LBUTTONUP);
    if (nChar == VK_UP)
		m_stArriba.SendMessage (WM_LBUTTONUP);
}

void CWinCamDlg::OnTimer(UINT nIDEvent)
{
	static bool enable=0;

	enable =!enable;
	if (enable)
		m_display.SetColor( RGB(100,100,100), RGB(0,255,0) );
	else
		m_display.SetColor( RGB(100,100,100), RGB(100,100,100) );

	CBitmapDialog::OnTimer(nIDEvent);
}
void CWinCamDlg::OnBnClickedConfig()
{
	CConfigDlg dlg;

	dlg.m_puerto=m_strPuerto;
	if (dlg.DoModal()==IDOK)
	{
		m_strPuerto=dlg.m_puerto;
		m_serial.StopMonitoring();
		m_bConectado=FALSE;
		OnBnClickedConectar();
	}

}

void CWinCamDlg::OnBnClickedConectar()
{
	if (!m_bConectado)
	{
		m_stLed.SetBitmap (LoadBitmap (AfxGetApp()->m_hInstance,MAKEINTRESOURCE (IDB_LEDON)));
		m_serial.InitPort ((COleControl *)this,m_strPuerto,"9600,N,8,1");
		m_serial.StartMonitoring();
		m_bConectado=TRUE;
	}
	else
	{	m_serial.StopMonitoring();
		m_stLed.SetBitmap (LoadBitmap (AfxGetApp()->m_hInstance,MAKEINTRESOURCE (IDB_LEDOFF)));
		m_bConectado=FALSE;
	}

	
}
