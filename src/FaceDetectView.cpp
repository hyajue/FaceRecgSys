// FaceDetectView.cpp : implementation of the CFaceDetectView class
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "DIB.h"
#include "FaceDetectDoc.h"
#include "FaceDetectView.h"
#include "STUDY_1.h"
#include "Tishi.h"
#include "fstream.h"
#include "GetStudyNum.h "
#include "ShowPMessage.h"
#include "XiuGai.h"
#include "DlgZhiFang.h"
#include "GetName.h"
#include "Message.h"
#include "shujuyanchi.h"
#include "Meg.h"
#include "DelectMessage.h"
#include "FINDMESSAGE.h"
#include "math.h"
#define WIDTHBYTES(bits)  ((bits+31)/32*4)
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
DIB gDib;
 HANDLE hDIB;
 HANDLE hDIB1;
HANDLE hDIBTemp;
HANDLE hDIBTemp1;
 int gheight;
 int gwidth;
 WORD gwBytesPerLine;
 static int v_left,v_top,v_bottom,v_right;
 
/////////////////////////////////////////////////////////////////////////////
// CFaceDetectView

IMPLEMENT_DYNCREATE(CFaceDetectView, CView)

BEGIN_MESSAGE_MAP(CFaceDetectView, CView)
	//{{AFX_MSG_MAP(CFaceDetectView)
	ON_COMMAND(ID_READY_LIGHTINGCONPENSATE, OnReadyLightingconpensate)
	ON_COMMAND(ID_READY_SCALE, OnReadyScale)
	ON_COMMAND(ID_READY_ContrastEnhance, OnREADYContrastEnhance)
	ON_COMMAND(ID_READY_ZFT, OnReadyZft)
	ON_COMMAND(ID_READY_WHITEBLACK, OnReadyWhiteblack)
	ON_COMMAND(ID_READY_BanishOnlyPoint, OnREADYBanishOnlyPoint)
	ON_COMMAND(ID_READY_Mediumvalue, OnREADYMediumvalue)
	ON_COMMAND(ID_READY_DilationFirst, OnREADYDilationFirst)
	ON_COMMAND(ID_READY_Decay, OnREADYDecay)
	ON_COMMAND(ID_READY_OutLine, OnREADYOutLine)
	ON_COMMAND(ID_READY_FixedPosition, OnREADYFixedPosition)
	ON_COMMAND(ID_PROCESSING_GetCharacteristicParameter, OnPROCESSINGGetCharacteristicParameter)
	ON_COMMAND(ID_PROSSING_detect, OnPROSSINGdetect)
	ON_COMMAND(AFX_ID_VIDIO, OnIdVidio)
	ON_COMMAND(ID_VIDIO_CANNEL, OnVidioCannel)
	ON_COMMAND(AFX_ID_PROSSING, OnIdProssing)
	ON_COMMAND(ID_READY_Template, OnREADYTemplate)
	ON_BN_CLICKED(IDOK_GetName, OnGetName)
	ON_COMMAND(ID_PROSSING_STUDY, OnProssingStudy)
	ON_COMMAND(ID_DETECTFACE, OnDetectface)
	ON_COMMAND(ID_STUDY_MENUITEM32798, OnStudyMenuitem32798)
	ON_COMMAND(ID_DATABASE_FIND, OnDatabaseFind)
	ON_COMMAND(ID_DATABASE_Delete, OnDATABASEDelete)
	ON_COMMAND(ID_MENUITEM32799, OnMenuitem32799)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectView construction/destruction

CFaceDetectView::CFaceDetectView()
{
	// TODO: add construction code here
	Study=0;
	pname="temp";
	Picture=1;
	Picture1=1;
	flagP=false;
	lpRgb = NULL;
	lpYcc = NULL;
	faceNum = 0;
	for(int i=0; i<ImgRange; i++)
		for (int j=0; j<ImgRange; j++)
		{
			this->emymapc[i][j] = false;
			this->emymapl[i][j] = false;
			this->lab[i][j] = false;
		}
	this->result = false;
       v_left=0;
	   v_top=0;
       v_bottom=0;
	   v_right=0;
	   GetFlag=0;
       FaceAere=false;
	   FaceLine=false;
	   FaceGray=false;
	   FaceGass=false;
	   FaceJunHeng=false;
	   FaceDbidu=false;
	   FaceTwo=false;
	   FaceGuLi=false;
	   FaceDingWei=false;
	   FaceTeZheng=false;
	   FaceShiBie=false;
	   FaceFix=false;
	   FacePara=false;
}

CFaceDetectView::~CFaceDetectView()
{
}

BOOL CFaceDetectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectView drawing

void CFaceDetectView::OnDraw(CDC* pDC)
{
	CFaceDetectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	   CPen NewPen1(PS_SOLID,2,RGB(0,201,87));
	//   CPen NewPen1(PS_SOLID,2,RGB(0,100,255));
	   CPen *pOldPen=pDC->SelectObject(&NewPen1);
		   
	if(hDIB)	   
		gDib.PaintDIBTrue(pDC->GetSafeHdc(),CRect(500+100,10+50,gwidth+500+100,gheight+10+50),hDIB,CRect(0,0,gwidth,gheight),SRCCOPY);

    
	 if(hDIB1)
        gDib.PaintDIBTrue1(pDC->GetSafeHdc(),CRect(500+100-300-100+150,10+300+50,820+100-300-100+150,250+300+50),hDIB1,CRect(0,0,gwidth,gheight),SRCCOPY);
    
	///////////////////////////Camera board///////////////////
	      int x1=10+100;
		  int y1=10+50;
		  int x2=320+10+100;
		  int y2=240+10+50;
		 pDC->MoveTo(x1-5,y1-5);
		 pDC->LineTo(x1-5,y2+5);

		 pDC->MoveTo(x1-5,y2+5);
		 pDC->LineTo(x2+5,y2+5);

		 pDC->MoveTo(x2+5,y2+5);
		 pDC->LineTo(x2+5,y1-5);

		 pDC->MoveTo(x2+5,y1-5);
		 pDC->LineTo(x1-5,y1-5);
		
		 pDC->TextOut(80,100,"C");
         pDC->TextOut(80,120,"a");
		 pDC->TextOut(80,140,"m");
		 
		 //dc.SetROP2(R2_NOTXORPEN);
	   CPen NewPen2(PS_SOLID,2,RGB(0,100,255));
	   pOldPen=pDC->SelectObject(&NewPen2);
//////////////////////Picture board////////////////////////
		   x1=500+100;
		   y1=10+50;
		   x2=820+100;
		   y2=250+50;
		 pDC->MoveTo(x1-5,y1-5);
		 pDC->LineTo(x1-5,y2+5);

		 pDC->MoveTo(x1-5,y2+5);
		 pDC->LineTo(x2+5,y2+5);

		 pDC->MoveTo(x2+5,y2+5);
		 pDC->LineTo(x2+5,y1-5);

		 pDC->MoveTo(x2+5,y1-5);
		 pDC->LineTo(x1-5,y1-5);
         pDC->TextOut(80+490,100,"I");
         pDC->TextOut(80+490,120,"m");
		 pDC->TextOut(80+490,140,"g");
         pDC->TextOut(80+490,160,"");

         
}


/////////////////////////////////////////////////////////////////////////////
//Draw lines for face boundaries

void CFaceDetectView::DrawLine(int left,int top,int bottom ,int right)
{
       v_left=0;
	   v_top=0;
       v_bottom=0;
	   v_right=0;

	   v_left=left-1;
	   v_top=bottom+1; 
       v_bottom=top-1;
	   if (top == 0)
		   v_bottom =0;
	   v_right=right+1;

       LPBYTE lpData;
	  long lOffset;
	  FaceAere=true;
	  lpData = gDib.FindDIBBits(hDIB);
    WORD gwBytesPerLine = gDib.BytePerLine(hDIB);

     for( int i=v_left; i<=v_right; i++)
	 {

              lOffset = gDib.PixelOffset( v_top,i, gwBytesPerLine);
                *(lpData + lOffset)=0;
			    *(lpData + lOffset+1)=205;
				*(lpData + lOffset+2)=0;
             lOffset = gDib.PixelOffset( v_bottom,i, gwBytesPerLine);
			    *(lpData + lOffset)=0;
			    *(lpData + lOffset+1)=205;
				*(lpData + lOffset+2)=0;
             

	 }

	for(int j=v_bottom; j<=v_top; j++)
	{
		  lOffset = gDib.PixelOffset( j,v_left, gwBytesPerLine);
                *(lpData + lOffset)=0;
			    *(lpData + lOffset+1)=205;
				*(lpData + lOffset+2)=0;
          lOffset = gDib.PixelOffset( j,v_right, gwBytesPerLine);
		        *(lpData + lOffset)=0;
			    *(lpData + lOffset+1)=205;
				*(lpData + lOffset+2)=0;
	}
	 
    v_top-=1;
	v_bottom+=1;
	v_left+=1;
	v_right-=1;

	
}

BOOL CFaceDetectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFaceDetectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFaceDetectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectView diagnostics

#ifdef _DEBUG
void CFaceDetectView::AssertValid() const
{
	CView::AssertValid();
}

void CFaceDetectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFaceDetectDoc* CFaceDetectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFaceDetectDoc)));
	return (CFaceDetectDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CFaceDetectView message handlers

/*****************
/***************************Lighting Compensate**************************/
/***************/
void CFaceDetectView::OnReadyLightingconpensate() 
{
	// TODO: Add your command handler code here
	if(FaceAere)
	{
		::AfxMessageBox("Please make sure face boudaries are set!");
		return ;
	}
	ReadyLightingconpensate2(); 
    FaceLine=true;
	FaceAere=false;
}

void CFaceDetectView::ReadyLightingconpensate2() 
{	
	if(!FaceLine)
	{
	//	::AfxMessageBox("Lighting Compensation!");
	}
	hDIBTemp = gDib.CopyHandle(hDIB);
	gDib.LightingCompensate(hDIB);
	GlobalUnlock(hDIB);
	Invalidate();
}

/*****************
/*************************** Gray Scale **************************/
/***************/

void CFaceDetectView::OnReadyScale() 
{
	// TODO: Add your command handler code here
	if(!FaceLine)
	{
	//	::AfxMessageBox("Lighting Compensation!");
	}
   // Mypic();
    ReadyScale3();
    
	FaceGray=true;
    FaceLine=false;
	
}

//Extract Special Pixels from bitmap

void CFaceDetectView::Mypic() 
{
	LPBYTE lpData;
	long lOffset;
	FILE *p1,*p2,*p3,*p4;

	lpData = gDib.FindDIBBits(hDIB);
    WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
	
	unsigned ColorR,ColorG,ColorB;
	double gray;
	int gray_int;
	Gray= new int*[v_top-v_bottom+1];
    
	LPBITMAPINFOHEADER lpbi;
	int width,height;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	                          //width and height   
	width = lpbi->biWidth;
	height = lpbi->biHeight;

	if((p1 = fopen("g://out1.txt","w+"))==NULL)
		::AfxMessageBox("Wrong!");
  //  p2 = fopen("g://out2.txt","w+");
//	p3 = fopen("g://out3.txt","w+");
//	p4 = fopen("g://out4.txt","w+");
    
	

	int k;

	for( k=0;k<v_top-v_bottom+1;k++)
      Gray[k]=new int [v_right-v_left+1];
     
     int k1,i,j;
	 CString s1,s2;
	 s1.Format("%d",width);
	 s2.Format("%d",height);
	 
	 CString para = "width:"+s1+"; height:"+s2;
	 ::AfxMessageBox(para);
	 rewind(p1);

  //  fprintf(p1,"{\n");

	for(i=height-1;i>=0;i--)
	{

		fprintf(p1,"ready[%3d] = %d'b",height-1-i,width);
	//	fprintf(p2,"back_2[%3d] = %d'b",height-1-i,width);
	//	fprintf(p3,"back_3[%3d] = %d'b",height-1-i,width);
	//	fprintf(p4,"back_4[%3d] = %d'b",height-1-i,width);

		for(j=0;j<=width-1; j++)

		{ 
		   

		   lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);

           ColorB=*(lpData + lOffset);
		   ColorG=*(lpData + lOffset+1);
		   ColorR=*(lpData + lOffset+2);
		   
		   gray = (ColorG*50+ColorR*39+ColorB*11)/100;
		   gray_int = gray;
		   

		   if(gray<50) fputc('1',p1);
		   else fputc('0',p1);
		   
     /*
		   
           gray = gray*(16.0/256.0);
		   gray_int = (int)gray;
           
      //     if((gray_int != 12)&&(gray_int!=11)&&(gray_int!=10))
           fprintf(p4,"%d",(gray_int)  %2);
           fprintf(p3,"%d",(gray_int/2)%2);
		   fprintf(p2,"%d",(gray_int/4)%2);
		   fprintf(p1,"%d",(gray_int/8)%2);
	//	   else 
	//	   fprintf(p1," ");
           
         */  

		   

           if(j==width -1) { fputc(';',p1); fputc('\n',p1); }
	//	   if(j==width -1) { fputc(';',p2); fputc('\n',p2); }
	//	   if(j==width -1) { fputc(';',p3); fputc('\n',p3); }
	//	   if(j==width -1) { fputc(';',p4); fputc('\n',p4); }

		}
	}
	fclose(p1);
//	fclose(p2);
//	fclose(p3);
//	fclose(p4);
}



