// DIB.cpp: implementation of the DIB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DIB.h"
#include"math.h"
#include "LikelyHood.h"
#define WIDTHBYTES(bits)  ((bits+31)/32*4)
#define RECTWIDTH(x) (x->right-x->left)
#define RECTHEIGHT(x) (x->bottom-x->top)
#define THRESHOLDCONTRAST  40
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define PI 3.1415926
extern int locax,locay;
#define m_WIDTH 600
#define m_HEIGHT 600

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////
HDIB DIB::ReadDIBFile(HANDLE hFile)
{
	BITMAPFILEHEADER bmfHeader;
	DWORD dwBitsSize;
	HANDLE hDIB;
	HANDLE hDIBtmp;
	LPBITMAPINFOHEADER lpbi;
	DWORD dwRead;
    //�õ��ļ���С
	dwBitsSize = GetFileSize(hFile,NULL);
	hDIB =  GlobalAlloc(GMEM_MOVEABLE,(DWORD)(sizeof(BITMAPINFOHEADER)));

	if(!hDIB)
		return NULL;

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	if(!lpbi)
	{
		GlobalFree(hDIB);
		return NULL;
	}
	
	if(!ReadFile(hFile,(LPBYTE)&bmfHeader,sizeof(BITMAPFILEHEADER),&dwRead,NULL))
		goto ErrExit;
	if(sizeof(BITMAPFILEHEADER)!=dwRead)//��ȡ�ļ�����
		goto ErrExit;
	if(bmfHeader.bfType != 0x4d42)//�ļ����Ͳ�ƥ��
		goto ErrExit;
	if(!ReadFile(hFile,(LPBYTE)lpbi,sizeof(BITMAPINFOHEADER),&dwRead,NULL))
		goto ErrExit;
	if(sizeof(BITMAPINFOHEADER)!= dwRead)//��ȡ���ݳ���
		goto ErrExit;
	
	GlobalUnlock(hDIB);
	if(lpbi->biSizeImage==0)
		lpbi->biSizeImage = (this->BytePerLine(hDIB))*lpbi->biHeight;
	hDIBtmp = GlobalReAlloc(hDIB,lpbi->biSize+lpbi->biSizeImage,0);
	if(!hDIBtmp)
		goto ErrExitNoUnlock;
	else
		hDIB = hDIBtmp;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	//��������趨�ļ�ָ��
	if(bmfHeader.bfOffBits != 0L)
		SetFilePointer(hFile,bmfHeader.bfOffBits,NULL,FILE_BEGIN);
    //��ȡ�ļ���������ɫ����
	if(ReadFile(hFile,(LPBYTE)lpbi+lpbi->biSize,lpbi->biSizeImage,&dwRead,NULL))
			goto OKExit;
	
	ErrExit:
		GlobalUnlock(hDIB);
	
	ErrExitNoUnlock:
		GlobalFree(hDIB); //�ͷ��ڴ�
		return NULL;

	OKExit:
		GlobalUnlock(hDIB);
		return hDIB;
		
}


HDIB DIB::LoadDIB(LPCTSTR lpFileName)
{
	HANDLE hDIB;
	HANDLE hFile;
	//�����ļ����
	if((hFile = CreateFile(lpFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL))!= INVALID_HANDLE_VALUE)
	{  
		//��ȡ����
		hDIB = ReadDIBFile(hFile);
		//�ر��ļ����
		CloseHandle(hFile);
		return hDIB;
	}
	return NULL;
}

BOOL DIB::PaintDIBTrue(HDC hDC,LPRECT lpDCRect,HANDLE hDIB,LPRECT lpDIBRect ,DWORD dwRop)
{
	LPBYTE lpDIBHdr;
	LPBYTE lpDIBBits;
	BOOL bSuccess = FALSE;

	if(!hDIB)
		return FALSE;
	lpDIBHdr = (LPBYTE)GlobalLock(hDIB);
	lpDIBBits = lpDIBHdr + sizeof(BITMAPINFOHEADER);
	bSuccess = StretchDIBits(hDC,lpDCRect->left,
								 lpDCRect->top,
								 RECTWIDTH(lpDCRect),
								 RECTHEIGHT(lpDCRect),
								 lpDIBRect->left,
								 ((LPBITMAPINFOHEADER)lpDIBHdr)->biHeight-lpDIBRect->top-RECTHEIGHT(lpDIBRect),
								 RECTWIDTH(lpDIBRect),
								 RECTHEIGHT(lpDIBRect),
								 lpDIBBits,
								 (LPBITMAPINFO)lpDIBHdr,
								 DIB_RGB_COLORS,
								 SRCCOPY);
	GlobalUnlock(hDIB);
	return bSuccess;
}


