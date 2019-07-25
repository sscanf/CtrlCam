// WinCam.cpp : define los comportamientos de las clases para la aplicación.
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


// Construcción de CWinCamApp

CWinCamApp::CWinCamApp()
{
	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}


// El único objeto CWinCamApp

CWinCamApp theApp;


// Inicialización de CWinCamApp

BOOL CWinCamApp::InitInstance()
{
	// Windows XP requiere InitCommonControls() si un manifiesto de 
	// aplicación especifica el uso de ComCtl32.dll versión 6 o posterior para habilitar
	// estilos visuales. De lo contrario, se generará un error al crear ventanas.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CWinCamDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: insertar aquí el código para controlar 
		//  cuándo se descarta el cuadro de diálogo con Aceptar
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: insertar aquí el código para controlar 
		//  cuándo se descarta el cuadro de diálogo con Cancelar
	}

	// Dado que el cuadro de diálogo se ha cerrado, devolver FALSE para salir
	//  de la aplicación en vez de iniciar el suministro de mensajes de dicha aplicación.
	return FALSE;
}
