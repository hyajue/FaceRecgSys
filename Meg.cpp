// Meg.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "Meg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Meg dialog


Meg::Meg(CWnd* pParent /*=NULL*/) 
	: CDialog(Meg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Meg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Meg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Meg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Meg, CDialog)
	//{{AFX_MSG_MAP(Meg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Meg message handlers
