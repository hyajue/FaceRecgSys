#if !defined(AFX_DELECTMESSAGE_H__3B0A4D80_AAC2_457C_83BC_0769AF18085D__INCLUDED_)
#define AFX_DELECTMESSAGE_H__3B0A4D80_AAC2_457C_83BC_0769AF18085D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DelectMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DelectMessage dialog

class DelectMessage : public CDialog
{
// Construction
public: 
	DelectMessage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DelectMessage)
	enum { IDD = IDD_DIALOG12 };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DelectMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DelectMessage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELECTMESSAGE_H__3B0A4D80_AAC2_457C_83BC_0769AF18085D__INCLUDED_)