void CFaceDetectView::ReadyScale3() 
{
	LPBYTE lpData;
	long lOffset;

	lpData = gDib.FindDIBBits(hDIB);
    WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
	unsigned ColorR,ColorG,ColorB,gray;
	Gray= new int*[v_top-v_bottom+1];
    
	LPBITMAPINFOHEADER lpbi;
	int width,height;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	                          //width and height   
	width = lpbi->biWidth;
	height = lpbi->biHeight;

	

	int k;

	for( k=0;k<v_top-v_bottom+1;k++)
      Gray[k]=new int [v_right-v_left+1];

     int k1,i,j;
  
	for(i=v_bottom,k=0; i<=v_top; i++,k++)
	{
		for(j=v_left,k1=0; j<=v_right; j++,k1++)

		{  
			lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);

           ColorB=*(lpData + lOffset);
		   ColorG=*(lpData + lOffset+1);
		   ColorR=*(lpData + lOffset+2);
		   gray = (ColorG*50+ColorR*39+ColorB*11)/100;
		   
		   *(lpData + lOffset)=gray ;
		   *(lpData + lOffset+1)=gray ;
		   *(lpData + lOffset+2)=gray ;
		    Gray[k][k1]=gray;

		}
	
	}

    

	//show histogram of current gray values in a new dialog
	DlgZhiFang*  dlg3;
	dlg3=new DlgZhiFang(this);
	dlg3->Create(IDD_DIALOG16);
	int bCount[256];
	double dense[256];
	for(i=0;i<256;i++) bCount[i]=0;

    for(i=v_bottom,k=0; i<=v_top; i++,k++)
		for(j=v_left,k1=0; j<=v_right; j++,k1++)
		{
		 if(Gray[k][k1]!=233)
         bCount[Gray[k][k1]]++;
		}

	int count=0;
    for(i=0;i<256;i++)
		count+=bCount[i];
	
	for(i=0;i<256;i++)
		dense[i] = ((double)bCount[i]/(double)count);

    for (i = 0; i <256; i++)
		dlg3->m_fIntensity[i] = dense[i] ;

	dlg3->ShowWindow(SW_RESTORE);
   Invalidate();
  
	
}

/*****************
/***************************Gaussian Smoothing**************************/
/***************/

void CFaceDetectView::OnREADYTemplate() 
{
	// TODO: Add your command handler code here
	if(!FaceGass)
		{
//		::AfxMessageBox("Gaussian Smoothing!");
	//	return ;
	}
    
	READYTemplate4();
	FaceGray=false;
    FaceGass=true;
}

void CFaceDetectView::READYTemplate4() 
{
	//Template parameter
	double tem[9]={1,2,1,
		           2,4,2,
				   1,2,1};

    //Template co
    double  xishu = 0.0625;   
   // double xishu = 0.1;

    //operate Template
	
	Template(tem ,3,3, xishu);

	Invalidate(TRUE);
}


/*****************
/*************************** Balancing Histogram **************************/
/***************/
void CFaceDetectView::OnReadyZft() 
{
	// TODO: Add your command handler code here
	
	if(!FaceJunHeng)
	{
//		::AfxMessageBox("Balancing Histogram!");
//		return ;
	}
	
    	
	ReadyZft5();
	FaceGass=false;
    FaceJunHeng=true;
}
void CFaceDetectView::ReadyZft5()
{
	LPBYTE lpData;
	long lOffset;
	lpData = gDib.FindDIBBits(hDIB);
    WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
	int k,i;
	int k1;
	ZFT= new int*[v_top-v_bottom+1];
	for( k=0;k<v_top-v_bottom+1;k++)
      ZFT[k]=new int [v_right-v_left+1];

	//store the counts of every gray value
    int lCount[256];
	for(int t=0;t<256;t++)
		lCount[t]=0;
    for(i=v_bottom,k=0; i<=v_top; i++,k++)
		for(int j=v_left,k1=0; j<=v_right; j++,k1++)
		{
         lCount[HeightTemplate[k][k1]]++;
		}
	

///////////////////////////////////////////////////////////////////////
		// Calculate Gray Map

		
		int bMap[256],j;

	for (i = 0; i < 256; i++)
	{
		// 0
		int lTemp = 0;		
		for (j = 0; j <= i ; j++)
		{
			lTemp += lCount[j];
		}
		
		// new gray value
		bMap[i] = (BYTE) (lTemp * 255 / (v_top-v_bottom+1) / (v_right-v_left+1));
	}
	

	for( i=v_bottom,k=0; i<=v_top; i++,k++)
		for(int j=v_left,k1=0; j<=v_right; j++,k1++)
		{
           lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
           int state=bMap[HeightTemplate[k][k1]];

           *(lpData + lOffset)=state ;
	       *(lpData + lOffset+1)=state ;
		   *(lpData + lOffset+2)=state ;

		   ZFT[k][k1]=state;

		}



		//show the new histogram

	DlgZhiFang*  dlg3;
	dlg3=new DlgZhiFang(this);
	dlg3->Create(IDD_DIALOG16);
	int bCount[256];
	double dense[256];
	for(i=0;i<256;i++) bCount[i]=0;

    for(i=v_bottom,k=0; i<=v_top; i++,k++)
		for(j=v_left,k1=0; j<=v_right; j++,k1++)
		{
		 if(ZFT[k][k1]!=233)
         bCount[ZFT[k][k1]]++;
		}

	int count=0;
    for(i=0;i<256;i++)
		count+=bCount[i];
	
	for(i=0;i<256;i++)
		dense[i] = ((double)bCount[i]/(double)count);

    for (i = 0; i <256; i++)
		dlg3->m_fIntensity[i] = dense[i] ;

	dlg3->ShowWindow(SW_RESTORE);
		 
	Invalidate();

}


///////////////////////////////////////////////////////////
///   inhance contrast

void CFaceDetectView::OnREADYContrastEnhance() 
{
	// TODO: Add your command handler code here
	if(!FaceJunHeng)
	{
//		::AfxMessageBox("Enhancing Contrast!");
		return ;
	}
	READYContrastEnhance6();
    FaceJunHeng=false;
	FaceDbidu=true;
}

void CFaceDetectView::READYContrastEnhance6()
{
	LPBYTE lpData;
	long lOffset;
	lpData = gDib.FindDIBBits(hDIB);
    WORD gwBytesPerLine = gDib.BytePerLine(hDIB);

	Icd= new int*[v_top-v_bottom+1];
	int k,i;
	for( k=0;k<v_top-v_bottom+1;k++)
     Icd[k]=new int [v_right-v_left+1];

	for( i=v_bottom,k=0; i<=v_top; i++,k++)
		for(int j=v_left,k1=0; j<=v_right; j++,k1++)
		{
           lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
           int state=IncreaseContrast(ZFT[k][k1], 100);    
           *(lpData + lOffset)=state ;
		   *(lpData + lOffset+1)=state ;
		   *(lpData + lOffset+2)=state ;
		   Icd[k][k1]=state;

		}
		 
	Invalidate();

}



int  CFaceDetectView::IncreaseContrast(int pByte,int n)
{
  //adjust contrast with n, the bigger n, the more enhanced contrast
	int Low = n;
	int High = 255-n;
	float Grad = ((float)(High-Low))/255;

	//if smaller than n
	if(pByte<=Low)
		return 0;

	//if medium enhance
	else if ((Low<pByte)&&(pByte<High))
		return int(((pByte-Low)/Grad));
	//else 255
	else
		return  255;

}


///////////////////////// Binaryzation //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
void CFaceDetectView::OnReadyWhiteblack() 
{
	// TODO: Add your command handler code here
	if(!FaceDbidu)
	{
	
	}
     ReadyWhiteblack7();
	 FaceDbidu=false;
	 FaceTwo=true;

}

void CFaceDetectView::ReadyWhiteblack7() 
{
	LPBYTE lpData;
	long lOffset;
	lpData = gDib.FindDIBBits(hDIB);
    WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
	WhiteBlack= new int*[v_top-v_bottom+1];
	
	//////////////////////////////////////////////////////////////////////
 
	int x,y;
	int n,k,k1;
	double Ut1,Ut2;
	 double Qt1;
	 double Qb;
	 double temp=0;
	 for(int t=100;t<256;t++)
	 {     int T_t=0; 
	       int B_t=0;
	       int Gsumn=0;
		   int Gsum=0;
          for(y=v_bottom,k=0; y<=v_top; y++,k++)
		        for(x=v_left,k1=0; x<=v_right; x++,k1++)
				{	
					lOffset = gDib.PixelOffset(y, x, gwBytesPerLine);
					if(Icd[k][k1]>=t)
					{
						T_t++;
                        Gsum=Gsum+Icd[k][k1];
					}
					else
					{
						B_t++;
						Gsumn=Gsumn+Icd[k][k1];
					}
				}

				Qt1=double(T_t)/((v_top-v_bottom+1)*(v_right-v_left+1));
                Ut1=double(Gsum)/T_t;
				Ut2=double(Gsumn)/B_t;
			    Qb=Qt1*(1-Qt1)*(Ut1-Ut2)*(Ut1-Ut2);
                if(Qb>temp)
				{
					temp=Qb;
                    n=t;
				}


	 }

	//////////////////////////////////////////////////////////////////////
	
	int i;
	for( k=0;k<v_top-v_bottom+1;k++)
     WhiteBlack[k]=new int [v_right-v_left+1];
     
	for( i=v_bottom,k=0; i<=v_top; i++,k++)
		for(int j=v_left,k1=0; j<=v_right; j++,k1++)
		{
           lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
           if(ZFT[k][k1]<n-50)
		   {
           *(lpData + lOffset)=0;
		   *(lpData + lOffset+1)=0;
		   *(lpData + lOffset+2)=0;
		   WhiteBlack[k][k1]=0;
		   }
		   else
		   {
		   *(lpData + lOffset)=255;
		   *(lpData + lOffset+1)=255;
		   *(lpData + lOffset+2)=255;
		   WhiteBlack[k][k1]=255;
		   }

		}
		 
	Invalidate();

}




//////////////////////////banish solo points////////////////////////////
void CFaceDetectView::OnREADYBanishOnlyPoint() 
{
      ReadyLightingconpensate2();

	  ReadyScale3();

	  READYTemplate4();

	  ReadyZft5();

	  READYContrastEnhance6();

	  ReadyWhiteblack7();
	


}


//////////////////////////////////////////////////////////////////////
// Median Filter (actually not used,replaced by Gaussian Algorithm)
void CFaceDetectView::OnREADYMediumvalue() 
{
	// TODO: Add your command handler code here
	
CFaceDetectDoc* pDoc = GetDocument();

	
   MidFilter(3,3);

	Invalidate(TRUE);

}


