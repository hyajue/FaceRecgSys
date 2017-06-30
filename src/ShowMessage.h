#if !defined(AFX_SHOWMESSAGE_H__023B830C_C1AE_43CB_9F17_618A792C2CE6__INCLUDED_)
#define AFX_SHOWMESSAGE_H__023B830C_C1AE_43CB_9F17_618A792C2CE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowMessage.h : header file
//
 
/////////////////////////////////////////////////////////////////////////////
// ShowMessage dialog

class ShowMessage : public CDialog
{
// Construction
public:
	ShowMessage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ShowMessage)
	enum { IDD = IDD_DIALOG9 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ShowMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ShowMessage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWMESSAGE_H__023B830C_C1AE_43CB_9F17_618A792C2CE6__INCLUDED_)
