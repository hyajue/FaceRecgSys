// GetStudyNum.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "GetStudyNum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GetStudyNum dialog


GetStudyNum::GetStudyNum(CWnd* pParent /*=NULL*/)
	: CDialog(GetStudyNum::IDD, pParent) 
{
	//{{AFX_DATA_INIT(GetStudyNum)
	m_Num = 0;
	//}}AFX_DATA_INIT
}


void GetStudyNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GetStudyNum)
	DDX_Text(pDX, IDC_EDIT1, m_Num);
	DDV_MinMaxInt(pDX, m_Num, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GetStudyNum, CDialog)
	//{{AFX_MSG_MAP(GetStudyNum)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GetStudyNum message handlers
