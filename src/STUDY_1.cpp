// STUDY_1.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "STUDY_1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// STUDY_1 dialog


STUDY_1::STUDY_1(CWnd* pParent /*=NULL*/)
	: CDialog(STUDY_1::IDD, pParent)
{
	//{{AFX_DATA_INIT(STUDY_1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void STUDY_1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(STUDY_1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(STUDY_1, CDialog)
	//{{AFX_MSG_MAP(STUDY_1)
	ON_BN_CLICKED(ID_DETECT_CONTINUE, OnDetectContinue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// STUDY_1 message handlers

void STUDY_1::OnDetectContinue() 
{
	 
	// TODO: Add your control notification handler code here
	
}
