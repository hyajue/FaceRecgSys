// Tishi.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "Tishi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Tishi dialog


Tishi::Tishi(CWnd* pParent /*=NULL*/)
	: CDialog(Tishi::IDD, pParent)
{
	//{{AFX_DATA_INIT(Tishi)
	m_number = 0;
	//}}AFX_DATA_INIT
}


void Tishi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Tishi)
	DDX_Text(pDX, IDC_EDIT1, m_number);
	DDV_MinMaxInt(pDX, m_number, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Tishi, CDialog)
	//{{AFX_MSG_MAP(Tishi)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Tishi message handlers
