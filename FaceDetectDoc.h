// FaceDetectDoc.h : interface of the CFaceDetectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEDETECTDOC_H__42B3DFEF_BDE4_4510_B373_046B407B3134__INCLUDED_)
#define AFX_FACEDETECTDOC_H__42B3DFEF_BDE4_4510_B373_046B407B3134__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "LikelyHood.h"
#include <afxtempl.h>
#include <math.h>

class CFaceDetectDoc : public CDocument
{
protected: // create from serialization only

	DECLARE_DYNCREATE(CFaceDetectDoc)
 
// Attributes
public:	
 CFaceDetectDoc();
 void Likehood(int m_WndWidth,int m_WndHeight)  ;
 void OnBtnBinary();
 //void MyDraw();
 void HistogramV() ;
 void OnBtnHistogramH();
 void OnBtnMarkFace();
 bool CopyBitMap(RGBQUAD **dest, RGBQUAD **source);
 void MakeBitMap();
 void DrawCross(CDC *pDC, CPoint point, COLORREF crColor);
 void READYGetFaceOutLline1();
 BOOL OnOpenDocument1(LPCTSTR lpszPathName);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFaceDetectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
public:
   RGBQUAD** m_tOriPixelArray;//ԭʼλͼ����
   RGBQUAD** m_tResPixelArray;//�ο�λͼ����
   RGBQUAD** m_tOriPixelArray1;
   int m_nWndWidth ;
   int m_nWndHeight;
   CLikelyHood	*method1;
   CBitmap* 	m_pResMap;
   	bool m_bFaceOK;//�����Ѿ�ȷ����־λ
	bool m_bShowFace;
	CRect m_rFaceRegion;//��������
	CDC *pDCShow;//������ͼ������
		//������һЩ��־λ
	bool m_bManualMarkFacial;
	bool m_bLeftEyeOK;//����ȷ����־λ
	bool m_bRightEyeOK;//����ȷ����־λ
	bool m_bLeftEyeLeftCornerOK;//�������
	bool m_bLeftEyeRightCornerOK;//�����ҽ�
	bool m_bRightEyeLeftCornerOK;//�������
	bool m_bRightEyeRightCornerOK;//�����ҽ�
	bool m_bLeftNostrilOK;//��ǽ�
	bool m_bRightNostrilOK;//�ұǽ�
	bool m_bLeftMouthCornerOK;//�����
	bool m_bRightMouthCornerOK;//�����
	bool m_bMidMouthOK;//���в�
	bool m_bMidNoseOK;//�Ǽ�
	//����������Щ�������λ��
	CPoint m_LeftEye;
	CPoint m_LeftEyeLeftCorner;
	CPoint m_LeftEyeRightCorner;
	CPoint m_RightEye;
	CPoint m_RightEyeLeftCorner;
	CPoint m_RightEyeRightCorner;
	CPoint m_LeftNostril;
	CPoint m_RightNostril;
	CPoint m_LeftMouthCorner;
	CPoint m_RightMouthCorner;
	CPoint m_MidMouth;
	CPoint m_MidNose;
	int left,right,l,top,bottom;
	LPCTSTR path;
// Generated message map functions
protected:
	//{{AFX_MSG(CFaceDetectDoc)
	afx_msg void OnREADYGetFaceOutLline();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDETECTDOC_H__42B3DFEF_BDE4_4510_B373_046B407B3134__INCLUDED_)
