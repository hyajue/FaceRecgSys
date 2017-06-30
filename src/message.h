#if !defined(AFX_MESSAGE_H__03B0E512_F431_453F_9AF5_874E4BD54971__INCLUDED_)
#define AFX_MESSAGE_H__03B0E512_F431_453F_9AF5_874E4BD54971__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// message.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// message dialog

class message : public CDialog
{
// Construction 
public:
	message(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(message)
	enum { IDD = IDD_DIALOG5 };
	CString	m_Name;
	CString	m_Sex;
	int		m_Age;
	CString	m_Tle;
	CString	m_Addresss;
	CString	m_Birthday;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(message)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(message)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGE_H__03B0E512_F431_453F_9AF5_874E4BD54971__INCLUDED_)
