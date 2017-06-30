// FaceDetectView.h : interface of the CFaceDetectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEDETECTVIEW_H__68937D34_4512_4AD0_A47E_713CFBCE99CD__INCLUDED_)
#define AFX_FACEDETECTVIEW_H__68937D34_4512_4AD0_A47E_713CFBCE99CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DIB.h"

#include "VFWImageProcessor.h"
class CFaceDetectView : public CView
{
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CFaceDetectView)

// Attributes
public:
	CFaceDetectDoc* GetDocument();

    CFaceDetectView();
	void DrawLine(int left,int top,int buttom ,int right);
	int  IncreaseContrast(int pByte,int n);
	void MidFilter(int tem_w,int tem_h);
	bool FixeEyes();
	void FixeNose();
	void FixeMouth();
	void GetPartParameter();
	void GetEyesParameter();
	void GetNoseParameter() ;
	void GetmouthParameter() ;
	HBITMAP ConvTo24Bit( HBITMAP h32 );
	void Centerofgravity();
	double GetM(int n,int m);
	double Getm(int n,int m);
	double Getmreye(int n,int m);
	double Getmleye(int n,int m);
	double AverageDeviation(double NewData,double OldData);
	void DrawCrossX(int X,int Y);
	void Template(double * tem ,int tem_w,int tem_h,double xishu);
	int TopPoint(int m_top,int m_bottom,int m_left,int m_right);
	int NoseX(int N_left,int N_right,int N_top,int N_bottom);
	int NoseY(int N_left,int N_right,int N_top,int N_bottom);
	int NoseRX(int N_left,int N_right,int N_top,int N_bottom);
	void EyeLineL(int m_top,int m_bottom,int m_left,int m_right);
	void GetNewParameter();
	int copyfile(const char* source, const char* dest);
	int copyfile1(const char* source, const char* dest);
	double TwoPointDistance(int x1,int y1,int x2,int y2);
	void ADDFace(CString name);
	void ReadyLightingconpensate2();
	void ReadyScale3();
	void READYTemplate4();
	void Mypic() ;
	void ReadyZft5();
	void READYContrastEnhance6();
	void ReadyWhiteblack7();
	bool READYFixedPosition8();
	void IdProssing();
// Operations
public:
    CRect faceLocation[10];
	int faceNum;
	bool flag[ImgRange][ImgRange];
	LPBYTE lpYcc;
	LPBYTE lpRB;
	LPBYTE lpYccTemp;
	LPBYTE lpRgb;
	bool   emymapl[ImgRange][ImgRange];
	bool   emymapc[ImgRange][ImgRange];
	bool   lab[ImgRange][ImgRange];
	CPoint mouthLocation;
	CPoint eye1;
	CPoint eye2;
	bool   result;
	CDC* pDCG;
	int **Gray ;

	int GetFlag;
	int **Icd;
	int **ZFT;
	int **WhiteBlack;
	int *Vtemp;
	int *Htemp;
	int R_beye;
	int L_teye;
	int L_beye;
	int B_NoseMiddleLine;
	int Cofg_lefteyex;
	int Cofg_lefteyey;
	int Cofg_righteyex;
	int Cofg_righteyey;
	int Cofg_nosex;
	int Cofg_nosey;
	int Cofg_mouthx;
	int Cofg_mouthy;
	int H_lleye;
    int H_lreye;
	int R_teye;
	int H_lMouth;
    int H_rMouth;
	int H_lnose;
    int H_rnose;
	int H_rleye;
    int H_rreye;
	int T_NoseMiddleLine;
	int T_MouthMiddleLine;
    int B_MouthMiddleLine;
    double Zx;
    double Zy;
	double M1,M2,M3,M4,M5,M6,M7;
	double M10;
    double M00;
    double M01;
    double Eleye;
    double Ereye;
	CLikelyHood	*method1;
    bool flagP;
	bool Close;
	CStatic m_VideoDisplay;
	CVFWImageProcessor m_VFWImageProc;
	int  **HeightTemplate;
	int N_MiddleX;
	int R_noseX;
	int L_noseX;
	int N_MiddleY;
	double x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11;
	int R_EyeLY;
	int R_EyeLX;
	int R_EyeRY;
	int R_EyeRX;
	int xiabaX;
	int xiabaY;
    int M_RX;
    int M_RY;
    int M_LX;
    int M_LY;
    int L_EyeRY;
    int L_EyeRX;
	int L_EyeLX;
	int L_EyeLY;
	int L_noseY;
	int R_noseY;
	int Study;
	int Picture;
	int Picture1;
	CString pname;
	bool FaceAere,FaceLine,FaceGray,FaceGass,FaceJunHeng,FaceDbidu,FaceTwo,FaceGuLi,FaceDingWei,FaceTeZheng,FaceShiBie,FaceFix,FacePara;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFaceDetectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFaceDetectView)
	afx_msg void OnReadyLightingconpensate();
	afx_msg void OnReadyScale();
	afx_msg void OnREADYContrastEnhance();
	afx_msg void OnReadyZft();
	afx_msg void OnReadyWhiteblack();
	afx_msg void OnREADYBanishOnlyPoint();
	afx_msg void OnREADYMediumvalue();
	afx_msg void OnREADYDilationFirst();
	afx_msg void OnREADYDecay();
	afx_msg void OnREADYOutLine();
	afx_msg void OnREADYFixedPosition();
	afx_msg void OnPROCESSINGGetCharacteristicParameter();
	afx_msg void OnPROSSINGdetect();
	afx_msg void OnIdVidio();
	afx_msg void OnVidioCannel();
	afx_msg void OnIdProssing();
	afx_msg void OnREADYTemplate();
	afx_msg void OnGetName();
	afx_msg void OnProssingStudy();
	afx_msg void OnDetectface();
	afx_msg void OnStudyMenuitem32798();
	afx_msg void OnDatabaseFind();
	afx_msg void OnDATABASEDelete();
	afx_msg void OnMenuitem32799();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FaceDetectView.cpp
inline CFaceDetectDoc* CFaceDetectView::GetDocument()
   { return (CFaceDetectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDETECTVIEW_H__68937D34_4512_4AD0_A47E_713CFBCE99CD__INCLUDED_)
