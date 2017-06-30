#if !defined(AFX_SHOWPMESSAGE_H__9972894D_11D5_4ECD_BAD1_553B8876610D__INCLUDED_)
#define AFX_SHOWPMESSAGE_H__9972894D_11D5_4ECD_BAD1_553B8876610D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowPMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ShowPMessage dialog

class ShowPMessage : public CDialog
{
// Construction 
public:
	ShowPMessage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ShowPMessage)
	enum { IDD = IDD_DIALOG9 };
	CString	m_Name;
	CString	m_Sex;
	CString	m_Birthday;
	CString	m_Teleph;
	CString	m_Address;
	CString	m_Age;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ShowPMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ShowPMessage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWPMESSAGE_H__9972894D_11D5_4ECD_BAD1_553B8876610D__INCLUDED_)
