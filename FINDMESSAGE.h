#if !defined(AFX_FINDMESSAGE_H__727B1461_783B_4DD5_A789_EA3D70115EBD__INCLUDED_)
#define AFX_FINDMESSAGE_H__727B1461_783B_4DD5_A789_EA3D70115EBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FINDMESSAGE.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FINDMESSAGE dialog

class FINDMESSAGE : public CDialog
{
// Construction
public:
	FINDMESSAGE(CWnd* pParent = NULL);   // standard constructor

// Dialog Data 
	//{{AFX_DATA(FINDMESSAGE)
	enum { IDD = IDD_DIALOG10 };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FINDMESSAGE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FINDMESSAGE)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDMESSAGE_H__727B1461_783B_4DD5_A789_EA3D70115EBD__INCLUDED_)
