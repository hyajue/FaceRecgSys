// DateName.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "DateName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// DateName dialog


DateName::DateName(CWnd* pParent /*=NULL*/)
	: CDialog(DateName::IDD, pParent)
{
	//{{AFX_DATA_INIT(DateName)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DateName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DateName)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DateName, CDialog)
	//{{AFX_MSG_MAP(DateName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DateName message handlers
