#if !defined(AFX_GETSTUDYNUM_H__8047C35C_2085_4B7C_A1B7_C5FE034795FB__INCLUDED_)
#define AFX_GETSTUDYNUM_H__8047C35C_2085_4B7C_A1B7_C5FE034795FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetStudyNum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GetStudyNum dialog

class GetStudyNum : public CDialog
{
// Construction
public:
	GetStudyNum(CWnd* pParent = NULL);   // standard constructor
 
// Dialog Data
	//{{AFX_DATA(GetStudyNum)
	enum { IDD = IDD_DIALOG7 };
	int		m_Num;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GetStudyNum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GetStudyNum)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETSTUDYNUM_H__8047C35C_2085_4B7C_A1B7_C5FE034795FB__INCLUDED_)