BOOL DIB::PaintDIBTrue1(HDC hDC,LPRECT lpDCRect,HANDLE hDIB,LPRECT lpDIBRect ,DWORD dwRop)
{
	LPBYTE lpDIBHdr;
	LPBYTE lpDIBBits;
	BOOL bSuccess = FALSE;

	if(!hDIB)
		return FALSE;
	lpDIBHdr = (LPBYTE)GlobalLock(hDIB);
	lpDIBBits = lpDIBHdr + sizeof(BITMAPINFOHEADER);
	bSuccess = StretchDIBits(hDC,lpDCRect->left,
								 lpDCRect->top,
								 RECTWIDTH(lpDCRect),
								 RECTHEIGHT(lpDCRect),
								 lpDIBRect->left,
								 ((LPBITMAPINFOHEADER)lpDIBHdr)->biHeight-lpDIBRect->top-RECTHEIGHT(lpDIBRect),
								 RECTWIDTH(lpDIBRect),
								 RECTHEIGHT(lpDIBRect),
								 lpDIBBits,
								 (LPBITMAPINFO)lpDIBHdr,
								 DIB_RGB_COLORS,
								 SRCCOPY);
	GlobalUnlock(hDIB);
	return bSuccess;
}

WORD DIB::BytePerLine(HANDLE hDIB)
{	
	WORD i;
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	i = WIDTHBYTES((lpbi->biWidth)*24);
	GlobalUnlock(hDIB);
	return i;	
}


LPBYTE  DIB::FindDIBBits(HANDLE hDIB)
{
	LPBYTE lpDIB,lpDIBtmp;
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	lpDIBtmp = (LPBYTE)lpbi;
	lpDIB = lpDIBtmp + sizeof(BITMAPINFOHEADER);
	GlobalUnlock(hDIB);
	return lpDIB;
}

long DIB::PixelOffset(int i,int j,WORD wBytePerLine)
{
	long   Offset;
	Offset = i*wBytePerLine + j*3;
	return Offset;
}






DIB::DIB()
{	
	for(int i=0;i<ImgRange; i++)
		for (int j=0; j<ImgRange; j++)
			this->lab[i][j] = false;
		m_pDib=NULL;

}
DIB::~DIB()
{

}





BOOL DIB:: SaveDIB(HANDLE hDib, CFile& file)
{
	// Bitmap�ļ�ͷ
	BITMAPFILEHEADER bmfHdr;
	
	// ָ��BITMAPINFOHEADER��ָ��
	LPBITMAPINFOHEADER lpBI;
	
	// DIB��С
	DWORD dwDIBSize =0;

	if (hDib == NULL)
	{
		// ���DIBΪ�գ�����FALSE
		return FALSE;
	}

	// ��ȡBITMAPINFO�ṹ��������
	lpBI = (LPBITMAPINFOHEADER) ::GlobalLock((HGLOBAL) hDib);
	
	if (lpBI == NULL)
	{
		// Ϊ�գ�����FALSE
		return FALSE;
	}
	
	// �ж��Ƿ���WIN3.0 DIB
//	if (!IS_WIN30_DIB(lpBI))
//	{
		// ��֧���������͵�DIB����
		
		// �������
	//	::GlobalUnlock((HGLOBAL) hDib);
		
		// ����FALSE
	//	return FALSE;
//	}

	// ����ļ�ͷ

	// �ļ�����"BM"
	bmfHdr.bfType =  0x4d42; //DIB_HEADER_MARKER;

	// ����DIB��Сʱ����򵥵ķ����ǵ���GlobalSize()����������ȫ���ڴ��С��
	// ����DIB�����Ĵ�С�������Ƕ༸���ֽڡ���������Ҫ����һ��DIB����ʵ��С��
	
	// �ļ�ͷ��С����ɫ���С
	// ��BITMAPINFOHEADER��BITMAPCOREHEADER�ṹ�ĵ�һ��DWORD���Ǹýṹ�Ĵ�С��
//	dwDIBSize = *(LPDWORD)lpBI; //+ ::PaletteSize((LPSTR)lpBI);
	dwDIBSize = sizeof(BITMAPINFOHEADER);//+lpBI->biSizeImage;	
	// ����ͼ���С
	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// ����RLEλͼ��û�������С��ֻ������biSizeImage�ڵ�ֵ
		dwDIBSize += lpBI->biSizeImage;
	}
	else
	{
		// ���صĴ�С
		DWORD dwBmBitsSize;

		// ��СΪWidth * Height
		dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*24) * lpBI->biHeight;
		
		// �����DIB�����Ĵ�С
		dwDIBSize += dwBmBitsSize;

		// ����biSizeImage���ܶ�BMP�ļ�ͷ��biSizeImage��ֵ�Ǵ���ģ�
		lpBI->biSizeImage = dwBmBitsSize;
	}


	// �����ļ���С��DIB��С��BITMAPFILEHEADER�ṹ��С
	bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER);
	
	// ����������
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;

	// ����ƫ����bfOffBits�����Ĵ�СΪBitmap�ļ�ͷ��С��DIBͷ��С����ɫ���С
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize;
											 // + PaletteSize((LPSTR)lpBI);
	// ����д�ļ�
