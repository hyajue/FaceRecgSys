// GetName.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "GetName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GetName dialog


GetName::GetName(CWnd* pParent /*=NULL*/) 
	: CDialog(GetName::IDD, pParent)
{
	//{{AFX_DATA_INIT(GetName)
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void GetName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GetName)
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDV_MaxChars(pDX, m_Name, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GetName, CDialog)
	//{{AFX_MSG_MAP(GetName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GetName message handlers
