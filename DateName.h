#if !defined(AFX_DATENAME_H__0E7D514A_A43C_4112_ADD0_07732EABAC0E__INCLUDED_)
#define AFX_DATENAME_H__0E7D514A_A43C_4112_ADD0_07732EABAC0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DateName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DateName dialog

class DateName : public CDialog 
{
// Construction
public:
	DateName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DateName)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DateName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DateName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATENAME_H__0E7D514A_A43C_4112_ADD0_07732EABAC0E__INCLUDED_)
