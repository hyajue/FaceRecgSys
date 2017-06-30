// ShowPMessage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "ShowPMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ShowPMessage dialog
 

ShowPMessage::ShowPMessage(CWnd* pParent /*=NULL*/)
	: CDialog(ShowPMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(ShowPMessage)
	m_Name = _T("");
	m_Sex = _T("");
	m_Birthday = _T("");
	m_Teleph = _T("");
	m_Address = _T("");
	m_Age = _T("");
	//}}AFX_DATA_INIT
}


void ShowPMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShowPMessage)
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT3, m_Sex);
	DDX_Text(pDX, IDC_EDIT4, m_Birthday);
	DDX_Text(pDX, IDC_EDIT5, m_Teleph);
	DDX_Text(pDX, IDC_EDIT6, m_Address);
	DDX_Text(pDX, IDC_EDIT2, m_Age);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShowPMessage, CDialog)
	//{{AFX_MSG_MAP(ShowPMessage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShowPMessage message handlers
