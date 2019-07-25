// WinCam.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Símbolos principales


// CWinCamApp:
// Consulte la sección WinCam.cpp para obtener información sobre la implementación de esta clase
//

class CWinCamApp : public CWinApp
{
public:
	CWinCamApp();

// Reemplazos
	public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern CWinCamApp theApp;
