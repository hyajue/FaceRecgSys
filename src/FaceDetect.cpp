// FaceDetect.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FaceDetect.h"

#include "MainFrm.h"
#include "FaceDetectDoc.h"
#include "FaceDetectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// CFaceDetectApp

BEGIN_MESSAGE_MAP(CFaceDetectApp, CWinApp)
	//{{AFX_MSG_MAP(CFaceDetectApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
//	ON_COMMAND(ID_BUTTON32785, OnButton32785)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectApp construction

CFaceDetectApp::CFaceDetectApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFaceDetectApp object

CFaceDetectApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectApp initialization

BOOL CFaceDetectApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

//数据库连接
	if(FAILED(::CoInitialize(NULL)))
	{
		AfxMessageBox("ADO Init failed");
		return false;
	}
	try
	{
		//SQL Server 2000 的DSN连接 要设置DSN为mydata
//		ADOConn.CreateInstance(__uuidof(Connection));
//		ADOConn->Open("DSN=STKDATA;Provider=MSDASQL","","",adConnectUnspecified);
		//Access 2000 的连接，不需要配置DSN
		ADOConn.CreateInstance("ADODB.Connection");///创建Connection对象
		ADOConn->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=CParameter.mdb;Persist Security Info=False","","",adModeUnknown);///连接数据库
        //ADOConn->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Message.mdb;Persist Security Info=False","","",adModeUnknown);///连接数据库
	}
	catch(_com_error &e)
	{
		CString err;
		err.Format("%s",(char *)(e.Description()));
		AfxMessageBox(err);
	}
	catch(...)
	{
		AfxMessageBox("Unknown Eoor...");
	}
	m_pADOSet.CreateInstance(__uuidof(Recordset));
//数据库连接结束
	
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CFaceDetectDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CFaceDetectView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

/*
   Menu = GetMenu();

   if (!Caps.fHasDlgVideoSource)
      Menu->EnableMenuItem(ID_SETTINGS_VIDEOSOURCE,MF_GRAYED);

   if (!Caps.fHasDlgVideoFormat)
      Menu->EnableMenuItem(ID_SETTINGS_VIDEOFORMAT,MF_GRAYED);

   if (!Caps.fHasDlgVideoDisplay)
      Menu->EnableMenuItem(ID_SETTINGS_VIDEODISPLAY,MF_GRAYED);
*/
   
///////////////////////////////////////////////////////////////////////////////
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CFaceDetectApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectApp message handlers

BOOL CFaceDetectApp::ADOExecute(_RecordsetPtr &ADOSet, CString strSQL)
{
	if(ADOSet->State==adStateOpen)	
		ADOSet->Close();
	try
	{
		if(ADOConn==NULL)
			ADOConn.CreateInstance (__uuidof(Connection));//创建连接实例
		variant_t vNULL;//变量体
		vNULL.vt=VT_ERROR;
		vNULL.scode=DISP_E_PARAMNOTFOUND;//
		ADOSet->PutRefActiveConnection (this->ADOConn );//创建与数据库对应的数据集
		ADOSet->Open((variant_t)strSQL, vNULL, adOpenStatic, adLockUnspecified, adCmdText);
		return true;
	}
	catch(_com_error &e)//获取系统错误
	{
		CString err;
		err.Format("ADO Error: %s",(char *)e.Description());
		AfxMessageBox(err);
		return false;
	}
}

void CFaceDetectApp::OnButton32785() 
{
	// TODO: Add your command handler code here
    //
}

int CFaceDetectApp::study()
{
   STUDY_1 dlg;
   int nResponse=dlg.DoModal();
   //if(nResponse==IDOK)
	   return 1;
 // else 
	 // return 0;
}

int CFaceDetectApp::Message()
{
	MessageName dlgname;
    int GetName=dlgname.DoModal();
	//if(GetName==IDOK)
		return 1;
//	else 
//		return 0;
}