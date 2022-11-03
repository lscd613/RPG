#pragma once
#include <graphics.h>
#include <Windows.h>
// ���øÿ����ʹ�� TransparentBlt ����
#pragma comment( lib, "MSIMG32.LIB")

#include <comdef.h>//��ʼ��һ��com��
#include "GdiPlus.h"

#pragma comment(lib,"gdiplus.lib")
#include <atlconv.h>

#include <string>

// ֧��͸�����Ƶ�putimage��
// pDestImgΪ�ձ�ʾ��pSrcImg������Ļ�ϣ����򻭵�pDestImg��
// ͸��ɫΪ��ɫ�������زı���������ַ�ɫ��Ҫ����������͸���ĵط�Ҳ͸����
// ��Դ��Ҫʹ��bmp��ʽ����Ϊjpg���Ż����أ�����ĳЩ͸�����ص㲻�����ۡ�
inline void putimagex(int destX, int destY, int destWidth, int destHeight, IMAGE &srcImg, int srcX, int srcY)
{
	// ��ȡ��ͼ���ں� IMAGE ����ľ����TransparentBlt ������Ҫ��
	HDC dstDC = GetImageHDC(NULL);
	HDC srcDC = GetImageHDC(&srcImg);

	int w = min(srcImg.getwidth() - srcX, destWidth);
	int h = min(srcImg.getheight() - srcY, destHeight);

	// ʹ�� Windows GDI ����ʵ��͸��λͼ
	TransparentBlt(dstDC, destX, destY, w, h, srcDC, srcX, srcY, w, h, 0xff00ff);
}

// ��ȡ���λ��
inline POINT GetCursorPos()
{
	HWND hwnd = GetHWnd();			// ��ȡ��ͼ���ھ��
	POINT point;
	GetCursorPos(&point);			// ��ȡ���ָ��λ�ã���Ļ���꣩
	ScreenToClient(hwnd, &point);	// �����ָ��λ��ת��Ϊ��������

	return point;
}

// �жϼ����Ƿ���
// @param key������ֵ����ĸ�����֣�ֱ����IsKeyDown('Q')��IsKeyDown('A')�ȣ�
//				����������Ҫʹ��������룺IsKeyDown(VK_F1)��IsKeyDown(VK_ESCAPE)���ٶ����������ҵ����ж���
inline bool IsKeyDown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000 ? 1 : 0);
}

inline void loadpng(IMAGE *pDstImg, LPCTSTR pImgFile)
{
	USES_CONVERSION;

	Gdiplus::Bitmap bitmap(A2W(pImgFile));


	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();
	pDstImg->Resize(width, height);


	Gdiplus::Rect rect(0, 0, width, height);
	Gdiplus::BitmapData bitmapData;
	if (0 != bitmap.LockBits(&rect, Gdiplus::ImageLockMode::ImageLockModeRead, PixelFormat32bppARGB, &bitmapData))
	{
		return;
	}
	DWORD* pmem = GetImageBuffer(pDstImg);
	char *pData = (char*)bitmapData.Scan0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (pData[3] == 0)
			{
				pmem[i * width + j] = RGB(255, 0, 255);
			}
			else
			{
				pmem[i * width + j] = RGB(pData[0], pData[1], pData[2]);
			}
			pData += 4;
		}
	}
	bitmap.UnlockBits(&bitmapData);
}

inline void loadimagex(IMAGE &destImg, LPCTSTR pImgFile)
{
	if (pImgFile == NULL)
	{
		return;
	}

	std::string filePath = pImgFile;

	if (filePath.find(".png") == std::string::npos)
	{
		loadimage(&destImg, pImgFile);
	}
	else
	{
		loadpng(&destImg, pImgFile);
	}



}

inline HWND initgraphx(int width, int height, int flag = NULL)
{
	HWND hWnd = initgraph(width, height, flag);

	Gdiplus::GdiplusStartupInput gidstart;
	ULONG_PTR gidplusToken;
	Gdiplus::GdiplusStartup(&gidplusToken, &gidstart, NULL);

	return hWnd;
}
inline void closegraphx()
{
	//Gdiplus::GdiplusShutdown(gidplusToken);// �ͷ�gdi+��Դ
	closegraph();
}

// ��pSrcImgˮƽ����ת�Ľ�������pDstImg
inline void mirrorimage(IMAGE &srcImg, IMAGE &dstImg)
{
	int width = srcImg.getwidth();
	int height = srcImg.getheight();
	dstImg.Resize(width, height);

	DWORD *pSrcMem = GetImageBuffer(&srcImg);
	DWORD *pDstMem = GetImageBuffer(&dstImg);

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			pDstMem[j] = pSrcMem[width - j - 1];
		}
		pSrcMem += width;
		pDstMem += width;
	}

}

inline int getImageWidth(IMAGE &img)
{
	return img.getwidth();
}

inline int getImageHeight(IMAGE &img)
{
	return img.getheight();
}