//	TRY
	{
		// д�ļ�ͷ
		file.Write((LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER));
		
		// дDIBͷ������
		file.WriteHuge(lpBI, dwDIBSize);
	}
//	CATCH (CFileException, e)
//	{
		// �������
	//	::GlobalUnlock((HGLOBAL) hDib);
		
		// �׳��쳣
///		THROW_LAST();
//	}
//	END_CATCH
	
	// �������
	::GlobalUnlock((HGLOBAL) hDib);
	
	// ����TRUE
	return TRUE;
}


HANDLE DIB::CopyHandle( HANDLE hSrc)
{	
	HANDLE hDst;
	LPBITMAPINFOHEADER lpbi;
	int width,height;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hSrc);
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	hDst = GlobalAlloc(GMEM_MOVEABLE,lpbi->biSize+lpbi->biSizeImage);
	if(!hDst)
		return NULL;
	LPBYTE lpDest;
	lpDest = (LPBYTE)GlobalLock(hDst);
	memcpy(lpDest,(LPBYTE)lpbi,lpbi->biSize+lpbi->biSizeImage);
	GlobalUnlock(hSrc);
	GlobalUnlock(hDst);
	return hDst;

}


BYTE * DIB::GetBits()
{
	//the size of the color map is determined by the number
	//of RGBQUAD structures presend.
	//it also depends on the bit_depth of the Dib
	DWORD dwNumColors,dwColorTableSize;
	BITMAPINFOHEADER *lpDib=(BITMAPINFOHEADER *)m_pDib;
          
	WORD wBitCount=lpDib->biBitCount;

	if(lpDib->biSize>=36)
		dwNumColors=lpDib->biClrUsed;
	else
		dwNumColors=0;
      
	if(dwNumColors==0)
	{
		if(wBitCount!=24)
			dwNumColors=1L<<wBitCount;
		else 
			dwNumColors=0;
	}

	dwColorTableSize=dwNumColors*sizeof(RGBQUAD);

	return m_pDib+lpDib->biSize+dwColorTableSize;
}

int DIB::GetBiBitCount()
{
	if(m_pDib!=NULL)
		return ((BITMAPINFOHEADER *)m_pDib)->biBitCount; 
	return 0;
}

LONG DIB::GetWidth()
{
	return ((BITMAPINFOHEADER *)m_pDib)->biWidth;
}

LONG DIB::GetHeight()
{
	return	((BITMAPINFOHEADER *)m_pDib)->biHeight;
}

