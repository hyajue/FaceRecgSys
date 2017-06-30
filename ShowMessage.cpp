// ShowMessage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "ShowMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// ShowMessage dialog


ShowMessage::ShowMessage(CWnd* pParent /*=NULL*/)
	: CDialog(ShowMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(ShowMessage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ShowMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShowMessage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShowMessage, CDialog)
	//{{AFX_MSG_MAP(ShowMessage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShowMessage message handlers
