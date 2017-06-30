// MessageName.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "MessageName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MessageName dialog
 

MessageName::MessageName(CWnd* pParent /*=NULL*/)
	: CDialog(MessageName::IDD, pParent)
{
	//{{AFX_DATA_INIT(MessageName)
	m_username = _T("");
	//}}AFX_DATA_INIT
}


void MessageName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MessageName)
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDV_MaxChars(pDX, m_username, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MessageName, CDialog)
	//{{AFX_MSG_MAP(MessageName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MessageName message handlers
