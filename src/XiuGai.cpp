// XiuGai.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "XiuGai.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// XiuGai dialog


XiuGai::XiuGai(CWnd* pParent /*=NULL*/)
	: CDialog(XiuGai::IDD, pParent)
{
	//{{AFX_DATA_INIT(XiuGai)
	m_Name = _T("");
	m_Age = 0;
	m_Birthday = _T("");
	m_Tel = _T("");
	m_Add = _T("");
	m_Xname = _T("");
	//}}AFX_DATA_INIT
	 flagN=0;
	 flagB=0;
	 flagA=0;
	 flagT=0;
     flagAD=0;
}


void XiuGai::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(XiuGai)
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDV_MaxChars(pDX, m_Name, 15);
	DDX_Text(pDX, IDC_EDIT2, m_Age);
	DDV_MinMaxInt(pDX, m_Age, 0, 200);
	DDX_Text(pDX, IDC_EDIT3, m_Birthday);
	DDX_Text(pDX, IDC_EDIT4, m_Tel);
	DDX_Text(pDX, IDC_EDIT5, m_Add);
	DDV_MaxChars(pDX, m_Add, 200);
	DDX_Text(pDX, IDC_EDIT6, m_Xname);
	DDV_MaxChars(pDX, m_Xname, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(XiuGai, CDialog)
	//{{AFX_MSG_MAP(XiuGai)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_COMMAND(ID_DATABASE_Modification, OnDATABASEModification)
	ON_COMMAND(ID_MENUITEM32799, OnMenuitem32799)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XiuGai message handlers

void XiuGai::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	flagN=1;
	
}

void XiuGai::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	flagA=1;
}

void XiuGai::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	flagT=1;
}

void XiuGai::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	flagB=1;
	
}

void XiuGai::OnCheck5() 
{
	// TODO: Add your control notification handler code here
	flagAD=1;
}

void XiuGai::OnDATABASEModification() 
{
	// TODO: Add your command handler code here
	
	

}

void XiuGai::OnMenuitem32799() 
{
	// TODO: Add your command handler code here
	
}
