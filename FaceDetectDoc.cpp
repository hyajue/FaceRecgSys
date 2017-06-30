// FaceDetectDoc.cpp : implementation of the CFaceDetectDoc class
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "DIB.h"
#include "FaceDetectDoc.h"
#include "FaceDetectView.h"
#include "LikelyHood.h"
#include "math.h"
#define WIDTHBYTES(bits)  ((bits+31)/32*4)
//#include "ReplaceDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern HANDLE hDIB;
extern HANDLE hDIB1;
extern HANDLE hDIBTemp;
extern HANDLE hDIBTemp1;
extern class DIB gDib;
extern int gheight;
extern int gwidth;
extern WORD gwBytesPerLine;
#define IDC_BMPSHOW                     1000

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectDoc

IMPLEMENT_DYNCREATE(CFaceDetectDoc, CDocument)

BEGIN_MESSAGE_MAP(CFaceDetectDoc, CDocument)
	//{{AFX_MSG_MAP(CFaceDetectDoc)
	ON_COMMAND(ID_READY_GetFaceOutLline, OnREADYGetFaceOutLline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectDoc construction/destruction

CFaceDetectDoc::CFaceDetectDoc()
{
	// TODO: add one-time construction code here
	 m_bFaceOK = false;
	


}

CFaceDetectDoc::~CFaceDetectDoc()
{
}

BOOL CFaceDetectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFaceDetectDoc serialization

void CFaceDetectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectDoc diagnostics

#ifdef _DEBUG
void CFaceDetectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFaceDetectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectDoc commands
BOOL CFaceDetectDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	if(hDIB)
		GlobalFree(hDIB);
	   path=lpszPathName;
	hDIB = gDib.LoadDIB(lpszPathName);
	ASSERT(hDIB != NULL);

	hDIBTemp = gDib.CopyHandle(hDIB);
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	gheight = lpbi->biHeight;
	gwidth = lpbi->biWidth;
    m_nWndWidth = gwidth;
	m_nWndHeight=gheight ;
	gwBytesPerLine = gDib.BytePerLine(hDIB);
	GlobalUnlock(hDIB);

	return TRUE;
}

BOOL CFaceDetectDoc::OnOpenDocument1(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	if(hDIB1)
		GlobalFree(hDIB1);
	   path=lpszPathName;
	hDIB1 = gDib.LoadDIB(lpszPathName);
	ASSERT(hDIB1 != NULL);
	hDIBTemp1 = gDib.CopyHandle(hDIB1);
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB1);
	gheight = lpbi->biHeight;
	gwidth = lpbi->biWidth;
    m_nWndWidth = gwidth;
	m_nWndHeight=gheight ;
	gwBytesPerLine = gDib.BytePerLine(hDIB1);
	GlobalUnlock(hDIB);

	return TRUE;
}
///////////////////////Get Face Outline//////////////////
void CFaceDetectDoc::OnREADYGetFaceOutLline() 
{
//	BYTE	*colorTable;
	if(!hDIB)
	{
		::AfxMessageBox("Please make sure there is picture in the region!");return ;
	}
	READYGetFaceOutLline1() ;

}