void CFaceDetectView::MidFilter(int tem_w,int tem_h)
{
	LPBYTE lpData;
	int m_Width;
	m_Width=v_right-v_left+1;
    int m_Height;
	int lOffset;
	m_Height=v_top-v_bottom+1;
	BYTE *temp=(BYTE*)malloc(tem_w*tem_h*sizeof(BYTE));
	lpData = gDib.FindDIBBits(hDIB);
	WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
  	for( int i=v_bottom; i<v_top; i++)
	{
		for(int j=v_left; j<v_right; j++)
	   {   
     
          for(int m=i-((tem_h-1)/2);m<=i+((tem_h-1)/2);m++)
          {
		     for(int n=j-((tem_w-1)/2);n<=j+((tem_w-1)/2);n++)
			 {
            
			  lOffset = gDib.PixelOffset(m, n, gwBytesPerLine);
		      temp[(m-i+((tem_h-1)/2))*tem_w+n-j+((tem_w-1)/2)]=*(lpData + lOffset);
			 }

          int mid;
		
           for(m=0;m<tem_w*tem_h-1;m++)
           {
		   
		      for(n=0;n<tem_w*tem_h-m-1;n++)
			 
			    if(temp[n]>temp[n+1]) 
                {
			    mid=temp[n];
                temp[n]=temp[n+1];
			    temp[n+1]=mid;
			  }
		   
		   } 

        
		       lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
              *(lpData + lOffset++) = temp[(tem_w*tem_h-1)/2];
			  *(lpData + lOffset++) = temp[(tem_w*tem_h-1)/2];
			  *(lpData + lOffset++) = temp[(tem_w*tem_h-1)/2];

	      
		 }
	   }
	}
	
}

void CFaceDetectView::OnREADYDilationFirst() 
{
	// TODO: Add your command handler code here
	gDib.Dilation(hDIB,v_top,v_bottom,v_left,v_right);
	gDib.Dilation(hDIB,v_top,v_bottom,v_left,v_right);
	Invalidate();
	
}

void CFaceDetectView::OnREADYDecay() 
{
	// TODO: Add your command handler code here
	
    gDib.Erasion(hDIB,v_top,v_bottom,v_left,v_right);
	gDib.Erasion(hDIB,v_top,v_bottom,v_left,v_right);
	gDib.Erasion(hDIB,v_top,v_bottom,v_left,v_right);
	Invalidate();


}




void CFaceDetectView::OnREADYOutLine() 
{
    LPBYTE lpData;
	lpData = gDib.FindDIBBits(hDIB);
	WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
  
	//vars
     int  i;
      int j;
	unsigned char n,e,s,w,ne,se,nw,sw;


   
	
       

	int k,k1;
	for(  i=v_bottom+1,k=1; i<v_top; i++,k++)
	{
		for( j=v_left+1,k1=1; j<v_right; j++,k1++)
		{
			int pixel = Icd[k][k1];
			
			if(pixel == 0)
			{
				
				nw = Icd[k][k1-1];
				n  = Icd[k+1][k1-1];
				ne = Icd[k+1][k1];
				w = Icd[k+1][k1+1];
				e = Icd[k][k1+1];
				sw =Icd[k-1][k1+1];
				s  = Icd[k-1][k1];
				se = Icd[k-1][k1-1];
			
				if(nw+n+ne+w+e+sw+s+se==0)
				{
					int lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
					*(lpData + lOffset++) = 255;
			        *(lpData + lOffset++) = 255;
			        *(lpData + lOffset++) = 255;


				}
			}
		}
	}


Invalidate();

}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////FACIAL POSITIONING///////////////////////////////////////////
void CFaceDetectView::OnREADYFixedPosition() 
{
	// TODO: Add your command handler code here
	
	READYFixedPosition8();
	FaceFix=true;
   

}

bool CFaceDetectView::READYFixedPosition8() 
{
    bool Over;
     
	 Over=FixeEyes();
	 if(!Over)
		 return false;
	 FaceGuLi=false;

	 FixeNose();
	 FixeMouth();
	
	 Invalidate();
	 return true;

}
///////////////////////////////////// Eye Position ////////////////////////////////////////
bool CFaceDetectView::FixeEyes()
{
	int i,j,k,k1,k_Middle,k1_Middle;
	LPBYTE lpData;
	lpData = gDib.FindDIBBits(hDIB);
	WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
	int lOffset;

	
	i=j=0;
    if((v_right-v_left)*(v_top-v_bottom)<10)
	{
		::AfxMessageBox("Face Too Small,Can't Recognize!");
		return false;
	}

	// Htemp is to record the maximum number of '0' values in a horizontal line ie. vertical cooridinate is fixed.
	// the line with maximum number of '0'(effective )values is the potential(still not) center horizontal line of the left eye


	Htemp=new int[(v_top-v_bottom)/2+1]; 

	for(i=0;i<(v_top-v_bottom)/2+1;i++)

		Htemp[i]=0;																																																																			

    //relative coordinates
	//half length of face
	k_Middle=(v_top-v_bottom)/2;
    // half width of face
	k1_Middle=(v_right-v_left)/2;
	 
    /////////////////////////////////////////////// Relative Left(Actual Right) Eye ////////////////////////
	 int Max=0;
	 int SMax=0;
	 int Line=0;
	 int BsecondLine=0;
	     L_teye=10000;
	
	 int L_EyeMiddleLine=0;
	 int TSecondLine=0;
	     L_beye=0;

	for(i=(v_top+v_bottom)/2,k=0;i<=v_top;i++,k++)
		for(j=v_left+(v_right-v_left)/2,k1=0;j<=v_left+(v_right-v_left);j++,k1++)
          if(WhiteBlack[k+k_Middle][k1+k1_Middle]==0)
		  {
                Htemp[k]++;
		  }
		  
  


	for(i=1;i<(v_top-v_bottom)/2-2;i++)
	{
		if(Htemp[i]>Max)
		{   
			Max=Htemp[i];
	    	Line=i;
			
		}
       
	}

if(Max<((v_right-v_left)/25))
  {
   ::AfxMessageBox("Please make sure there are eyes in the picture!");
 //   return false ;
  }
  

////////////////////////////////////////Left Crest

int t1=Htemp[(v_top-v_bottom)/10+3];
int t2=Htemp[(v_top-v_bottom)/10+4];
int t3=Htemp[(v_top-v_bottom)/10+5];
int t4=Htemp[(v_top-v_bottom)/10+6];
int t5=Htemp[(v_top-v_bottom)/10+7];
int t6=Htemp[(v_top-v_bottom)/10+8];
int t7=Htemp[(v_top-v_bottom)/10+9];

int M_Line=Line;
int t=0;
int top=0;



for(i=(v_top-v_bottom)/10+10;i<Line+4;i++)
{   
   if(t4>=t1&&t4>=t2&&t4>=t3&&t4>=t5&&t4>=t6&&t4>=t7&&t4>Max*0.25)
		{   
	    	Line=i-2;
			break;		
		}
  
   t1=t2;
   t2=t3;
   t3=t4;
   t4=t5;
   t5=t6;
   t6=t7;
   t7=Htemp[i];

   
}



//////////////////////////////////////////// Top Left
///////////////////////////////fix to 0.3
int jump=0;

if(Line+2<(v_top-v_bottom)/2)
for(double xishu=0.3;xishu<0.9;xishu=xishu+0.1)
{
	if(jump==1)
	break;

    for(i=Line+1;i<(v_top-v_bottom)/2;i++)
	{
	     if(Htemp[i]<=Max*xishu)
		 {
			  L_teye=i;jump=1;
			  break;
		 }
	}

	
}

/////////////////////////////////////////  Bottom Left
if((Line-1)>0)
    for(i=Line-1;i>=0;i--)
	{
	  if(Htemp[i]<=Max*0.3)
		 {
			 L_beye=i;
			 break;
		 }
	}

L_EyeMiddleLine=Line;

 
//////////////////////////////////////// Left Boundaryof Lefteye
	 
  H_lleye=0;
  H_lreye=0;

  for(j=((v_right-v_left)/5)*3+((v_right-v_left)/5)/2;j<(v_right-v_left);j++)
  {   int  Count=0;
	  for(i=L_beye+(v_top-v_bottom)/2;i<L_teye+(v_top-v_bottom)/2;i++)
	  {
	  if(WhiteBlack[i][j]==0)
	   Count++;
	  }
	   if(Count<(L_teye-L_beye)/5||j==(v_right-v_left-1))
	   {H_lleye=j;
	    break;
	   }
  }

  //////////////////////////////////// Right Boundaryof Lefteye
  for(j=((v_right-v_left)/5)*3+((v_right-v_left)/5)/2;j>(v_right-v_left)/2;j--)
  {   int  Count=0;
	  for(i=L_beye+(v_top-v_bottom)/2;i<L_teye+(v_top-v_bottom)/2;i++)
	  {
	  if(WhiteBlack[i][j]==0)
	   Count++;
	  }
	   if(Count<(L_teye-L_beye)/5||j==(v_right-v_left)/2+1)
	   {H_lreye=j;
	    break;
	   }
  }
  
   

/////////////////////////////////////////Relative Right (Actual Left) Eye///////////////////////////

	   Max=0;
	   k1_Middle=(v_right-v_left)/5;
	   k_Middle=(v_top-v_bottom)/2;
	   int R_EyeMiddleLine=0;
	   int Count=0;
	       R_teye=0;

       for(i=0;i<(v_top-v_bottom)/2+1;i++)
		          Htemp[i]=0;
	  for(i=(v_top+v_bottom)/2,k=0;i<=v_top;i++,k++)
		for(j=v_left,k1=0;j<=v_left+(v_right-v_left)/2;j++,k1++)
          if(WhiteBlack[k+k_Middle][k1]==0)
		  {
                Htemp[k]++;
		  }
  
		  
for(i=5;i<(v_top-v_bottom)/2-2;i++)
	{
		if(Htemp[i]>Max)
		{   
			Max=Htemp[i];
	    	Line=i;
			
		}
       
	}
int SLine=Line;

///////////////////////////////////Right Crest
 int x1=Htemp[5];
 int x2=Htemp[6];
 top=0;
for(i=8;i<Line+4;i++)
{   
   if(top>x1&&top>x2&&top>Max*0.25)
		{   
	    	Line=i-2;
			break;		
		}
   else
   {
    if(x1>x2)
		t=x1;
	else
		t=x2;

	top=t;

   }
   x1=Htemp[i];
   x2=Htemp[++i];
   
}

if(Line<L_EyeMiddleLine-15)
{
 t=0;
 x1=Htemp[L_EyeMiddleLine-15];
 x2=Htemp[L_EyeMiddleLine-14];
 top=0;
 
for(i=L_EyeMiddleLine-13;i<L_EyeMiddleLine+10;i++)
{   
   if(top>x1&&top>x2&&top>Max*0.25)
		{   
	    	Line=i-2;
			break;		
		}
   else
   {
    if(x1>x2)
		t=x1;
	else
		t=x2;

	top=t;

   }
   x1=Htemp[i];
   x2=Htemp[++i];
   
}


}

  R_EyeMiddleLine=Line;

/////////////////////////////////Top Right	
jump=0;
R_teye=0;
if(R_EyeMiddleLine+5<(v_top-v_bottom)/2)
for(double xishu=0.3;xishu<0.9;xishu=xishu+0.1)
{	 
   for(i=Line+1;i<(v_top-v_bottom)/2;i++)
	{
	     if(Htemp[i]<=Max*xishu)
		 {
			  R_teye=i;jump=1;
			  break;
		 }
	}
   if(jump==1)
	   break;
	
}

/////////////////////////////////Bottom Right
     R_beye=0;
    if((R_EyeMiddleLine-5)>0)
      for(i=Line-1;i>=0;i--)
	{
	  if(Htemp[i]<=Max*0.3)
		 {
			 R_beye=i;
			 break;
		 }
	}

///////////////////////////////Left Boundaryof Righteye
  H_rleye=0;
  H_rreye=0;
  for(j=((v_right-v_left)/5)*1+((v_right-v_left)/5)/2;j<(v_right-v_left)/2;j++)
  {   int  Count=0;
	  for(i=R_beye+(v_top-v_bottom)/2;i<R_teye+(v_top-v_bottom)/2;i++)
	  if(WhiteBlack[i][j]==0)
	   Count++;
	   if(Count<(R_teye-R_beye)/5)
	   {H_rleye=j;
	    break;
	   }
  }
/////////////////////////////////Right Boundaryof Righteye
  for(j=((v_right-v_left)/5)+((v_right-v_left)/5)/2;j>0;j--)
  {   int  Count=0;
	  for(i=R_beye+(v_top-v_bottom)/2;i<R_teye+(v_top-v_bottom)/2;i++)
	  if(WhiteBlack[i][j]==0)
	   Count++;
	   if(Count<(R_teye-R_beye)/5)
	   {H_rreye=j;
	    break;
	   }
  }
  
  if((H_rleye-H_rreye)<(H_lleye-H_lreye))
	  H_rreye=H_rleye-(H_lleye-H_lreye);
  else
	  H_lleye=H_lreye+(H_rleye-H_rreye);
  if(((L_teye-L_beye)-(R_teye-R_beye))>2)
	  L_teye=L_beye+(R_teye-R_beye);
  if(((R_teye-R_beye)-(L_teye-L_beye))>2)
	  R_teye=R_beye+(L_teye-L_beye);
////////////////////////////////////////////////////////////

  /*
  if(R_beye>L_teye||R_beye==L_teye||R_teye<L_beye||R_teye==L_beye)
  {
   ::AfxMessageBox("Please Recheck Pic!");
    return false ;
  }
  */

  //////////////////////////////////// SUM UP EYE COORDINATES///////////////////////////////////////
///////////////////////////////////////////////////////////
   //Left (Actual Right) Eye
    int m_top=(v_top-v_bottom)/2+L_teye;
    int m_bottom=(v_top-v_bottom)/2+L_beye;
    int m_left=H_lreye;
    int m_right=H_lleye;

  int L_EyeTopY=L_teye+(v_top-v_bottom)/2+v_bottom;
  int L_EyeTopX=TopPoint(m_top, m_bottom, m_left,m_right)+v_left;
      DrawCrossX(L_EyeTopX,L_EyeTopY);
  
	 
  L_EyeLY=(L_teye-L_beye)/3+(v_top-v_bottom)/2+v_bottom+L_beye+1;
  L_EyeLX=v_left+H_lleye;
      DrawCrossX(L_EyeLX,L_EyeLY);

  L_EyeRY=(L_teye-L_beye)/3+(v_top-v_bottom)/2+v_bottom+L_beye+1;
  L_EyeRX=v_left+H_lreye;
  DrawCrossX(L_EyeRX,L_EyeRY);

  int L_EyeBY=v_bottom+(v_top-v_bottom)/2+L_beye;
  int L_EyeBX=L_EyeTopX;
  DrawCrossX(L_EyeBX,L_EyeBY);
		  

///////////////////////////////////////////////////////////////////////////////

 //Right (actual left) eye
 //relative coordinates according to face area
  m_top=(v_top-v_bottom)/2+R_teye;
  m_bottom=(v_top-v_bottom)/2+R_beye;
  m_left=H_rreye;
  m_right=H_rleye;

  //absolute coordinates according to the whole pic
  int R_EyeTopY=R_teye+(v_top-v_bottom)/2+v_bottom;  
  int R_EyeTopX=TopPoint(m_top, m_bottom, m_left,m_right)+v_left;

  DrawCrossX(R_EyeTopX,R_EyeTopY);

  R_EyeLY=(R_teye-R_beye)/3+(v_top-v_bottom)/2+v_bottom+R_beye+1;
  R_EyeLX=v_left+H_rleye;
          DrawCrossX(R_EyeLX,R_EyeLY);

  R_EyeRY=(R_teye-R_beye)/3+(v_top-v_bottom)/2+v_bottom+R_beye+1;
  R_EyeRX=v_left+H_rreye;
     DrawCrossX(R_EyeRX,R_EyeRY);

  int R_EyeBY=v_bottom+(v_top-v_bottom)/2+R_beye;
  int R_EyeBX= R_EyeTopX;
       DrawCrossX(R_EyeBX,R_EyeBY);

	 


return true;
}

