// Study.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "Study.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Study dialog 


Study::Study(CWnd* pParent /*=NULL*/)
	: CDialog(Study::IDD, pParent)
{
	//{{AFX_DATA_INIT(Study)
	m_Num = 0;
	//}}AFX_DATA_INIT
}


void Study::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Study)
	DDX_Text(pDX, IDC_EDIT1, m_Num);
	DDV_MinMaxInt(pDX, m_Num, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Study, CDialog)
	//{{AFX_MSG_MAP(Study)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Study message handlers