void CFaceDetectDoc::READYGetFaceOutLline1()  
{
	DIB *m_pMainDib=new DIB();

   //BYTE *m_pDib=m_pMainDib->GetBits();
	
//	colorTable = (BYTE *)m_pDib;

   //////////////////////////////////////////////////////
    HDIB hNewDIB = NULL;
	LPBITMAPINFOHEADER lpSrc,lpDest;
	LPBYTE lpS,lpD;
	DWORD dwBytesPerLine;
	DWORD dwImgSize;
//	WORD wBytesPerLine;
	unsigned i ,j,height,width;
	if(!hDIB)
		return ;
	
	lpSrc = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

	dwBytesPerLine = WIDTHBYTES(24*(lpSrc->biWidth));
	dwImgSize = lpSrc->biHeight * dwBytesPerLine;
	//apply for memory
	hNewDIB = GlobalAlloc(GHND,sizeof(BITMAPINFOHEADER)+dwImgSize);

	lpDest = (LPBITMAPINFOHEADER)GlobalLock(hNewDIB);
	
	
   	memcpy((void*)lpDest,(void*)lpSrc,sizeof(BITMAPINFOHEADER));
	
	DWORD dwSBytesPerLine;
	
	dwSBytesPerLine = (24*(lpSrc->biWidth)+31)/32*4;

	height = lpDest->biHeight;
	width = lpDest->biWidth;
	lpS = (LPBYTE)lpSrc;
//	wBytesPerLine = this->BytePerLine(hDIB);//
	lpD = (LPBYTE)lpDest;	
	lpS = lpS + sizeof(BITMAPINFOHEADER);
	lpD = lpD + sizeof(BITMAPINFOHEADER);
	
   ////////////////////////////////////////////////////
  
	int byteBitCount  = m_pMainDib->GetBiBitCount()/8;

	m_tOriPixelArray  = new RGBQUAD*[height];
	m_tResPixelArray  = new RGBQUAD*[height];

for(i=0; i<height; i++)
	{
		m_tOriPixelArray[i] = new RGBQUAD[width];
		m_tResPixelArray[i] = new RGBQUAD[width];
	
	}

    LPBYTE lpData;
	long lOffset;
	lpData = gDib.FindDIBBits(hDIB);
    WORD gwBytesPerLine = gDib.BytePerLine(hDIB);

	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)

		{  
			lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);

            m_tOriPixelArray[i][j].rgbBlue =*(lpData + lOffset++);
		    m_tOriPixelArray[i][j].rgbGreen=*(lpData + lOffset++);
			m_tOriPixelArray[i][j].rgbRed  =*(lpData + lOffset++);
			
			m_tOriPixelArray[i][j].rgbReserved = 0;

			m_tResPixelArray[i][j]=m_tOriPixelArray[i][j];
		
	
		}
	
	}
	m_nWndWidth=width;
    m_nWndHeight=height;

  method1 =new CLikelyHood(m_tOriPixelArray,m_nWndWidth,m_nWndHeight);
  
  Likehood(m_nWndWidth,m_nWndHeight) ;
  OnBtnBinary();
  
  HistogramV();
  OnBtnHistogramH();
  
  OnBtnMarkFace();

  
}

////////////////////////////////////////////////////////////////////////////////
// Calculate Likelyhood
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDoc::Likehood(int m_WndWidth,int m_WndHeight) 
{
	int i,j;

	SetCursor(LoadCursor(NULL,IDC_WAIT));
    
	method1->CalLikeHood();

for( i=0; i<m_WndHeight; i++)
	for( j=0; j<m_WndWidth;  j++)
	{
		m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =m_tResPixelArray[i][j].rgbRed=(int)(method1->m_pLikeliHoodArray[i][j]*255);
	    
	}
	//MakeBitMap();
  
	SetCursor(LoadCursor(NULL,IDC_ARROW));	
}

////////////////////////////////////////////////////////////////////////////////
// Binarization
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDoc::OnBtnBinary() 
{
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	int i,j;
//	 long lOffset;
	 LPBYTE lpData = gDib.FindDIBBits(hDIB);
    WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
	if(!method1->CalBinary())
	{
		AfxMessageBox("Please calculate Likehood first!");
		SetCursor(LoadCursor(NULL,IDC_ARROW));	
		return;
	}
	 

    
	for(i=0; i<m_nWndHeight; i++)
	for( j=0; j<m_nWndWidth;  j++)
	{
		m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
		m_tResPixelArray[i][j].rgbRed  = (int)(method1->m_pBinaryArray[i][j]*255);
	
	}

//	MakeBitMap();
	
	SetCursor(LoadCursor(NULL,IDC_ARROW));	
	//MyDraw();
}