int CFaceDetectView::TopPoint(int m_top,int m_bottom,int m_left,int m_right)
{
    int Max=0;
	int L,R;
   for(int j=m_left;j<m_right;j++)
   { int Count=0;
	   for(int i=m_bottom;i<m_top;i++)
		   if(WhiteBlack[i][j]==0)
	             Count++;
		   if(Max<Count)
		   {
			   Max=Count; L=j;
		   }
   }

 Max=0;
 for(j=m_right;j>m_left;j--)  
   { int Count=0;
	   for(int i=m_bottom;i<m_top;i++)
		   if(WhiteBlack[i][j]==0)
	             Count++;
		   if(Max<Count)
		   {
			   Max=Count; R=j;
		   }
   }
   return (L+R)/2;



}


///////////////////////////////////// Nose Position ////////////////////////////////////////
void CFaceDetectView::FixeNose()
{   
	int N_top;
	int i,j;
	LPBYTE lpData;
	lpData = gDib.FindDIBBits(hDIB);
	WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
	int lOffset;
	if(R_beye>L_beye)
		N_top=L_beye;
	else
		N_top=R_beye;
    T_NoseMiddleLine=0;
	    B_NoseMiddleLine=0;
    int a=(H_rleye-H_lreye)*0.5;
	for(i=(v_top-v_bottom)/2+N_top-10;i>(v_top-v_bottom)/4;i--)
		{   int Count=0;
			for(j=H_rleye;j<H_lreye;j++)
			{
				if(WhiteBlack[i][j]==0)
					Count++;
			}
			if(((v_right-v_left)/5)*0.1<Count)
			{  
			    T_NoseMiddleLine=i; 
				break;
			}
        }

  
	for(i=T_NoseMiddleLine-3;i>(v_top-v_bottom)/4;i--)
		{   int Count=0;
			for(j=((v_right-v_left)/5)*2;j<((v_right-v_left)/5)*3;j++)
			{
				if(WhiteBlack[i][j]==0)
					Count++;
			}
			if(((v_right-v_left)/5)*0.3>Count)
			{
			    B_NoseMiddleLine=i; 
				break;
			}
        }



  ///////////////////////  Left ////////////////////////////////////////
    H_lnose=0;
	for(j=(H_lreye+H_rleye)/2;j<((v_right-v_left)/5)*4;j++)
		{   int Count=0;
			for(i=B_NoseMiddleLine;i<T_NoseMiddleLine;i++)
			{
				if(WhiteBlack[i][j]==0)
					Count++;
			}
			if((T_NoseMiddleLine-B_NoseMiddleLine)*0.3<Count)
			{
			    H_lnose=j; 
			
			}
        }


///////////////////////Right   //////
H_rnose=0;
	for(j=(H_lreye+H_rleye)/2;j>((v_right-v_left)/5);j--)
		{   int Count=0;
			for(i=B_NoseMiddleLine;i<T_NoseMiddleLine;i++)
			{
				if(WhiteBlack[i][j]==0)
					Count++;
			}
			if((T_NoseMiddleLine-B_NoseMiddleLine)*0.3<Count)
			{
			    H_rnose=j; 
			
			}
        }
if(H_lnose==0)
  H_lnose=H_lreye;
if(H_rnose==0)
  H_rnose=H_rleye;
  

//////////////////////////////////////////////////////////////////////////
  int N_left=(H_lnose+H_rnose)/2;
  int N_right=((v_right-v_left)/5)*4;
  int N_ntop=T_NoseMiddleLine;
  int N_bottom=B_NoseMiddleLine;
      L_noseX=  H_lnose+v_left;
  L_noseY=NoseY(N_left,N_right,N_ntop,N_bottom)+v_bottom;
      

  N_left=((v_right-v_left)/5);
  N_right=(H_lnose+H_rnose)/2;
  N_ntop=T_NoseMiddleLine;
  N_bottom=B_NoseMiddleLine;
  R_noseX=H_rnose+v_left;
  R_noseY=NoseY(N_left,N_right,N_ntop,N_bottom)+v_bottom;

  L_noseY=(L_noseY+R_noseY)/2;
  R_noseY=L_noseY;
  
   //***************************************************************    Middle Point (important!!)
   N_MiddleX=(R_noseX+L_noseX)/2;
   N_MiddleY=(L_noseX-R_noseX)*0.4+L_noseY;
   
   DrawCrossX(N_MiddleX, N_MiddleY);

 
  DrawCrossX(L_noseX,L_noseY);
  DrawCrossX(R_noseX,R_noseY);

}

int CFaceDetectView::NoseX(int N_left,int N_right,int N_top,int N_bottom)
{
	int Max=0;
	int N_x;
   for(int i=N_left;i<N_right;i++)
   {  int Count=0;
	   for(int j=N_bottom;j<N_top;j++)
	   {
          if(WhiteBlack[j][i]==0)
			Count++; 
	   }
	   if(Max<Count)
	   {
		   Max=Count;
		   N_x=i;
	   }
   }
   for( i=N_x;i<N_right;i++)
   {    int  Count=0;
	   for(int j=N_bottom;j<N_top;j++)
	   {
          if(WhiteBlack[j][i]==0)
			Count++; 
	   }
	   if(Max*0.5>Count)
	   {
		   N_x=i;break;

	   }
   }
   return N_x;
}

int CFaceDetectView::NoseRX(int N_left,int N_right,int N_top,int N_bottom)
{
	int Max=0;
	int N_x;
   for(int i=N_right;i>N_left;i--)
   {  int Count=0;
	   for(int j=N_bottom;j<N_top;j++)
	   {
          if(WhiteBlack[j][i]==0)
			Count++; 
	   }
	   if(Max<Count)
	   {
		   Max=Count;
		   N_x=i;
	   }
   }

   for(i=N_x;i>N_left;i--)
   {  int Count=0;
	   for(int j=N_bottom;j<N_top;j++)
	   {
          if(WhiteBlack[j][i]==0)
			Count++; 
	   }
	   if(Max*0.5>Count)
	   {
		   N_x=i;break;
	   }
   }
   return N_x;
}
int CFaceDetectView::NoseY(int N_left,int N_right,int N_top,int N_bottom)
{
	int Max=0;
	int N_y;
   for(int j=N_bottom;j<N_top;j++)
   {  int Count=0;
	   for(int i=N_left;i<N_right;i++)
	   {
          if(WhiteBlack[j][i]==0)
			Count++; 
	   }
	   if(Max<Count)
	   {
		   Max=Count;
		   N_y=j;
	   }
   }
   return N_y;
}

/////////////////////////////////////Mouth Position////////////////////////////////////////
void CFaceDetectView::FixeMouth()
{
  T_MouthMiddleLine=0;
  B_MouthMiddleLine=0;
  LPBYTE lpData;
  lpData = gDib.FindDIBBits(hDIB);
  WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
	int lOffset;
int i,j;
for(i=B_NoseMiddleLine-2;i>1;i--)
		{   int Count=0;
			for(j=((v_right-v_left)/5)*2;j<((v_right-v_left)/5)*3;j++)
			{
				if(WhiteBlack[i][j]==0)
					Count++;
			}
			if(((v_right-v_left)/5)*0.3<Count)
			{
			    T_MouthMiddleLine=i; 
				break;
			}
        }
    int jump=0;
	for(i=T_MouthMiddleLine-((v_right-v_left)/5)*0.5;i>3;i--)
		{   int Count=0;
			for(j=((v_right-v_left)/5)*2;j<((v_right-v_left)/5)*3;j++)
			{
				if(WhiteBlack[i][j]==0)
					Count++;
			}
			if(((v_right-v_left)/5)*0.3>Count)
			{
			    B_MouthMiddleLine=i; 
				
				break;
			}
			
        }

	int M_Max=0;
	int M_Line=0;
	for(i=B_NoseMiddleLine-2;i>B_NoseMiddleLine-22;i--)
	{   int Count=0;
		for(j=0;j<(v_right-v_left);j++)
		{
         if(WhiteBlack[i][j]==0)
			 Count++;
		}
		if(M_Max<Count)
		{
         M_Max=Count;
		 M_Line=i;
		}
	}
/*
///////////////////////////////////////////////////////////////////////////////////
for(j=v_left;j<v_right;j++)
{
	  lOffset = gDib.PixelOffset(M_Line+v_bottom, j, gwBytesPerLine);
					*(lpData + lOffset) = 0;
			        *(lpData + lOffset+1) = 0;
			        *(lpData + lOffset+2) =255;
					

}
//////////////////////////////////////////////////////////////////////////////////
*/


   H_lMouth=0;
   H_rMouth=0;
   int B_Underjaw = 0;

   //mouth left and right

  for(j=((v_right-v_left)/5)*2+((v_right-v_left)/5)/2+10;j<(v_right-v_left);j++)
  {   int  Count=0;
	  for(i=B_MouthMiddleLine;i<T_MouthMiddleLine+2;i++)
	  if(WhiteBlack[i][j]==0)
	   Count++;
	   if(Count<(T_MouthMiddleLine-B_MouthMiddleLine)/4)
	   {H_lMouth=j;
	    break;
	   }
  }

  for(j=((v_right-v_left)/5)*2+((v_right-v_left)/5)/2-6;j>0;j--)
  {   int  Count=0;
	  for(i=B_MouthMiddleLine;i<T_MouthMiddleLine+2;i++)
	  if(WhiteBlack[i][j]==0)
	   Count++;
	   if(Count<(T_MouthMiddleLine-B_MouthMiddleLine)/4)
	   {H_rMouth=j;
	    break;
	   }
  }

  for (j=H_rMouth;j<H_lMouth;j++)
  {
	  int Count = 0;
	  for(i=(v_top-v_bottom)/10 ;i<B_MouthMiddleLine+1;i++)
		  if(WhiteBlack[i][j]==0)
	      Count++;
	  if(Count > (v_right-v_left)*0.1)
		  B_Underjaw = j;

  }
  //under jaw

////////////////////////////////////////////////////////////////////////////
       N_MiddleX=((H_rleye+H_lreye)/2+v_left+N_MiddleX)/2;
	  if(((N_MiddleX-v_left)-H_rMouth)>(H_lMouth-(N_MiddleX-v_left)))
	  {
		  M_RX=H_rMouth+v_left ;
		  M_RY=M_Line+v_bottom;

          M_LX=((N_MiddleX-v_left)-H_rMouth)+(N_MiddleX-v_left)+v_left-2;
		  M_LY=M_Line+v_bottom;
	  }
	  else
	  { 
		   M_LX=H_lMouth+v_left ;
		   M_LY=M_Line+v_bottom;

		   M_RX=(N_MiddleX-v_left)-(H_lMouth-(N_MiddleX-v_left))+v_left+3;
		   M_RY=M_Line+v_bottom;
	  }

	  if(M_LX<L_noseX)
		  M_LX=L_noseX+(L_noseX-R_noseX)/2;
	  if(M_RX>R_noseX)
          M_RX=R_noseX-(L_noseX-R_noseX)/2;

      DrawCrossX( M_LX,  M_LY);
	  
      DrawCrossX( M_RX, M_RY);

	  xiabaX=N_MiddleX;
	  //xiabaY=N_MiddleY-(2*(L_teye+(v_top-v_bottom)/2-N_MiddleY+v_bottom))*4/5;
	  xiabaY=N_MiddleY-(N_MiddleY-T_MouthMiddleLine-v_bottom)*2-(N_MiddleY-T_MouthMiddleLine-v_bottom)/4;
	  DrawCrossX( xiabaX, xiabaY);
	 

}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Extracting Feature Parameters////////////////////////////////////
void CFaceDetectView::OnPROCESSINGGetCharacteristicParameter() 
{
	// TODO: Add your command handler code here

 /*   
	Centerofgravity();
	GetEyesParameter();
    GetPartParameter();
	GetNoseParameter() ;
	GetmouthParameter() ;	
*/	

	GetNewParameter();

	FacePara=true;
	Invalidate();
	
}

