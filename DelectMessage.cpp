// DelectMessage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "DelectMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DelectMessage dialog


DelectMessage::DelectMessage(CWnd* pParent /*=NULL*/) 
	: CDialog(DelectMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(DelectMessage)
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void DelectMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DelectMessage)
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDV_MaxChars(pDX, m_Name, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DelectMessage, CDialog)
	//{{AFX_MSG_MAP(DelectMessage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DelectMessage message handlers
