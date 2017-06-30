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
    //得到文件大小
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
	if(sizeof(BITMAPFILEHEADER)!=dwRead)//读取文件出错
		goto ErrExit;
	if(bmfHeader.bfType != 0x4d42)//文件类型不匹配
		goto ErrExit;
	if(!ReadFile(hFile,(LPBYTE)lpbi,sizeof(BITMAPINFOHEADER),&dwRead,NULL))
		goto ErrExit;
	if(sizeof(BITMAPINFOHEADER)!= dwRead)//读取数据出错
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
	//根据情况设定文件指针
	if(bmfHeader.bfOffBits != 0L)
		SetFilePointer(hFile,bmfHeader.bfOffBits,NULL,FILE_BEGIN);
    //读取文件的象素颜色数据
	if(ReadFile(hFile,(LPBYTE)lpbi+lpbi->biSize,lpbi->biSizeImage,&dwRead,NULL))
			goto OKExit;
	
	ErrExit:
		GlobalUnlock(hDIB);
	
	ErrExitNoUnlock:
		GlobalFree(hDIB); //释放内存
		return NULL;

	OKExit:
		GlobalUnlock(hDIB);
		return hDIB;
		
}


HDIB DIB::LoadDIB(LPCTSTR lpFileName)
{
	HANDLE hDIB;
	HANDLE hFile;
	//创建文件句柄
	if((hFile = CreateFile(lpFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL))!= INVALID_HANDLE_VALUE)
	{  
		//读取数据
		hDIB = ReadDIBFile(hFile);
		//关闭文件句柄
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
	// Bitmap文件头
	BITMAPFILEHEADER bmfHdr;
	
	// 指向BITMAPINFOHEADER的指针
	LPBITMAPINFOHEADER lpBI;
	
	// DIB大小
	DWORD dwDIBSize =0;

	if (hDib == NULL)
	{
		// 如果DIB为空，返回FALSE
		return FALSE;
	}

	// 读取BITMAPINFO结构，并锁定
	lpBI = (LPBITMAPINFOHEADER) ::GlobalLock((HGLOBAL) hDib);
	
	if (lpBI == NULL)
	{
		// 为空，返回FALSE
		return FALSE;
	}
	
	// 判断是否是WIN3.0 DIB
//	if (!IS_WIN30_DIB(lpBI))
//	{
		// 不支持其它类型的DIB保存
		
		// 解除锁定
	//	::GlobalUnlock((HGLOBAL) hDib);
		
		// 返回FALSE
	//	return FALSE;
//	}

	// 填充文件头

	// 文件类型"BM"
	bmfHdr.bfType =  0x4d42; //DIB_HEADER_MARKER;

	// 计算DIB大小时，最简单的方法是调用GlobalSize()函数。但是全局内存大小并
	// 不是DIB真正的大小，它总是多几个字节。这样就需要计算一下DIB的真实大小。
	
	// 文件头大小＋颜色表大小
	// （BITMAPINFOHEADER和BITMAPCOREHEADER结构的第一个DWORD都是该结构的大小）
//	dwDIBSize = *(LPDWORD)lpBI; //+ ::PaletteSize((LPSTR)lpBI);
	dwDIBSize = sizeof(BITMAPINFOHEADER);//+lpBI->biSizeImage;	
	// 计算图像大小
	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// 对于RLE位图，没法计算大小，只能信任biSizeImage内的值
		dwDIBSize += lpBI->biSizeImage;
	}
	else
	{
		// 象素的大小
		DWORD dwBmBitsSize;

		// 大小为Width * Height
		dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*24) * lpBI->biHeight;
		
		// 计算出DIB真正的大小
		dwDIBSize += dwBmBitsSize;

		// 更新biSizeImage（很多BMP文件头中biSizeImage的值是错误的）
		lpBI->biSizeImage = dwBmBitsSize;
	}


	// 计算文件大小：DIB大小＋BITMAPFILEHEADER结构大小
	bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER);
	
	// 两个保留字
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;

	// 计算偏移量bfOffBits，它的大小为Bitmap文件头大小＋DIB头大小＋颜色表大小
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize;
											 // + PaletteSize((LPSTR)lpBI);
	// 尝试写文件
//	TRY
	{
		// 写文件头
		file.Write((LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER));
		
		// 写DIB头和象素
		file.WriteHuge(lpBI, dwDIBSize);
	}
//	CATCH (CFileException, e)
//	{
		// 解除锁定
	//	::GlobalUnlock((HGLOBAL) hDib);
		
		// 抛出异常
///		THROW_LAST();
//	}
//	END_CATCH
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDib);
	
	// 返回TRUE
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

