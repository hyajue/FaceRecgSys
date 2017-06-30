#if !defined(AFX_TISHI_H__7244FCD7_AED5_4FA8_8245_4BE5532CF888__INCLUDED_)
#define AFX_TISHI_H__7244FCD7_AED5_4FA8_8245_4BE5532CF888__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tishi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Tishi dialog

class Tishi : public CDialog
{
// Construction
public:
	Tishi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Tishi)
	enum { IDD = IDD_DIALOG8 };
	int		m_number;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Tishi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Tishi)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TISHI_H__7244FCD7_AED5_4FA8_8245_4BE5532CF888__INCLUDED_)