///////////////////////////////////////////////////////////////////////
void CFaceDetectView::GetNewParameter()
{     
      CString para,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11;
      x1=TwoPointDistance(R_EyeRX,R_EyeRY,N_MiddleX,N_MiddleY)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x2=TwoPointDistance(R_EyeLX,R_EyeLY,N_MiddleX,N_MiddleY)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x3=TwoPointDistance(L_EyeRX,L_EyeRY,N_MiddleX,N_MiddleY)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x4=TwoPointDistance(L_EyeLX,L_EyeLY,N_MiddleX,N_MiddleY)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x5=TwoPointDistance(R_noseX,R_noseY,N_MiddleX,N_MiddleY)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x6=TwoPointDistance(L_noseX,L_noseY,N_MiddleX,N_MiddleY)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x7=TwoPointDistance(M_RX, M_RY,N_MiddleX,N_MiddleY)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x8=TwoPointDistance(M_LX, M_LY,N_MiddleX,N_MiddleY)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x9=(L_EyeRX-R_EyeLX)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x10=(L_noseX-R_noseX)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

	  x11=(M_LX-M_RX)/TwoPointDistance(N_MiddleX,N_MiddleY,xiabaX,xiabaY);

      s1.Format("%7.4f",x1);
	  s2.Format("%7.4f",x2);
	  s3.Format("%7.4f",x3);
	  s4.Format("%7.4f",x4);
	  s5.Format("%7.4f",x5);
	  s6.Format("%7.4f",x6);
	  s7.Format("%7.4f",x7);
	  s8.Format("%7.4f",x8);
	  s9.Format("%7.4f",x9);
	  s10.Format("%7.4f",x10);
	  s11.Format("%7.4f",x11);
      
	  para="x1:   "+s1+"\nx2:   "+s2+"\nx3:   "+s3+"\nx4:   "+s4+"\nx5:   "+s5+"\nx6:   "+s6+"\nx7:   "+s7+"\nx8:   "+s8+"\nx9:   "+s9+"\nx10:  "+s10+"\nx11:  "+s11;
	  ::AfxMessageBox(para);
	  
	  
	  
}
double CFaceDetectView::TwoPointDistance(int x1,int y1,int x2,int y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

///////////////////////////////////////Get Center Of Gravity of organs(not used finally)///////////////////////
void CFaceDetectView::Centerofgravity()
{
///////////////////////Left Eye////////////////////////////////////////////
	int i,j,x,y;
	int sumx=0;
	int sumy=0;
	int sumg=0;
		for(i=(v_top-v_bottom)/2+L_beye,y=1;i<=(v_top-v_bottom)/2+L_teye;i++,y++)
		for(j=H_lreye,x=1;j<=H_lleye;j++,x++)
          if(WhiteBlack[i][j]==0)
		  {
               sumx=sumx+x; 
			   sumy=sumy+y;
			   sumg++;
		  }
    Cofg_lefteyex=sumx/sumg;
	Cofg_lefteyey=sumy/sumg;

     DrawCrossX(v_left+H_lreye+Cofg_lefteyex,(v_top+v_bottom)/2+L_beye+Cofg_lefteyey);

///////////////////////right eye////////////////////////////////////////////

       sumx=0;
	   sumy=0;
	   sumg=0;
	   
	for(i=(v_top-v_bottom)/2+R_beye,y=1;i<(v_top-v_bottom)/2+R_teye;i++,y++)
	{   
		for(j=H_rreye,x=1;j<=H_rleye;j++,x++)
          if(WhiteBlack[i][j]==0)
		  { 
               sumx=sumx+x; 
			   sumy=sumy+y;
			   sumg++;
		  }
	}
	
	  Cofg_righteyex=sumx/sumg;
	  Cofg_righteyey=sumy/sumg;
	
DrawCrossX(v_left+H_rreye+Cofg_righteyex,(v_top+v_bottom)/2+R_beye+Cofg_righteyey);
///////////////////////nose////////////////////////////////////////////
	   sumx=0;
	   sumy=0;
	   sumg=0;
     for(i=B_NoseMiddleLine,y=1;i<=T_NoseMiddleLine;i++,y++)
	    for(j=H_rnose,x=1;j<=H_lnose;j++,x++)
          if(WhiteBlack[i][j]==0)
		  {
               sumx=sumx+x; 
			   sumy=sumy+y;
			   sumg++;
		  }
       Cofg_nosex=sumx/sumg;
       Cofg_nosey=sumy/sumg;
DrawCrossX(v_left+H_rnose+Cofg_nosex,v_bottom+B_NoseMiddleLine+Cofg_nosey);
///////////////////////mouth////////////////////////////////////////////
       sumx=0;
	   sumy=0;
	   sumg=0;
     for(i=B_MouthMiddleLine,y=1;i<=T_MouthMiddleLine;i++,y++)
	    for(j=H_rMouth,x=1;j<=H_lMouth;j++,x++)
          if(WhiteBlack[i][j]==0)
		  {
               sumx=sumx+x; 
			   sumy=sumy+y;
			   sumg++;
		  }
       Cofg_mouthx=sumx/sumg;
	   Cofg_mouthy=sumy/sumg;


///////////////////////////////////////////////////////////////////////////////////////////

 
}
//////////////////////////get eye parameters/////////////////////////////////////
void CFaceDetectView::GetEyesParameter()
{
  double TwoEyeAngle;
  double Toweye_nose;
  double Toweye_mouth;
  double Toweye_face;
  int X;
  int Y;
  ///////////////////////////////////angles of two eyes///////////////////////////////
    if(Cofg_lefteyex>Cofg_righteyex)
		X=Cofg_lefteyex-Cofg_righteyex+H_lreye-H_rreye;
	else
		X=Cofg_righteyex-Cofg_lefteyex+H_lreye-H_rreye;
	 if(Cofg_lefteyey>Cofg_righteyey)
		 Y=Cofg_lefteyey-Cofg_righteyey+abs(L_beye-R_beye);
	 else
		 Y=Cofg_righteyey-Cofg_lefteyey+abs(L_beye-R_beye);
	 TwoEyeAngle=atan(double(Y)/X);
   ///////////////////////////////////angle of eye and nose//////////////////////////////
    int T_line;
	int L_line ;
	int R_line;

T_line=X*X+Y*Y;
	R_line=((v_top-v_bottom)/2+R_beye+Cofg_righteyey-Cofg_nosey-B_NoseMiddleLine)*
           ((v_top-v_bottom)/2+R_beye+Cofg_righteyey-Cofg_nosey-B_NoseMiddleLine)+
		    (H_rnose+Cofg_nosex-H_rreye-Cofg_righteyex)*(H_rnose+Cofg_nosex-H_rreye-Cofg_righteyex);
    L_line=((v_top-v_bottom)/2+L_beye+Cofg_lefteyey-Cofg_nosey-B_NoseMiddleLine)*
            ((v_top-v_bottom)/2+L_beye+Cofg_lefteyey-Cofg_nosey-B_NoseMiddleLine)+
            (H_rnose+Cofg_nosex-H_lreye-Cofg_righteyex)*(H_rnose+Cofg_nosex-H_lreye-Cofg_righteyex);
    Toweye_nose  =	(T_line-R_line-L_line)/(-2.0*sqrt(R_line)*sqrt(L_line));
	
///////////////////////////////////////angle -- mouth and nose////////////////////////////////            
T_line=X*X+Y*Y;
	R_line=((v_top-v_bottom)/2+R_beye+Cofg_righteyey-Cofg_mouthy-B_MouthMiddleLine)*
           ((v_top-v_bottom)/2+R_beye+Cofg_righteyey-Cofg_mouthy-B_MouthMiddleLine)+
		    (H_rMouth+Cofg_mouthx-H_rreye-Cofg_righteyex)*(H_rMouth+Cofg_mouthx-H_rreye-Cofg_righteyex);

    L_line=((v_top-v_bottom)/2+L_beye+Cofg_lefteyey-Cofg_mouthy-B_MouthMiddleLine)*
            ((v_top-v_bottom)/2+L_beye+Cofg_lefteyey-Cofg_mouthy-B_MouthMiddleLine)+
            (H_rMouth+Cofg_mouthx-H_lreye-Cofg_righteyex)*(H_rMouth+Cofg_mouthx-H_lreye-Cofg_righteyex);
     Toweye_mouth=	(T_line-R_line-L_line)/(-2.0*sqrt(R_line)*sqrt(L_line));
	
//////////////////////////////////////////////////////////////
        Toweye_face=double(X)/(v_left-v_right);
//////////////////////////////////////////////////////////////


}

///////////////////////////get face parameter/////////////////////////////////////
void CFaceDetectView::GetPartParameter()
{
  Zx=0.0;
  Zy=0.0;
  
  M10=GetM(1,0);
  M00=GetM(0,0);
  M01=GetM(0,1);
  Zx=M10/M00;
  Zy=M01/M00;
  
  
  M1=Getm(2,0)+Getm(0,2);
  
  M2=(Getm(2,0)-Getm(0,2))*(Getm(2,0)-Getm(0,2))+4*(Getm(1,1)*Getm(1,1));
  
  M3=(Getm(3,0)-Getm(1,2))*(Getm(3,0)-Getm(1,2))+(3*Getm(2,1)+Getm(0,3))*(3*Getm(2,1)+Getm(0,3));
  
  M4=(Getm(3,0)+Getm(1,2))*(Getm(3,0)+Getm(1,2))+(Getm(2,1)+Getm(0,3))*(Getm(2,1)+Getm(0,3));
  
  M5=(Getm(3,0)-3*Getm(1,2))*(Getm(3,0)+Getm(1,2))*((Getm(3,0)+Getm(1,2))*(Getm(3,0)+Getm(1,2))-3*(Getm(2,1)+Getm(0,3))*(Getm(2,1)+Getm(0,3)))+
     (3*Getm(2,1)-Getm(0,3))*(Getm(2,1)+Getm(0,3))*(3*(Getm(3,0)+Getm(1,2))*(Getm(3,0)+Getm(1,2))-(Getm(2,1)+Getm(0,3))*(Getm(2,1)+Getm(0,3)));
  
  M6=(Getm(2,0)-Getm(0,2))*((Getm(3,0)+Getm(1,2))*(Getm(3,0)+Getm(1,2))-(Getm(2,1)+Getm(0,3))*(Getm(2,1)+Getm(0,3)))+4*Getm(1,1)*(Getm(3,0)+Getm(1,2))*(Getm(2,1)+Getm(0,3));
 
  M7=(3*Getm(1,2)-Getm(3,0))*(Getm(3,0)+Getm(1,2))*((Getm(3,0)+Getm(1,2))*(Getm(3,0)+Getm(1,2))-3*(Getm(2,1)+Getm(0,3))*(Getm(2,1)+Getm(0,3)))+
      (3*Getm(2,1)-Getm(0,3))*(Getm(2,1)+Getm(0,3))*(2*(Getm(0,3)+Getm(1,2))*(Getm(0,3)+Getm(1,2)));

  Eleye=(Getmleye(2,0)+Getmleye(0,2)+sqrt((Getmleye(2,0)+Getmleye(0,2))*(Getmleye(2,0)+Getmleye(0,2))-4*Getmleye(0,2)*Getmleye(2,0)+4*Getmleye(1,1)*Getmleye(1,1)))/
	  (Getmleye(2,0)+Getmleye(0,2)-sqrt((Getmleye(2,0)+Getmleye(0,2))*(Getmleye(2,0)+Getmleye(0,2))-4*Getmleye(0,2)*Getmleye(2,0)+4*Getmleye(1,1)*Getmleye(1,1)));

  Ereye=(Getmreye(2,0)+Getmreye(0,2)+sqrt((Getmreye(2,0)+Getmreye(0,2))*(Getmreye(2,0)+Getmreye(0,2))-4*Getmreye(0,2)*Getmreye(2,0)+4*Getmreye(1,1)*Getmreye(1,1)))/
	  (Getmreye(2,0)+Getmreye(0,2)-sqrt((Getmreye(2,0)+Getmreye(0,2))*(Getmreye(2,0)+Getmreye(0,2))-4*Getmreye(0,2)*Getmreye(2,0)+4*Getmreye(1,1)*Getmreye(1,1)));

}

double CFaceDetectView::GetM(int n,int m)
{
	double GetCM=0;

	for(int i=0;i<v_top-v_bottom;i++)
		for(int j=0;j<v_right-v_left;j++)
		{  
          double Getx=0.0;
		  Getx=pow(i,n);
          double Gety=0.0;
		  Gety=pow(j,m);
		  int fij;
		  if(WhiteBlack[i][j]==0)
			  fij=1;
		  else 
			  fij=0;
          GetCM=GetCM+fij*Getx*Gety;
		}
return GetCM;
}

double CFaceDetectView::Getm(int n,int m)
{
	double GetCm=0;
	int flat=0;
   	for(int i=0;i<v_top-v_bottom;i++)
		for(int j=0;j<v_right-v_left;j++)
		{  
          double Getx=0.0;
		  Getx=pow(i-Zx,-n);
          double Gety=0.0;
		  Gety=pow(j-Zy,-m);
		  int fij;
		  if(WhiteBlack[i][j]==0)
			  fij=1;
		  else 
			  fij=0;
		  GetCm=GetCm+fij*Getx*Gety;
		}
	double m00=1.0;
	if((n+m)>1&&flat==0)
	{
         m00=pow(Getm(0,0),double (m+n)/2);
		 flat=1;
	}
     GetCm=GetCm/m00;
		return GetCm;
}

double CFaceDetectView::Getmleye(int n,int m)
{
 double GetCmleye=0;
   	for(int i=(v_top-v_bottom)/2+L_beye,y=1;i<=(v_top-v_bottom)/2+L_teye;i++,y++)
		for(int j=H_lreye,x=1;j<=H_lleye;j++,x++)
		{  
          double Getx=0.0;
		  Getx=pow(i-Zx,-n);
          double Gety=0.0;
		  Gety=pow(j-Zy,-m);
		  int fij;
		  if(WhiteBlack[i][j]==0)
			  fij=1;
		  else 
			  fij=0;
		  GetCmleye=GetCmleye+fij*Getx*Gety;
		}
	return GetCmleye;

}

double CFaceDetectView::Getmreye(int n,int m)
{
   double GetCmreye=0;
   	for(int i=(v_top-v_bottom)/2+R_beye,y=1;i<(v_top-v_bottom)/2+R_teye;i++,y++)  
		for(int j=H_rreye,x=1;j<=H_rleye;j++,x++)
		{  
          double Getx=0.0;
		  Getx=pow(i-Zx,-n);
          double Gety=0.0;
		  Gety=pow(j-Zy,-m);
		  int fij;
		  if(WhiteBlack[i][j]==0)
			  fij=1;
		  else 
			  fij=0;
		  GetCmreye=GetCmreye+fij*Getx*Gety;
		}
      return GetCmreye;
}


void CFaceDetectView::OnPROSSINGdetect() 
{
	// TODO: Add your command handler code here
    	UpdateData(TRUE);
	     CString SQLstr;
		 double temp=0.0;
		 int Count=100;
///////////////////////////////////////////////////////////////////
    SQLstr = "SELECT username,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,Picture,Sex,Age,Birthday,Teleph,Address FROM CParameter";
		
    theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	 Count=theApp.m_pADOSet->GetRecordCount();
	  CFaceDetectDoc *doc=new CFaceDetectDoc();
	 CString name="liminyue2";
	 int nResponse=0;
     if(Count==0)
	 {
	  message *dlgname=new message(); 
     int GN=dlgname->DoModal();
	  
       if(GN==IDOK)
	   {
	     name=dlgname->m_Name;
	   
	     ADDFace(name);

	   }
	 }

_variant_t sName;
_variant_t sE;
_variant_t aG;
_variant_t bI;
_variant_t tE;
_variant_t aD;
_variant_t pI;

_variant_t Y1;
_variant_t Y2;
_variant_t Y3;
_variant_t Y4;
_variant_t Y5;
_variant_t Y6;
_variant_t Y7;
_variant_t Y8;
_variant_t Y9;
_variant_t Y10;
_variant_t Y11;

if(Count>0)
{
	   
	     theApp.m_pADOSet->MoveFirst();
      _variant_t UnameY=theApp.m_pADOSet->GetCollect("username");
	       sName=UnameY;

      Y1=theApp.m_pADOSet->GetCollect("X1");
      Y2=theApp.m_pADOSet->GetCollect("X2");
      Y3=theApp.m_pADOSet->GetCollect("X3");
      Y4=theApp.m_pADOSet->GetCollect("X4");
      Y5=theApp.m_pADOSet->GetCollect("X5");
      Y6=theApp.m_pADOSet->GetCollect("X6");
      Y7=theApp.m_pADOSet->GetCollect("X7");
      Y8=theApp.m_pADOSet->GetCollect("X8");
      Y9=theApp.m_pADOSet->GetCollect("X9");
      Y10=theApp.m_pADOSet->GetCollect("X10");
	  Y11=theApp.m_pADOSet->GetCollect("X11");	
	               pI=theApp.m_pADOSet->GetCollect("Picture");
	              sE=theApp.m_pADOSet->GetCollect("Sex");
				  aG=theApp.m_pADOSet->GetCollect("Age");
				  bI=theApp.m_pADOSet->GetCollect("Birthday");
				  tE=theApp.m_pADOSet->GetCollect("Teleph");
				  aD=theApp.m_pADOSet->GetCollect("Address");
	     
				  theApp.m_pADOSet->MoveNext();
  
  for(int i=0;i<Count-1;i=i+1)
  {
	  
	  
      _variant_t UnameZ=theApp.m_pADOSet->GetCollect("username");
      _variant_t Z1=theApp.m_pADOSet->GetCollect("X1");
      _variant_t Z2=theApp.m_pADOSet->GetCollect("X2");
      _variant_t Z3=theApp.m_pADOSet->GetCollect("X3");
      _variant_t Z4=theApp.m_pADOSet->GetCollect("X4");
      _variant_t Z5=theApp.m_pADOSet->GetCollect("X5");
      _variant_t Z6=theApp.m_pADOSet->GetCollect("X6");
      _variant_t Z7=theApp.m_pADOSet->GetCollect("X7");
      _variant_t Z8=theApp.m_pADOSet->GetCollect("X8");
      _variant_t Z9=theApp.m_pADOSet->GetCollect("X9");
      _variant_t Z10=theApp.m_pADOSet->GetCollect("X10");
	  _variant_t Z11=theApp.m_pADOSet->GetCollect("X11");
                  
	  
	  int sum1=0;
	  int sum2=0;

	  if(fabs(double(Y1)-x1)>fabs(double(Z1)-x1))
          sum2++;
	  else
		  sum1++;

	  if(fabs(double(Y2)-x2)>fabs(double(Z2)-x2))
          sum2++;
	  else
		  sum1++;
	  
	  if(fabs(double(Y3)-x3)>fabs(double(Z3)-x3))
          sum2++;
	  else
		  sum1++;

	  if(fabs(double(Y4)-x4)>fabs(double(Z4)-x4))
          sum2++;
	  else
		  sum1++;

	  if(fabs(double(Y5)-x5)>fabs(double(Z5)-x5))
          sum2++;
	  else
		  sum1++;

	  if(fabs(double(Y6)-x6)>fabs(double(Z6)-x6))
          sum2++;
	  else
		  sum1++;

	  if(fabs(double(Y7)-x7)>fabs(double(Z7)-x7))
          sum2++;
	  else
		  sum1++;
	  
	  if(fabs(double(Y8)-x8)>fabs(double(Z8)-x8))
          sum2++;
	  else
		  sum1++;

	  if(fabs(double(Y9)-x9)>fabs(double(Z9)-x9))
          sum2++;
	  else
		  sum1++;

	  if(fabs(double(Y10)-x10)>fabs(double(Z10)-x10))
          sum2++;
	  else
		  sum1++;

	  if(fabs(double(Y11)-x11)>fabs(double(Z11)-x11))
          sum2++;
	  else
		  sum1++;

	  if(sum1<sum2 )
	  {  // sE=theApp.m_pADOSet->GetCollect("Sex");
		  sE=theApp.m_pADOSet->GetCollect("Sex");
		  aG=theApp.m_pADOSet->GetCollect("Age");
		  bI=theApp.m_pADOSet->GetCollect("Birthday");
		  tE=theApp.m_pADOSet->GetCollect("Teleph");
		  aD=theApp.m_pADOSet->GetCollect("Address");
		  pI=theApp.m_pADOSet->GetCollect("Picture");
		  UnameY=UnameZ;
		  sName=UnameY;
		  Y1=Z1;
		  Y2=Z2;
          Y2=Z2;
          Y3=Z3;
          Y4=Z4;
          Y5=Z5;
          Y6=Z6;
          Y7=Z7;
          Y8=Z8;
          Y9=Z9;
          Y10=Z10;
          Y11=Z11;
	  }
	theApp.m_pADOSet->MoveNext();
  }

}

double Dsum;

      CString a1=(char* )(_bstr_t)Y1;
	  double b1=atof(a1);
	  CString a2=(char* )(_bstr_t)x1;
	  double b2=atof(a2);
      double Dsum1=fabs(b1-b2);

	   a1=(char* )(_bstr_t)Y2;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x2;
	   b2=atof(a2);
      double Dsum2=fabs(b1-b2);
   
	   a1=(char* )(_bstr_t)Y3;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x3;
	   b2=atof(a2);
      double Dsum3=fabs(b1-b2);

       a1=(char* )(_bstr_t)Y4;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x4;
	   b2=atof(a2);
      double Dsum4=fabs(b1-b2);

	  a1=(char* )(_bstr_t)Y5;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x5;
	   b2=atof(a1);
      double Dsum5=fabs(b1-b2);

      a1=(char* )(_bstr_t)Y6;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x6;
	   b2=atof(a2);
      double Dsum6=fabs(b1-b2);

      a1=(char* )(_bstr_t)Y7;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x7;
	   b2=atof(a2);
      double Dsum7=fabs(b1-b2);

       a1=(char* )(_bstr_t)Y8;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x8;
	   b2=atof(a2);
      double Dsum8=fabs(b1-b2);

	  a1=(char* )(_bstr_t)Y9;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x9;
	   b2=atof(a2);
      double Dsum9=fabs(b1-b2);

	  a1=(char* )(_bstr_t)Y10;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x10;
	   b2=atof(a2);
      double Dsum10=fabs(b1-b2);

	  a1=(char* )(_bstr_t)Y11;
	   b1=atof(a1);
	   a2=(char* )(_bstr_t)x11;
	   b2=atof(a2);
      double Dsum11=fabs(b1-b2);

	  
      Dsum=Dsum1+Dsum2+Dsum3+Dsum4+Dsum5+Dsum6+Dsum7+Dsum8+Dsum9+Dsum10+Dsum11;
     shujuyanchi *yanchi=new shujuyanchi();
	 // yanchi->DoModal();
	 
    for(int i=0;i<15000;i++)
	{
		for(int j=0;j<50000;j++)
		{
			;
		}
	}
	  yanchi->DestroyWindow();

        CFaceDetectDoc * InsertPicture=new CFaceDetectDoc();
        CString strTemp=(char* )(_bstr_t)pI;
        InsertPicture->OnOpenDocument1(strTemp);
        ShowPMessage *SPM=new ShowPMessage();
          SPM->m_Name=(char* )(_bstr_t)sName;//MessageBox("OK!");
          SPM->m_Sex=(char* )(_bstr_t)sE;
          SPM->m_Age=(char* )(_bstr_t)aG;
		  SPM->m_Birthday=(char* )(_bstr_t)bI;
		  SPM->m_Teleph=(char* )(_bstr_t)tE;
		  SPM->m_Address=(char* )(_bstr_t)aD;
		  SPM->DoModal();
		   //MessageBox("OK!");

             


}
//////////////////////////////////////////////////////////////////
double CFaceDetectView::AverageDeviation(double NewData,double OldData)
{   double Sx;
	Sx=sqrt(((NewData-OldData)*(NewData-OldData))/2);
	return Sx;
}
//////////////////////////////////// Draw Cross////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void  CFaceDetectView::DrawCrossX(int X,int Y)
{
	LPBYTE lpData;
	lpData = gDib.FindDIBBits(hDIB);
	WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
	int lOffset;

for(int j=X-4;j<X+4;j++)
{
	lOffset = gDib.PixelOffset(Y, j, gwBytesPerLine);
					*(lpData + lOffset) = 0;
			        *(lpData + lOffset+1) = 0;
			        *(lpData + lOffset+2) =255 ;
}

for(int i=Y-4;i<Y+4;i++)
{
	lOffset = gDib.PixelOffset(i, X, gwBytesPerLine);
					*(lpData + lOffset) = 0;
			        *(lpData + lOffset+1) = 255;
			        *(lpData + lOffset+2) =0 ;
}
Invalidate();

}


BOOL CFaceDetectView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
//	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

if(CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext)==FALSE)
	return false;
      
	  CRect rc(10+100,10+50,320+10+100,240+10+50);
	  m_VideoDisplay.Create("",WS_VISIBLE|WS_CHILD,rc,this,0);
      m_VideoDisplay.ShowWindow(SW_SHOW);
	   
	return TRUE;
}



