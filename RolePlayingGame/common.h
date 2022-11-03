#pragma once
#include <graphics.h>
#include <Windows.h>
// 引用该库才能使用 TransparentBlt 函数
#pragma comment( lib, "MSIMG32.LIB")

#include <comdef.h>//初始化一下com口
#include "GdiPlus.h"

#pragma comment(lib,"gdiplus.lib")
#include <atlconv.h>

#include <string>

// 支持透明绘制的putimage，
// pDestImg为空表示将pSrcImg画到屏幕上，否则画到pDestImg上
// 透明色为粉色，所以素材本身如果出现粉色需要处理，否则不想透明的地方也透明了
// 资源需要使用bmp格式，因为jpg会优化像素，导致某些透明像素点不够“粉”
inline void putimagex(int destX, int destY, int destWidth, int destHeight, IMAGE &srcImg, int srcX, int srcY)
{
	// 获取绘图窗口和 IMAGE 对象的句柄，TransparentBlt 函数需要用
	HDC dstDC = GetImageHDC(NULL);
	HDC srcDC = GetImageHDC(&srcImg);

	int w = min(srcImg.getwidth() - srcX, destWidth);
	int h = min(srcImg.getheight() - srcY, destHeight);

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, destX, destY, w, h, srcDC, srcX, srcY, w, h, 0xff00ff);
}

// 获取鼠标位置
inline POINT GetCursorPos()
{
	HWND hwnd = GetHWnd();			// 获取绘图窗口句柄
	POINT point;
	GetCursorPos(&point);			// 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hwnd, &point);	// 将鼠标指针位置转换为窗口坐标

	return point;
}

// 判断键盘是否按下
// @param key：按键值，字母、数字，直接用IsKeyDown('Q')，IsKeyDown('A')等，
//				其他按键需要使用虚拟键码：IsKeyDown(VK_F1)，IsKeyDown(VK_ESCAPE)，百度虚拟键码可找到所有定义
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
	//Gdiplus::GdiplusShutdown(gidplusToken);// 释放gdi+资源
	closegraph();
}

// 将pSrcImg水平镜像翻转的结果输出到pDstImg
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