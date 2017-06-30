#if !defined(AFX_DLGZHIFANG_H__65C38E0D_EE25_409A_AA74_727D9273B3F4__INCLUDED_)
#define AFX_DLGZHIFANG_H__65C38E0D_EE25_409A_AA74_727D9273B3F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgZhiFang.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgZhiFang dialog

class DlgZhiFang : public CDialog
{
// Construction
public:
	float m_fIntensity[256];
	DlgZhiFang(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgZhiFang)
	enum { IDD = IDD_DIALOG16 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgZhiFang)
	protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgZhiFang)
	afx_msg void OnPaint();
	afx_msg void OnCoord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGZHIFANG_H__65C38E0D_EE25_409A_AA74_727D9273B3F4__INCLUDED_)