void CFaceDetectView::OnIdVidio() 
{
	// TODO: Add your command handler code here
    
    
	if(flagP==false)
	{
    CRect Rect(10+100,10+50,320+10+100,240+10+50);
    CAPDRIVERCAPS Caps;

  //  m_VideoDisplay.GetWindowRect(Rect);
  //  ScreenToClient(Rect);
    m_VFWImageProc.Initialize();
    m_VFWImageProc.DriverGetCaps(&Caps);	
	m_VFWImageProc.EnablePreviewVideo(*this, Rect.TopLeft().x,Rect.TopLeft().y,320,240,1);



	flagP=true;
	}
}

void CFaceDetectView::OnVidioCannel() 
{
	// TODO: Add your command handler code here
	m_VFWImageProc.Destroy();flagP=false;
}
BOOL Capture(CVFWImageProcessor &ImageProc, LPCTSTR Filename)//***********************

{
   ULONG Length = 0;
   CFile File;
   BOOL Ret = FALSE;
   CHAR Ext[_MAX_EXT];

   _splitpath(Filename,NULL,NULL,NULL,Ext);

   if (stricmp(Ext,".avi") == 0)
   {
      Ret = ImageProc.CaptureAVI(Filename,4.0,10,10);
   }
   else if (stricmp(Ext,".bmp") == 0)
   {
      BITMAPINFO *Bitmap = NULL;
      BITMAPFILEHEADER bfh;

      ImageProc.CaptureDIB(&Bitmap,0,&Length);

      if (Bitmap)
      {
         File.Open(Filename,CFile::modeCreate |
                                    CFile::modeWrite |
                                    CFile::shareDenyNone |
                                    CFile::typeBinary);

         bfh.bfType = 0x4d42;    // 0x42 = "B" 0x4d = "M"
         bfh.bfSize = (DWORD) Length + sizeof(BITMAPFILEHEADER);
         bfh.bfOffBits = (DWORD)   sizeof(BITMAPFILEHEADER) +
                                   sizeof(BITMAPINFOHEADER) +
                                    Bitmap->bmiHeader.biClrUsed * sizeof (RGBQUAD);
         bfh.bfReserved1 = 0;
         bfh.bfReserved2 = 0;

         File.Write(&bfh,sizeof(bfh));
         File.Write(Bitmap,Length);
         File.Close();

         Ret = TRUE;

         delete Bitmap;
      }
   }

   return Ret;
}

