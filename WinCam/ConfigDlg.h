#pragma once

#include "bitmapdialog.h"
// Cuadro de di�logo de CConfigDlg

class CConfigDlg : public CBitmapDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~CConfigDlg();

// Datos del cuadro de di�logo
	enum { IDD = IDD_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_puerto;
};
