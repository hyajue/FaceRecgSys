// FINDMESSAGE.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "FINDMESSAGE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FINDMESSAGE dialog


FINDMESSAGE::FINDMESSAGE(CWnd* pParent /*=NULL*/)
	: CDialog(FINDMESSAGE::IDD, pParent) 
{
	//{{AFX_DATA_INIT(FINDMESSAGE)
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void FINDMESSAGE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FINDMESSAGE)
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDV_MaxChars(pDX, m_Name, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FINDMESSAGE, CDialog)
	//{{AFX_MSG_MAP(FINDMESSAGE)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FINDMESSAGE message handlers
