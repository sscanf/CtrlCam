// WinCam.cpp : define los comportamientos de las clases para la aplicaci�n.
//

#include "stdafx.h"
#include "WinCam.h"
#include "WinCamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinCamApp

BEGIN_MESSAGE_MAP(CWinCamApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Construcci�n de CWinCamApp

CWinCamApp::CWinCamApp()
{
	// TODO: agregar aqu� el c�digo de construcci�n,
	// Colocar toda la inicializaci�n importante en InitInstance
}


// El �nico objeto CWinCamApp

CWinCamApp theApp;


// Inicializaci�n de CWinCamApp

BOOL CWinCamApp::InitInstance()
{
	// Windows XP requiere InitCommonControls() si un manifiesto de 
	// aplicaci�n especifica el uso de ComCtl32.dll versi�n 6 o posterior para habilitar
	// estilos visuales. De lo contrario, se generar� un error al crear ventanas.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CWinCamDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: insertar aqu� el c�digo para controlar 
		//  cu�ndo se descarta el cuadro de di�logo con Aceptar
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: insertar aqu� el c�digo para controlar 
		//  cu�ndo se descarta el cuadro de di�logo con Cancelar
	}

	// Dado que el cuadro de di�logo se ha cerrado, devolver FALSE para salir
	//  de la aplicaci�n en vez de iniciar el suministro de mensajes de dicha aplicaci�n.
	return FALSE;
}
