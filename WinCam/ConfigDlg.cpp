// ConfigDlg.cpp: archivo de implementaci�n
//

#include "stdafx.h"
#include "WinCam.h"
#include "ConfigDlg.h"


// Cuadro de di�logo de CConfigDlg

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)
CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CConfigDlg::IDD, pParent)
	, m_puerto(_T(""))
{
}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_PORT, m_puerto);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CBitmapDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de CConfigDlg

BOOL CConfigDlg::OnInitDialog()
{
	SetBitmap (IDB_CONFIG);
	CBitmapDialog::OnInitDialog();

	// TODO:  Agregue aqu� la inicializaci�n adicional

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPCI�N: las p�ginas de propiedades OCX deben devolver FALSE
}
