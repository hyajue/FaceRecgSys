#if !defined(AFX_SHUJUYANCHI_H__3073A348_4EE7_4DAC_9AA9_86B17598C939__INCLUDED_)
#define AFX_SHUJUYANCHI_H__3073A348_4EE7_4DAC_9AA9_86B17598C939__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// shujuyanchi.h : header file
//
 
/////////////////////////////////////////////////////////////////////////////
// shujuyanchi dialog

class shujuyanchi : public CDialog
{
// Construction
public:
	shujuyanchi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(shujuyanchi)
	enum { IDD = IDD_DIALOG15 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(shujuyanchi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(shujuyanchi)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUJUYANCHI_H__3073A348_4EE7_4DAC_9AA9_86B17598C939__INCLUDED_)
