#if !defined(AFX_MESSAGENAME_H__B1922213_5EFF_49F0_AA5A_6F2B86D1E5BB__INCLUDED_)
#define AFX_MESSAGENAME_H__B1922213_5EFF_49F0_AA5A_6F2B86D1E5BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MessageName dialog

class MessageName : public CDialog
{
// Construction
public:
	MessageName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data 
	//{{AFX_DATA(MessageName)
	enum { IDD = IDD_DIALOG1 };
	CString	m_username;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MessageName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MessageName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGENAME_H__B1922213_5EFF_49F0_AA5A_6F2B86D1E5BB__INCLUDED_)
