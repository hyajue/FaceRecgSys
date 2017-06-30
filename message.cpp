// message.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// message dialog


message::message(CWnd* pParent /*=NULL*/) 
	: CDialog(message::IDD, pParent)
{
	//{{AFX_DATA_INIT(message)
	m_Name = _T("");
	m_Sex = _T("");
	m_Age = 0;
	m_Tle = _T("");
	m_Addresss = _T("");
	m_Birthday = _T("");
	//}}AFX_DATA_INIT
}


void message::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(message)
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDV_MaxChars(pDX, m_Name, 15);
	DDX_Text(pDX, IDC_EDIT2, m_Sex);
	DDV_MaxChars(pDX, m_Sex, 2);
	DDX_Text(pDX, IDC_EDIT3, m_Age);
	DDV_MinMaxInt(pDX, m_Age, 0, 200);
	DDX_Text(pDX, IDC_EDIT5, m_Tle);
	DDV_MaxChars(pDX, m_Tle, 10);
	DDX_Text(pDX, IDC_EDIT6, m_Addresss);
	DDV_MaxChars(pDX, m_Addresss, 100);
	DDX_Text(pDX, IDC_EDIT4, m_Birthday);
	DDV_MaxChars(pDX, m_Birthday, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(message, CDialog)
	//{{AFX_MSG_MAP(message)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// message message handlers