////////////////////////////////////////////////////////////////////////////////
// Vertical Histogram
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDoc::HistogramV() 
{
	
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	for(int i=0; i<m_nWndHeight; i++)		
	{
		int count = 0;
		for(int j=0; j<m_nWndWidth;  j++)
		{
			if(method1->m_pBinaryArray[i][j] == 1) count++;
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 255;
		}
		for(j=0; j<count;  j++)
		{
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 0;
		}
	}
	
//	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));			
}

////////////////////////////////////////////////////////////////////////////////
// Horizontal Histogram
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDoc::OnBtnHistogramH() 
{


	SetCursor(LoadCursor(NULL,IDC_WAIT));
	for(int j=0; j<m_nWndWidth;  j++)	
	{
		int count = 0;
		for(int i=0; i<m_nWndHeight; i++)
		{
			if(method1->m_pBinaryArray[i][j] == 1) count++;
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 255;
		}
		for(i=m_nWndHeight-1; i>=m_nWndHeight-count;i--)
		{
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 0;
		}
	}
	
//	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));		
}


////////////////////////////////////////////////////////////////////////////////
//Mark Face Region
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDoc::OnBtnMarkFace() 
{
	
	/****
	   Left and Right
	****************************************************/

	SetCursor(LoadCursor(NULL,IDC_WAIT));
	int *temp = new int[m_nWndWidth];
	int max = 0;
	int pos = -1;
	for(int j=0; j<m_nWndWidth;  j++)   ////////////////Count valid pixels in each column	
	{
		int count = 0;
		for(int i=0; i<m_nWndHeight; i++)
		{
			if(method1->m_pBinaryArray[i][j]== 1) count++;
		}
		temp[j] = count;
		if(count > max)      ////////////////////////which volumn has most valid pixels
		{
			max = count;
			pos = j;
		}
	}

	
	for(l=pos; l>=0; l--)   ////////////////////////get left boundary
	{
		if(temp[l]<max*0.2||l==0)
		{
			left = l;
			break;
		}
	}
	for(l=pos; l<m_nWndWidth; l++)////////////////////////get right boundary
	{
		if(temp[l]<max*0.3||l==m_nWndWidth-1)
		{
			right = l;
			break;
		}
	}

    /******
	   Top and Bottom
	****************************************************/	
     //the var bottom is the relative bottom in the image,but the actual top of the face
	int flag=0;
	
	for(int h=m_nWndHeight-1;h>0;h--)
   {    int count=0;
	   if(flag) break;
	   for(int w=left;w<right;w++)
	   {
		   if(method1->m_pBinaryArray[h][w] == 1)
			   count++;
	   }
              if((count>=(right-left)*0.7))
			  { bottom=h; flag=1;}		   
   }
	
  top=0;
  for(int i=0; i<m_nWndHeight; i++)
	{
		int count = 0;
		for(l = left;l<=right;l++)
		{
			if(method1->m_pBinaryArray[i][l] == 1) count++;
		}
		if( (count>=(right-left)*0.6) && ( (bottom-top)>=(right-left)*1.7) )
		{
		
			top = i;
		}

		}
	
	SetCursor(LoadCursor(NULL,IDC_ARROW));			
	CFaceDetectView *Gd=new CFaceDetectView();
	Gd->DrawLine(left,top,bottom,right);

	CString s1;
	 s1.Format("%d,%d,%d,%d",left,right,top,bottom);
	 
	 CString para = "faceregion:(left,right,top,bottom)"+s1;
	 ::AfxMessageBox(para);
	
	if(m_bFaceOK)
	{
		//ReplaceDoc dlg;
	//	if(dlg.DoModal()==IDOK)
	//	{
			CopyBitMap(m_tResPixelArray,m_tOriPixelArray);
			CRect rect(left,top,right,bottom);
			m_rFaceRegion = rect;
//			MakeBitMap();
		//}
	}
	else
	{
		m_bFaceOK = true;
		CopyBitMap(m_tResPixelArray,m_tOriPixelArray);
		CRect rect(left,top,right,bottom);
		m_rFaceRegion = rect;

	}
}
////////////////////////////////////////////////////////////////////////////////
// 拷贝位图
// 参数：  dest－目标位图指针
//         source－源位图指针    Copy Bitmap 
////////////////////////////////////////////////////////////////////////////////
bool CFaceDetectDoc::CopyBitMap(RGBQUAD **dest, RGBQUAD **source)
{
	if(source==NULL || dest==NULL) 
		return false;
	for(int i=0; i<m_nWndHeight; i++)
		for(int j=0; j<m_nWndWidth; j++)
			dest[i][j]=source[i][j];
	
	return true;
}
////////////////////////////////////////////////////////////////////////////////
// 生成新的位图   Make Bitmap
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDoc::MakeBitMap()
{
	CClientDC ClientDC(pDCShow->GetWindow());
	if(m_pResMap!=NULL) delete m_pResMap;

	m_pResMap=new CBitmap();
	m_pResMap->CreateCompatibleBitmap(&ClientDC,m_nWndWidth,m_nWndHeight);

	CDC  dc;
	dc.CreateCompatibleDC(&ClientDC);
	dc.SelectObject(m_pResMap);

	for(int i=0; i<m_nWndHeight; i++)
	for(int j=0; j<m_nWndWidth; j++)
	dc.SetPixelV(j,i,RGB(m_tResPixelArray[i][j].rgbRed,m_tResPixelArray[i][j].rgbGreen,m_tResPixelArray[i][j].rgbBlue));
    
	if(m_bFaceOK )
	{
		CBrush Pen;
		Pen.CreateSolidBrush(RGB(255,0,0));
		dc.FrameRect(m_rFaceRegion,&Pen);
	 	Pen.DeleteObject();
	}

	if(m_bLeftEyeOK)					DrawCross(&dc,m_LeftEye,RGB(255,0,0));
	if(m_bRightEyeOK)					DrawCross(&dc,m_RightEye,RGB(255,0,0));
	if(m_bLeftEyeLeftCornerOK)			DrawCross(&dc,m_LeftEyeLeftCorner,RGB(255,0,255));
	if(m_bLeftEyeRightCornerOK)			DrawCross(&dc,m_LeftEyeRightCorner,RGB(255,255,0));
	if(m_bRightEyeLeftCornerOK)			DrawCross(&dc,m_RightEyeLeftCorner,RGB(255,0,255));
	if(m_bRightEyeRightCornerOK)		DrawCross(&dc,m_RightEyeRightCorner,RGB(255,255,0));
	if(m_bLeftNostrilOK)				DrawCross(&dc,m_LeftNostril,RGB(0,255,0));
	if(m_bRightNostrilOK)				DrawCross(&dc,m_RightNostril,RGB(0,255,0));
	if(m_bMidNoseOK)					DrawCross(&dc,m_MidNose,RGB(0,255,0));
	if(m_bLeftMouthCornerOK)			DrawCross(&dc,m_LeftMouthCorner,RGB(0,0,255));
	if(m_bRightMouthCornerOK)			DrawCross(&dc,m_RightMouthCorner,RGB(0,0,255));
	if(m_bMidMouthOK)					DrawCross(&dc,m_MidMouth,RGB(0,0,255));

	dc.DeleteDC();

//	MyDraw();
}
////////////////////////////////////////////////////////////////////////////////
// Draw Cross
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDoc::DrawCross(CDC *pDC, CPoint point, COLORREF crColor)
{
	CPen pen,*oldPen;
	pen.CreatePen(PS_SOLID,1,crColor);
	oldPen = (CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(point.x-7,point.y);
	pDC->LineTo(point.x+7,point.y);
	pDC->MoveTo(point.x,point.y-7);
	pDC->LineTo(point.x,point.y+7);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}