//////////////////////光线补偿//////////////////////////////
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
	//得到图片宽和高
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	//得到图片数据区
	lpData = this->FindDIBBits(hDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = this->BytePerLine(hDIB);
	//比例系数
	const float thresholdco = 0.05;
	//象素个数的临界常数
	const int thresholdnum = 100;
	//灰度级数组
	int histogram[256];
	for(int i =0;i<256;i++)
		histogram[i] = 0;
	//对于过于小的图片的判断
	if(width*height*thresholdco < thresholdnum)
		return false;
	int colorr,colorg,colorb;
	long lOffset;
	//考察整个图片
	
	for( i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{	
			//得到象素数据的偏移
			lOffset = this->PixelOffset(i,j,wBytesPerLine);
			//得到rgb值
			colorb = *(lpData+lOffset++);
			colorg = *(lpData+lOffset++);
			colorr = *(lpData+lOffset++);
			//计算灰度值
			int gray = (colorr * 299 + colorg * 587 + colorb * 114)/1000;
			histogram[gray]++;
		}
		int calnum =0;
		int total = width*height;
		int num;
		//下面的循环得到满足系数thresholdco的临界灰度级
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
		//得到满足条件的象素总的灰度值
		for(i = 255;i>=255-num;i--)
		{
			averagegray += histogram[i]*i;
			calnum += histogram[i];
		}
		averagegray /=calnum;
		//得到光线补偿的系数
		float co = 255.0/(float)averagegray;
		//下面的循环对图象进行光线补偿
		for(i =0;i<height;i++)
			for(int j=0;j<width;j++)
			{	
				//得到数据偏移
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				//得到蓝色分量
				colorb = *(lpData+lOffset);
				//调整
				colorb *=co;
				//临界判断
				if(colorb >255)
					colorb = 255;
				//保存
				*(lpData+lOffset) = colorb;
				//绿色分量
				colorb = *(lpData+lOffset+1);
				colorb *=co;
				if(colorb >255)
					colorb = 255;
				*(lpData+lOffset+1) = colorb;
				//红色分量
				colorb = *(lpData+lOffset+2);
				colorb *=co;
				if(colorb >255)
					colorb = 255;
				*(lpData+lOffset+2) = colorb;

			}

			return TRUE;
}
//////////////////////////////////////膨胀////////////////////////////////////////////
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
	//得到图象的基本信息
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = m_top;
	width = m_right;
	wBytesPerLine = this->BytePerLine(hDIB);
	lpData = this->FindDIBBits(hDIB);
	//申请一块和数据区大小相同的内存
	lpTemp = (LPBYTE) new BYTE[wBytesPerLine * height];
	
	
	long lOffsetJudge;
	for (int i=1+m_bottom; i<height-1; i++)
		for (int j=1+m_left; j<width-1; j++)
		{	
			lOffset = this->PixelOffset(i, j, wBytesPerLine);
			//如果当前点为白色，接着循环
			if(*(lpData + lOffset) == 255)
			{
				*(lpTemp + lOffset++) = 255;
				*(lpTemp + lOffset++) = 255;
				*(lpTemp + lOffset++) = 255;
				continue;
			}
			//否则考察上下左右四个点
			else
			{	
				lOffsetJudge = this->PixelOffset(i-1, j, wBytesPerLine);
				//如果上面的点为白色
				if(*(lpData + lOffsetJudge) == 255)
				{	//设置为白色，并继续循环
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}

				//考察下面的点
				lOffsetJudge = this->PixelOffset(i+1,j, wBytesPerLine);
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				
				//考察左边的点
				lOffsetJudge = this->PixelOffset(i,j-1, wBytesPerLine);
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				//考察右边的点
				lOffsetJudge = this->PixelOffset(i,j+1, wBytesPerLine);
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				//如果上下左右都是黑色点，则把暂时区域的点设置为黑色
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;

			}
				
		}
		//处理图象四周的点，设置为黑色
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
		//把暂时区域的点拷贝到原句柄区域下面
		memcpy(lpData, lpTemp, wBytesPerLine*height);
		delete [] lpTemp;
		GlobalUnlock(hDIB);
	
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////腐蚀///////////////////////////////////////
void DIB::Erasion(HANDLE hDIB,int m_top,int m_bottom,int m_left,int m_right)
{

	LPBITMAPINFOHEADER lpbi;
	LPBYTE lpData;
	WORD wBytesPerLine;
	long lOffset;
	long lOffsetJudge;
	int height;
	int width;
	
	//得到基本数据
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = m_top;
	width = m_right;
	wBytesPerLine = BytePerLine(hDIB);
	lpData = FindDIBBits(hDIB);
	
	HANDLE hTempDIB;
	LPBYTE lpTemp;
	//申请同样大小的内存
	hTempDIB =   GlobalAlloc(GMEM_MOVEABLE,(DWORD)(sizeof(BITMAPINFOHEADER) + wBytesPerLine*height));
	//判断内存情况
	if(!hTempDIB)
	{	
		GlobalFree(hTempDIB);
		GlobalFree(hDIB);
		return;
	}
	lpTemp = (LPBYTE)GlobalLock(hTempDIB);
	lpTemp+= sizeof(BITMAPINFOHEADER);
	//下面的循环实现腐蚀功能
	for (int i=1+m_bottom; i<height-1; i++)
		for (int j=1+m_left; j<width-1; j++)
		{
			lOffset = PixelOffset(i,j,wBytesPerLine);
			//如果为白色点
			if (*(lpData+lOffset) == 255)
			{	
				//考察上面的点
				lOffsetJudge = PixelOffset(i-1, j, wBytesPerLine);
				//如果是黑色就把原来的点设置为黑色，并接着循环
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//考察下面的点
				lOffsetJudge = PixelOffset(i+1, j, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//左面的点
				lOffsetJudge = PixelOffset(i, j-1, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//右面的点
				lOffsetJudge = PixelOffset(i, j+1, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//如果上下左右四个点都是白色，则设置为白色
				lOffset = this->PixelOffset(i, j, wBytesPerLine);
				*(lpTemp + lOffset)   = 255;
				*(lpTemp + lOffset+1) = 255;
				*(lpTemp + lOffset+2) = 255;
				
			}
			//如果当前点为黑色，则在暂时的目标区域中设置为黑色
			else
			{
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;
			}
		}
		
		//把图象周边的点全部设置为黑色
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
	//把暂时区域的数值拷贝到原来的句柄下面
	memcpy(lpData,lpTemp,wBytesPerLine*height);
	GlobalUnlock(hDIB);
	GlobalUnlock(hTempDIB);
	GlobalFree(hTempDIB);
}