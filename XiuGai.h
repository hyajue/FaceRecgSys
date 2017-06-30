#if !defined(AFX_XIUGAI_H__D7323894_C1F9_4BBE_9ADF_9B2CB70F1DCB__INCLUDED_)
#define AFX_XIUGAI_H__D7323894_C1F9_4BBE_9ADF_9B2CB70F1DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XiuGai.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// XiuGai dialog

class XiuGai : public CDialog
{
// Construction
public:
	XiuGai(CWnd* pParent = NULL);   // standard constructor
    int flagN;
	int flagB;
	int flagA;
	int flagT;
	int flagAD;

// Dialog Data
	//{{AFX_DATA(XiuGai)
	enum { IDD = IDD_DIALOG14 };
	CString	m_Name;
	int		m_Age;
	CString	m_Birthday;
	CString	m_Tel;
	CString	m_Add;
	CString	m_Xname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(XiuGai)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(XiuGai)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck4();
	afx_msg void OnCheck3();
	afx_msg void OnCheck5();
	afx_msg void OnDATABASEModification();
	afx_msg void OnMenuitem32799();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XIUGAI_H__D7323894_C1F9_4BBE_9ADF_9B2CB70F1DCB__INCLUDED_)
