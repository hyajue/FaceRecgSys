// FaceDetect.h : main header file for the FACEDETECT application
//

#if !defined(AFX_FACEDETECT_H__AEF21766_F7CC_4436_8E0C_715129B52791__INCLUDED_)
#define AFX_FACEDETECT_H__AEF21766_F7CC_4436_8E0C_715129B52791__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "VFWImageProcessor.h"
#include "resource.h"       // main symbols
#include "STUDY_1.h"
#include "MessageName.h "
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

///////////////////////////////////////////////////////////////////////////// 
// CFaceDetectApp:
// See FaceDetect.cpp for the implementation of this class
//

class CFaceDetectApp : public CWinApp
{
public:
	CFaceDetectApp();
public:
  CVFWImageProcessor m_VFWImageProc;
	_RecordsetPtr m_pADOSet;
    	
    _ConnectionPtr ADOConn;
	BOOL ADOExecute(_RecordsetPtr &ADOSet, CString strSQL);
	int study();
	int Message();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFaceDetectApp)
	afx_msg void OnAppAbout();
	afx_msg void OnButton32785();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
};

extern CFaceDetectApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDETECT_H__AEF21766_F7CC_4436_8E0C_715129B52791__INCLUDED_)