void CFaceDetectView::OnIdProssing()
{
   IdProssing();
 //  OnPROSSINGdetect();
	 
	
}
void CFaceDetectView::IdProssing()
{
// TODO: Add your command handler code here
   CString Filter;
   CString Filename;
   CRect Rect;

 //  Filter = "Bitmap Files (*.bmp)|*.bmp|AVI Files (*.avi)|*.avi||";

 //  CFileDialog FileDlg(FALSE, "BMP", NULL,
                      // OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                      // Filter,
                      // this);

  // if (FileDlg.DoModal() == IDOK)
  // {
      RedrawWindow();

      //Filename = FileDlg.GetPathName();
	  

      Filename="g:"+pname+".bmp";
      Capture(m_VFWImageProc, Filename);

      m_VideoDisplay.GetWindowRect(Rect);
      ScreenToClient(Rect);

      m_VFWImageProc.EnablePreviewVideo(*this, Rect.TopLeft().x,Rect.TopLeft().y);
	  //m_VFWImageProc.Destroy();
	  flagP=false;
      CFaceDetectDoc * InsertPicture=new CFaceDetectDoc();
	  InsertPicture->OnOpenDocument(Filename);
     // InsertPicture->READYGetFaceOutLline1();
/*
      ReadyLightingconpensate2();

	  ReadyScale3();

	  READYTemplate4();
 
	  ReadyZft5();

	  READYContrastEnhance6();

	  ReadyWhiteblack7();

 bool jum=READYFixedPosition8();
          if(!jum)
			  return ;
	  GetNewParameter();
	  */
	  
     
	  
	  Invalidate();
}


/*****************************************************
* 
*   函数名称：
*      Template：
*
*    参数：
*	   HDIB    hDIB         －图像的句柄
*      double  *tem         －指向模板的指针
*      int  tem_w           －模板的宽度
*      int  tem_h           －模板的高度
*      double xishu         －模板的系数
*         
*    功能：
*	   对图像进行模板操作
*
*    说明：
*	   为处理方便起见，模板的宽度和高度都应为奇数
*******************************************************/
void CFaceDetectView::Template(double * tem ,int tem_w,int tem_h,double xishu)
{

    //统计中间值
    double sum;

    //循环变量
    int i,j,m,n;

	int w, h;

	//获取图像的宽度
	w = (v_right-v_left)+1;
	
	//获取图像的高度
	h = (v_top-v_bottom)+1;	
	HeightTemplate= new int*[v_top-v_bottom+1];
	int k;
	for( k=0;k<v_top-v_bottom+1;k++)
     HeightTemplate[k]=new int [v_right-v_left+1];
	//对图像进行扫描
   
	//行 
    for(i=0;i<h;i++)
    {  
		//列
	   for(j=0;j<w;j++)
	   {   

		   //为统计变量赋初始值
	       sum=0;

         //对于图像的4个边框的象素保持原灰度不变
	     if( j<((tem_w-1)/2) || j>(w-(tem_w+1)/2) || i<((tem_h-1)/2) || i>(h-(tem_h+1)/2) )
	      HeightTemplate[i][j]=Gray[i][j];
		 
         //对于其他的象素进行模板操作
		 else 
         { 

          //将点（i,j）点作为模板的中心
          for(m=i-((tem_h-1)/2);m<=i+((tem_h-1)/2);m++)
          {
		     for(n=j-((tem_w-1)/2);n<=j+((tem_w-1)/2);n++)
		    
             //将以点（i，j）为中心，与模板大小相同的范围内的象素与模板对用位置的系数
			 //进行相乘并线形叠加
		     sum+=Gray[m][n]* tem[(m-i+((tem_h-1)/2))*tem_w+n-j+((tem_w-1)/2)];
		  
		  }
          
		  //将结果乘上总的模板系数
          sum=(int)sum*xishu;

		  //计算绝对值
		  sum = fabs(sum);

		  //如果小于0，强制赋值为0
          if(sum<0)     
          sum=0;

		  //如果大于255，强制赋值为255
          if(sum>255)
		  sum=255;

		  //将计算的结果放到新的位图的相应位置
	      HeightTemplate[i][j]=sum;
		 }
	   }
	} 
	///////////////////////////////////////////////////////////////////////
	int k1;
	LPBYTE lpData;
	long lOffset;
	lpData = gDib.FindDIBBits(hDIB);
    WORD gwBytesPerLine = gDib.BytePerLine(hDIB);
   for( i=v_bottom,k=0; i<=v_top; i++,k++)
		for(j=v_left,k1=0; j<=v_right; j++,k1++)
		{
           lOffset = gDib.PixelOffset(i, j, gwBytesPerLine);
       
		   *(lpData + lOffset)=HeightTemplate[k][k1];
		   *(lpData + lOffset+1)=HeightTemplate[k][k1];
		   *(lpData + lOffset+2)=HeightTemplate[k][k1];
		   
		  
		}

		 

}

void CFaceDetectView::OnGetName() 
{	::AfxMessageBox("Face too small!");
	// TODO: Add your control notification handler code here
	GetName *Name=new GetName();
	CString name=Name->m_Name;
	ADDFace(name);
	

}
void CFaceDetectView::ADDFace(CString name)
{       CString SQLstr;
	   CFaceDetectDoc *doc=new CFaceDetectDoc();
	   CString s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11;
	   s1.Format("%f",x1);
	   s2.Format("%f",x2);
	   s3.Format("%f",x3);
	   s4.Format("%f",x4);
	   s5.Format("%f",x5);
	   s6.Format("%f",x6);
	   s7.Format("%f",x7);
	   s8.Format("%f",x8);
	   s9.Format("%f",x9);
	   s10.Format("%f",x10);
	   s11.Format("%f",x11);
	    //LPCTSTR path=doc->path;
	   CString path="g:"+pname+".bmp";
	   CString cpath="g:\\"+pname+".bmp";
	   SQLstr ="insert into CParameter (username,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,Picture) values('"+name+"','"+s1+"','"+s2+"','"+s3+"','"+s4+"','"+s5+"','"+s6+"','"+s7+"','"+s8+"','"+s9+"','"+s10+"','"+s11+"','"+path+"')";
       theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	   
		
}

