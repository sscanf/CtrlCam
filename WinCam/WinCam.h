// WinCam.h: archivo de encabezado principal para la aplicaci�n PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// S�mbolos principales


// CWinCamApp:
// Consulte la secci�n WinCam.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CWinCamApp : public CWinApp
{
public:
	CWinCamApp();

// Reemplazos
	public:
	virtual BOOL InitInstance();

// Implementaci�n

	DECLARE_MESSAGE_MAP()
};

extern CWinCamApp theApp;
