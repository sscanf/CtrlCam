// WinCamDlg.h: archivo de encabezado
//
#include "BitmapDialog.h"
#include "BmpButton.h"
#include "afxwin.h"
#include "SerialPort.h"
#include "digistring.h"
#include "hoverbutton.h"
#pragma once


// Cuadro de diálogo de CWinCamDlg
class CWinCamDlg : public CBitmapDialog
{
// Construcción
public:
	CWinCamDlg(CWnd* pParent = NULL);	// Constructor estándar

// Datos del cuadro de diálogo
	enum { IDD = IDD_WINCAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;
	HACCEL m_hAccel;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	LONG OnRxChar(WPARAM ch, LPARAM port);
	void InsertDisplay (char digit);

	CSerialPort	m_serial;
public:
	CBmpButton m_stArriba;
	CBmpButton m_stArribaDrcha;
	CBmpButton m_stDerecha;
	CBmpButton m_stAbajoDrcha;
	CBmpButton m_stAbajo;
	CBmpButton m_stAbajoIzda;
	CBmpButton m_stIzquierda;
	CBmpButton m_stArribaIzda;

	CBmpButton m_stTecla1;
	CBmpButton m_stTecla2;
	CBmpButton m_stTecla3;
	CBmpButton m_stTecla4;
	CBmpButton m_stTecla5;
	CBmpButton m_stTecla6;
	CBmpButton m_stTecla7;
	CBmpButton m_stTecla8;
	CBmpButton m_stTecla9;
	CBmpButton m_stTeclaAst;
	CBmpButton m_stTecla0;
	CBmpButton m_stTeclaAlm;

	CBmpButton m_stFocoMas;
	CBmpButton m_stFocoMenos;
	CBmpButton m_stZoomMas;
	CBmpButton m_stZoomMenos;

	CHoverButton m_config;
	CHoverButton m_conectar;


	afx_msg void OnStnClickedAbajodrcha();
	afx_msg void OnStnClickedAbajoizda();
	afx_msg void OnStnClickedArriba();
	void CWinCamDlg::OnStnClickedAbajo();
	afx_msg void OnStnClickedArribadrcha();
	afx_msg void OnStnClickedArribaizda();
	afx_msg void OnStnClickedDerecha();
	afx_msg void OnStnClickedIzquierda();
protected:
	CDigistring m_display;
	CString m_strDisplay;
public:
	afx_msg void OnStnClickedTecla1();
	afx_msg void OnStnClickedTeclaAst();
	afx_msg void OnStnClickedTecla0();
	afx_msg void OnStnClickedTeclaAlm();
	afx_msg void OnStnClickedTecla9();
	afx_msg void OnStnClickedTecla8();
	afx_msg void OnStnClickedTecla7();
	afx_msg void OnStnClickedTecla5();
	afx_msg void OnStnClickedTecla6();
	afx_msg void OnStnClickedTecla4();
	afx_msg void OnStnClickedTecla3();
	afx_msg void OnStnClickedTecla2();
	afx_msg void OnAbajoLButtonUp(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnArriba();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	bool m_bFlash;
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStnClickedZoommas();
	afx_msg void OnStnClickedZoommenos();
	afx_msg void OnStnClickedFocomas();
	afx_msg void OnStnClickedFocomenos();
	afx_msg void OnBnClickedConectar();
	afx_msg void OnBnClickedConfig();
	CStatic m_stLed;
	bool m_bConectado;
	CString m_strPuerto;
};