void CFaceDetectView::OnProssingStudy() 
{
	// TODO: Add your command handler code here
	 int num;
	GetStudyNum * St=new GetStudyNum();
	int op=St->DoModal();
	
	if(op==IDOK)
		num=St->m_Num;
	else
		return ;
	if(num==0)
		return ;

double *x_1;
 x_1=new double [num];
 double  *x_2;
 x_2=new double [num];
 double  *x_3;
 x_3=new double [num];
 double  *x_4;
 x_4=new double [num];
 double  *x_5;
 x_5=new double [num];
 double  *x_6;
 x_6=new double [num];
 double  *x_7;
 x_7=new double [num];
 double  *x_8;
 x_8=new double [num];
 double  *x_9;
 x_9=new double [num];
 double  *x_10;
 x_10=new double [num];
 double  *x_11;
 x_11=new double [num];
 
   CString M_Name;
   CString M_Sex;
   int  M_Age;
   CString M_Birthday;
   CString M_Tel;
   CString M_Add;
  message *dlgname=new message(); 
     int GN=dlgname->DoModal();
	  /////弹出对话框插入///////////
       if(GN==IDOK)
	   {
	    M_Name=dlgname->m_Name;
		M_Sex=dlgname->m_Sex;
		M_Age=dlgname->m_Age;
		M_Birthday=dlgname->m_Birthday;
		M_Tel=dlgname->m_Tle;
		M_Add=dlgname->m_Addresss;
	   }
	   else
		   return ;
   pname=M_Name;
  Tishi *TS=new Tishi();	

 
for(int i=0;i<num;i++)
{
     
     
     
     TS->m_number=i+1;
	 op=TS->DoModal();
	 IdProssing();
     x_1[i]=x1;
	 x_2[i]=x2;
	 x_3[i]=x3;
	 x_4[i]=x4;
	 x_5[i]=x5;
	 x_6[i]=x6;
	 x_7[i]=x7;
	 x_8[i]=x8;
	 x_9[i]=x9;
	 x_10[i]=x10;
	 x_11[i]=x11;
	
	 	

}
double sum_1=0;
double sum_2=0;
double sum_3=0;
double sum_4=0;
double sum_5=0;
double sum_6=0;
double sum_7=0;
double sum_8=0;
double sum_9=0;
double sum_10=0;
double sum_11=0;
for(int j=0;j<i;j++)
{
	sum_1=sum_1+x_1[j];
    sum_2=sum_2+x_2[j];
    sum_3=sum_3+x_3[j];
    sum_4=sum_4+x_4[j];
    sum_5=sum_5+x_5[j];
    sum_6=sum_6+x_6[j];
    sum_7=sum_7+x_7[j];
    sum_8=sum_8+x_8[j];
    sum_9=sum_9+x_9[j];
    sum_10=sum_10+x_10[j];
    sum_11=sum_11+x_11[j];



}

sum_1=sum_1/i;
sum_2=sum_2/i;
sum_3=sum_3/i;
sum_4=sum_4/i;
sum_5=sum_5/i;
sum_6=sum_6/i;
sum_7=sum_7/i;
sum_8=sum_8/i;
sum_9=sum_9/i;
sum_10=sum_10/i;
sum_11=sum_11/i;


       CString SQLstr;
	  
	   CString s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12;
	   s1.Format("%f",sum_1);
	   s2.Format("%f",sum_2);
	   s3.Format("%f",sum_3);
	   s4.Format("%f",sum_4);
	   s5.Format("%f",sum_5);
	   s6.Format("%f",sum_6);
	   s7.Format("%f",sum_7);
	   s8.Format("%f",sum_8);
	   s9.Format("%f",sum_9);
	   s10.Format("%f",sum_10);
	   s11.Format("%f",sum_11);
	   s12.Format("%f", M_Age);
	    //LPCTSTR path=doc->path;
	    CString path="d:"+pname+".bmp";
	   SQLstr ="insert into CParameter (username,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,Picture,Sex,Age,Birthday,Teleph,Address) values('"+M_Name+"','"+s1+"','"+s2+"','"+s3+"','"+s4+"','"+s5+"','"+s6+"','"+s7+"','"+s8+"','"+s9+"','"+s10+"','"+s11+"','"+path+"','"+M_Sex+"','"+s12+"','"+M_Birthday+"','"+M_Tel+"','"+M_Add+"')";
       theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
}

void CFaceDetectView::OnDetectface() 
{
	// TODO: Add your command handler code here
	CFaceDetectDoc * InsertPicture=new CFaceDetectDoc();

	 if(!hDIB)
	 {::AfxMessageBox("请确定是否有需要识别的图像!");return ;}

      InsertPicture->READYGetFaceOutLline1();
     
	  if(!FaceTwo){
      ReadyLightingconpensate2();

	  ReadyScale3();

	  READYTemplate4();

	  ReadyZft5();

	  READYContrastEnhance6();

	  ReadyWhiteblack7();
	  }
      
	  if(!FaceFix)
	  {
	  bool jum=READYFixedPosition8();
          if(!jum)
			  return ;
	  }
	  if(!FacePara)
	  {
	  GetNewParameter();
	  }
   
	  OnPROSSINGdetect();
}

void CFaceDetectView::OnStudyMenuitem32798() 
{
	// TODO: Add your command handler code here
	  
   CString M_Name;
   CString M_Sex;
   int  M_Age;
   CString M_Birthday;
   CString M_Tel;
   CString M_Add;


   message *dlgname=new message(); 
     int GN=dlgname->DoModal();
	  /////弹出对话框插入///////////
       if(GN==IDOK)
	   {
	    M_Name=dlgname->m_Name;
		M_Sex=dlgname->m_Sex;
		M_Age=dlgname->m_Age;
		M_Birthday=dlgname->m_Birthday;
		M_Tel=dlgname->m_Tle;
		M_Add=dlgname->m_Addresss;
	   }
	   else
		   return ;
   pname=M_Name;
	 CFaceDetectDoc * InsertPicture=new CFaceDetectDoc();
	  /*

	  InsertPicture->READYGetFaceOutLline1();

      ReadyLightingconpensate2();

	  ReadyScale3();

	  READYTemplate4();

	  ReadyZft5();

	  READYContrastEnhance6();

	  ReadyWhiteblack7();

	  READYFixedPosition8();
	  GetNewParameter();
	  */

	  CString SQLstr;
	  
	  CString s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12;
	   s1.Format("%f",x1);
	   s2.Format("%f",x2);
	   s3.Format("%f",x3);
	   s4.Format("%f",x4);
	   s5.Format("%f",x5);
	   s6.Format("%f",x6);
	   s7.Format("%f",x7);
	   s8.Format("%f",x8);
	   s9.Format("%f",x9);
	   s10.Format("%f",x10);
	   s11.Format("%f",x11);
	   s12.Format("%d", M_Age);

//	   GetModuleFileName( NULL, cpath, 1000 );
	//   getcwd(cpath,100);
	   
       
//	   strncpy(cpath,(LPCTSTR)path,sizeof(cpath));
	  // CString path=doc->path;
	   
       

	   CString path="g:"+pname+".bmp";
	   CString cpath="g:\\"+pname+".bmp";
	//   copyfile1("G:\FaceModel\040220401.bmp",cpath);

	   ::AfxMessageBox(path);
	   SQLstr ="insert into CParameter (username,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,Picture,Sex,Age,Birthday,Teleph,Address) values('"+M_Name+"','"+s1+"','"+s2+"','"+s3+"','"+s4+"','"+s5+"','"+s6+"','"+s7+"','"+s8+"','"+s9+"','"+s10+"','"+s11+"','"+path+"','"+M_Sex+"','"+s12+"','"+M_Birthday+"','"+M_Tel+"','"+M_Add+"')";
       theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	   
	   
}

int CFaceDetectView::copyfile(const char* source, const char* dest)
{

FILE *f,*y;
char ch;
f = fopen(source,"r");
y = fopen(dest,"w");
if(f==NULL) return 1;
if(y==NULL) return 2;
while((ch=fgetc(f))!=EOF)
{
if(fputc(ch,y)==EOF) return 3;
}
fputc(EOF,y);
fclose(f);
fclose(y);
return 0;
}

int CFaceDetectView::copyfile1(const char* source, const char* dest)
{
char ch;
ifstream from(source);
ofstream to(dest);
if(!from) return 1;
if(!to) return 2;
while(from.get(ch))
{
if(!to.put(ch)) return 3;
}
return 0;
}

void CFaceDetectView::OnDatabaseFind() 
{
	// TODO: Add your command handler code here
    FINDMESSAGE *Find=new FINDMESSAGE();
	_variant_t sE;
    _variant_t aG;
    _variant_t bI;
    _variant_t tE;
    _variant_t aD;
	_variant_t UnameY;
	int ok=Find->DoModal();
	if(ok==IDOK)
	{   
		CString SQLstr = "SELECT username,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,Picture,Sex,Age,Birthday,Teleph,Address FROM CParameter";
		theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	    int Count=theApp.m_pADOSet->GetRecordCount();
        theApp.m_pADOSet->MoveFirst();

		for(int i=0;i<Count;i++)
		{
		UnameY=theApp.m_pADOSet->GetCollect("username");
		sE=theApp.m_pADOSet->GetCollect("Sex");
		aG=theApp.m_pADOSet->GetCollect("Age");
		bI=theApp.m_pADOSet->GetCollect("Birthday");
		tE=theApp.m_pADOSet->GetCollect("Teleph");
		aD=theApp.m_pADOSet->GetCollect("Address");
		CString a1=(char* )(_bstr_t)UnameY;
	   
		if(a1==Find->m_Name)
		{
         
          ShowPMessage *SPM=new ShowPMessage();
          SPM->m_Name=(char* )(_bstr_t)UnameY;//MessageBox("OK!");
          SPM->m_Sex=(char* )(_bstr_t)sE;
          SPM->m_Age=(char* )(_bstr_t)aG;
		  SPM->m_Birthday=(char* )(_bstr_t)bI;
		  SPM->m_Teleph=(char* )(_bstr_t)tE;
		  SPM->m_Address=(char* )(_bstr_t)aD;
		  SPM->DoModal();
          return ;
		}	
		theApp.m_pADOSet->MoveNext();
		}
        Meg *Ts=new Meg();
		int ok1=Ts->DoModal();
		return ;
	

	}
	
}


void CFaceDetectView::OnDATABASEDelete() 
{
	// TODO: Add your command handler code here
    DelectMessage *opn=new DelectMessage();
	int op=opn->DoModal();
	CString a1;
	CString SQLstr = "SELECT username,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,Picture,Sex,Age,Birthday,Teleph,Address FROM CParameter";
		theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	    int Count=theApp.m_pADOSet->GetRecordCount();
        theApp.m_pADOSet->MoveFirst();
  if(op==IDOK)
	{
		for(int i=0;i<Count;i++)
		{
		 _variant_t UnameY=theApp.m_pADOSet->GetCollect("username");
		 a1=(char* )(_bstr_t)UnameY;
	   
		if(a1==opn->m_Name)
		{
         ::AfxMessageBox("删除成功！");
		 CString m_name=opn->m_Name;
         CString SQLstr = "DELETE FROM CParameter WHERE (username)=('"+m_name+"')";
         theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
		 break;
		}
	      theApp.m_pADOSet->MoveNext();
		}
	   if(a1!=opn->m_Name)
	    ::AfxMessageBox("删除不成功！");
     
	}
}

void CFaceDetectView::OnMenuitem32799() 
{
	// TODO: Add your command handler code here
	XiuGai *XG=new XiuGai();
	CString s1;
	if(XG->DoModal()==IDOK)
	{
	if(XG->flagN==1)
	{
	CString m_name=XG->m_Xname;
	CString name = XG->m_Name;
    CString SQLstr = "UPDATE CParameter SET username=('"+name+"') WHERE (username)=('"+m_name+"')";
    theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	XG->flagN=0;
	}
	if(XG->flagA==1)
	{
	CString m_name=XG->m_Xname;
	s1.Format("%d",XG->m_Age);
	CString name = s1;
    CString SQLstr = "UPDATE CParameter SET Age=('"+name+"') WHERE (username)=('"+m_name+"')";
    theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	XG->flagA=0;
	}
	if(XG->flagT==1)
	{
	CString m_name=XG->m_Xname;
	CString name = XG->m_Tel;
    CString SQLstr = "UPDATE CParameter SET Teleph=('"+name+"') WHERE (username)=('"+m_name+"')";
    theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	XG->flagT=0;
	}
	if(XG->flagB==1)
	{
	CString m_name=XG->m_Xname;
	CString name = XG->m_Birthday;
    CString SQLstr = "UPDATE CParameter SET Birthday=('"+name+"') WHERE (username)=('"+m_name+"')";
    theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	XG->flagB=0;
	}
	if(XG->flagAD==1)
	{
	CString m_name=XG->m_Xname;
	CString name = XG->m_Add;
    CString SQLstr = "UPDATE CParameter SET Address=('"+name+"') WHERE (username)=('"+m_name+"')";
    theApp.ADOExecute(theApp.m_pADOSet,SQLstr);
	XG->flagAD=0;
	}
	}
}
