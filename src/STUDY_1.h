#if !defined(AFX_STUDY_1_H__BC1ACE77_2B84_442E_A8F8_719E6BCD9980__INCLUDED_)
#define AFX_STUDY_1_H__BC1ACE77_2B84_442E_A8F8_719E6BCD9980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// STUDY_1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// STUDY_1 dialog

class STUDY_1 : public CDialog
{
// Construction
public:
	STUDY_1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(STUDY_1)
	enum { IDD = IDD_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(STUDY_1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(STUDY_1)
	afx_msg void OnDetectContinue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STUDY_1_H__BC1ACE77_2B84_442E_A8F8_719E6BCD9980__INCLUDED_)
