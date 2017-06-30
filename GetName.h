#if !defined(AFX_GETNAME_H__20AD8627_E86C_440E_BAE3_60DD94AD3FB6__INCLUDED_)
#define AFX_GETNAME_H__20AD8627_E86C_440E_BAE3_60DD94AD3FB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GetName dialog

class GetName : public CDialog
{
// Construction
public:
	GetName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data 
	//{{AFX_DATA(GetName)
	enum { IDD = IDD_DIALOG2 };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GetName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GetName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETNAME_H__20AD8627_E86C_440E_BAE3_60DD94AD3FB6__INCLUDED_)