//////////////////////���߲���//////////////////////////////
//Lighting Compensate
////////////////////////////////////////////////////////////
BOOL DIB::LightingCompensate(HANDLE hDIB)
{
	if(!hDIB)
		return FALSE;
	LPBITMAPINFOHEADER lpbi;
	int width,height;
	LPBYTE lpData;
	WORD wBytesPerLine;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	//�õ�ͼƬ��͸�
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	//�õ�ͼƬ������
	lpData = this->FindDIBBits(hDIB);
	//�õ�ͼƬÿ�е�������ռ�ֽڸ���
	wBytesPerLine = this->BytePerLine(hDIB);
	//����ϵ��
	const float thresholdco = 0.05;
	//���ظ������ٽ糣��
	const int thresholdnum = 100;
	//�Ҷȼ�����
	int histogram[256];
	for(int i =0;i<256;i++)
		histogram[i] = 0;
	//���ڹ���С��ͼƬ���ж�
	if(width*height*thresholdco < thresholdnum)
		return false;
	int colorr,colorg,colorb;
	long lOffset;
	//��������ͼƬ
	
	for( i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{	
			//�õ��������ݵ�ƫ��
			lOffset = this->PixelOffset(i,j,wBytesPerLine);
			//�õ�rgbֵ
			colorb = *(lpData+lOffset++);
			colorg = *(lpData+lOffset++);
			colorr = *(lpData+lOffset++);
			//����Ҷ�ֵ
			int gray = (colorr * 299 + colorg * 587 + colorb * 114)/1000;
			histogram[gray]++;
		}
		int calnum =0;
		int total = width*height;
		int num;
		//�����ѭ���õ�����ϵ��thresholdco���ٽ�Ҷȼ�
		for(i =0;i<256;i++)
		{
			if((float)calnum/total < thresholdco)
			{
				calnum+= histogram[255-i];
				num = i;
			}
			else
				break;
		}
		int averagegray = 0;
		calnum =0;
		//�õ����������������ܵĻҶ�ֵ
		for(i = 255;i>=255-num;i--)
		{
			averagegray += histogram[i]*i;
			calnum += histogram[i];
		}
		averagegray /=calnum;
		//�õ����߲�����ϵ��
		float co = 255.0/(float)averagegray;
		//�����ѭ����ͼ����й��߲���
		for(i =0;i<height;i++)
			for(int j=0;j<width;j++)
			{	
				//�õ�����ƫ��
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				//�õ���ɫ����
				colorb = *(lpData+lOffset);
				//����
				colorb *=co;
				//�ٽ��ж�
				if(colorb >255)
					colorb = 255;
				//����
				*(lpData+lOffset) = colorb;
				//��ɫ����
				colorb = *(lpData+lOffset+1);
				colorb *=co;
				if(colorb >255)
					colorb = 255;
				*(lpData+lOffset+1) = colorb;
				//��ɫ����
				colorb = *(lpData+lOffset+2);
				colorb *=co;
				if(colorb >255)
					colorb = 255;
				*(lpData+lOffset+2) = colorb;

			}

			return TRUE;
}
//////////////////////////////////////����////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void DIB::Dilation(HANDLE hDIB,int m_top,int m_bottom,int m_left,int m_right)
{
LPBITMAPINFOHEADER lpbi;
	int height;
	int width;
	WORD wBytesPerLine;
	LPBYTE lpData;
	LPBYTE lpTemp;
	long lOffset;
	//�õ�ͼ��Ļ�����Ϣ
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = m_top;
	width = m_right;
	wBytesPerLine = this->BytePerLine(hDIB);
	lpData = this->FindDIBBits(hDIB);
	//����һ�����������С��ͬ���ڴ�
	lpTemp = (LPBYTE) new BYTE[wBytesPerLine * height];
	
	
	long lOffsetJudge;
	for (int i=1+m_bottom; i<height-1; i++)
		for (int j=1+m_left; j<width-1; j++)
		{	
			lOffset = this->PixelOffset(i, j, wBytesPerLine);
			//�����ǰ��Ϊ��ɫ������ѭ��
			if(*(lpData + lOffset) == 255)
			{
				*(lpTemp + lOffset++) = 255;
				*(lpTemp + lOffset++) = 255;
				*(lpTemp + lOffset++) = 255;
				continue;
			}
			//���򿼲����������ĸ���
			else
			{	
				lOffsetJudge = this->PixelOffset(i-1, j, wBytesPerLine);
				//�������ĵ�Ϊ��ɫ
				if(*(lpData + lOffsetJudge) == 255)
				{	//����Ϊ��ɫ��������ѭ��
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}

				//��������ĵ�
				lOffsetJudge = this->PixelOffset(i+1,j, wBytesPerLine);
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				
				//������ߵĵ�
				lOffsetJudge = this->PixelOffset(i,j-1, wBytesPerLine);
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				//�����ұߵĵ�
				lOffsetJudge = this->PixelOffset(i,j+1, wBytesPerLine);
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				//����������Ҷ��Ǻ�ɫ�㣬�����ʱ����ĵ�����Ϊ��ɫ
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;

			}
				
		}
		//����ͼ�����ܵĵ㣬����Ϊ��ɫ
		for(i=m_bottom; i<height; i++)
		{
			lOffset = this->PixelOffset(i, 0, wBytesPerLine);
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}

		for(i=m_bottom; i<height; i++)
		{
			lOffset = this->PixelOffset(i, width-1, wBytesPerLine);
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}

		for(i=m_left; i<width; i++)
		{
			lOffset = this->PixelOffset(0, i, wBytesPerLine);
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}

		for(i=m_left; i<width; i++)
		{
			lOffset = this->PixelOffset(height-1, i, wBytesPerLine);
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}
		//����ʱ����ĵ㿽����ԭ�����������
		memcpy(lpData, lpTemp, wBytesPerLine*height);
		delete [] lpTemp;
		GlobalUnlock(hDIB);
	
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////��ʴ///////////////////////////////////////
void DIB::Erasion(HANDLE hDIB,int m_top,int m_bottom,int m_left,int m_right)
{

	LPBITMAPINFOHEADER lpbi;
	LPBYTE lpData;
	WORD wBytesPerLine;
	long lOffset;
	long lOffsetJudge;
	int height;
	int width;
	
	//�õ���������
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = m_top;
	width = m_right;
	wBytesPerLine = BytePerLine(hDIB);
	lpData = FindDIBBits(hDIB);
	
	HANDLE hTempDIB;
	LPBYTE lpTemp;
	//����ͬ����С���ڴ�
	hTempDIB =   GlobalAlloc(GMEM_MOVEABLE,(DWORD)(sizeof(BITMAPINFOHEADER) + wBytesPerLine*height));
	//�ж��ڴ����
	if(!hTempDIB)
	{	
		GlobalFree(hTempDIB);
		GlobalFree(hDIB);
		return;
	}
	lpTemp = (LPBYTE)GlobalLock(hTempDIB);
	lpTemp+= sizeof(BITMAPINFOHEADER);
	//�����ѭ��ʵ�ָ�ʴ����
	for (int i=1+m_bottom; i<height-1; i++)
		for (int j=1+m_left; j<width-1; j++)
		{
			lOffset = PixelOffset(i,j,wBytesPerLine);
			//���Ϊ��ɫ��
			if (*(lpData+lOffset) == 255)
			{	
				//��������ĵ�
				lOffsetJudge = PixelOffset(i-1, j, wBytesPerLine);
				//����Ǻ�ɫ�Ͱ�ԭ���ĵ�����Ϊ��ɫ��������ѭ��
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//��������ĵ�
				lOffsetJudge = PixelOffset(i+1, j, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//����ĵ�
				lOffsetJudge = PixelOffset(i, j-1, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//����ĵ�
				lOffsetJudge = PixelOffset(i, j+1, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//������������ĸ��㶼�ǰ�ɫ��������Ϊ��ɫ
				lOffset = this->PixelOffset(i, j, wBytesPerLine);
				*(lpTemp + lOffset)   = 255;
				*(lpTemp + lOffset+1) = 255;
				*(lpTemp + lOffset+2) = 255;
				
			}
			//�����ǰ��Ϊ��ɫ��������ʱ��Ŀ������������Ϊ��ɫ
			else
			{
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;
			}
		}
		
		//��ͼ���ܱߵĵ�ȫ������Ϊ��ɫ
		for(i=m_bottom; i<height; i++)
		{
			lOffset = PixelOffset(i, 0, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
		
		for(i=m_bottom; i<height; i++)
		{
			lOffset = PixelOffset(i, width-1, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}

	for (i=m_left; i<width; i++)
		{
			lOffset = PixelOffset(0, i, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	
	for (i=m_left; i<width; i++)
		{
			lOffset = PixelOffset(height-1, i, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	//����ʱ�������ֵ������ԭ���ľ������
	memcpy(lpData,lpTemp,wBytesPerLine*height);
	GlobalUnlock(hDIB);
	GlobalUnlock(hTempDIB);
	GlobalFree(hTempDIB);
}