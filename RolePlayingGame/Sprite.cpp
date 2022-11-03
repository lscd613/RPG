#include "pch.h"
#include "Sprite.h"
#include <fstream>
#include <iostream>
#include "ImageManager.h"
void copyVec(std::vector<int>& v1, std::vector<int>& v2) {
	if (v2.size() > v1.size()) {
		return;
	}
	for (int i = 0; i < v2.size(); i++)
	{
		v1[i] = v2[i];
	}
}


void Sprite::SetImages(std::string type, int typeId)
{
	ImageManager* imgMng = ImageManager::GetInstance();
	if (!imgMng) {
		return;
	}
	imgVecPtr = imgMng->GetImage(type, typeId);
	if (imgVecPtr) {
		for (int i = 0, j = 0; i < paintIndexMax.size() && j < imgVecPtr->size(); i++, j++) {
			paintIndexMax[i] = (int)((*imgVecPtr)[j].size()) / DIRECT;
		}
	}
}

void Sprite::PaintingSwitch(const moveStatus moveStatus, const int width)
{
	if (moveStatus < 0 || moveStatus >= paintIndexMax.size()) {
		return;
	}
	switch (moveStatus)
	{
	case run:
		if (g_data.gridWidth / paintIndexMax[moveStatus] * 2 <= runPointSum)
		{
			runPointSum = 0;
			++PaintIndex[moveStatus];
		}
		break;
	default:
		if ((int)(GetTickCount() - paintTimeIndex) > paintIntervaltime)
		{
			++PaintIndex[moveStatus];
			paintTimeIndex = GetTickCount();
		}
		break;
	}
	if (PaintIndex[moveStatus] >= paintIndexMax[moveStatus])
	{
		PaintIndex[moveStatus] = 0;
	}
	runPointSum += 2;
}

Sprite::Sprite(const position& p, const moveStatus& s, const property& prop):pos(p),stat(s),prop(prop)
,imgVecPtr(nullptr)
{

}

Sprite::~Sprite()
{

}



void Sprite::Render(int centerX, const int centerY)
{
	if (!imgVecPtr || stat < 0 || stat >= imgVecPtr->size()) {
		return;
	}
	auto &imgVec = (*imgVecPtr)[stat];

	int tmpIndex = prop.direction * paintIndexMax[stat] + PaintIndex[stat];
	if (tmpIndex < 0 || tmpIndex > imgVec.size()) {
		return;
	}

	putimagex(pos.x - centerX + g_data.cameraCenter[0] + statOffset[stat],
		pos.y - centerY + g_data.cameraCenter[1] - yOffset, pWidth, pHeight,
		*imgVec[tmpIndex],
		px[stat], py);

	if (prop.HP > 0) {
		int x = pos.x - centerX + g_data.cameraCenter[0] - 20;
		int y = pos.y - centerY + g_data.cameraCenter[1] - 95;
		rectangle(x, y, x + 30, y + 10);
		setfillcolor(RED);
		double percent = prop.HP / (double)prop.max_HP;
		fillrectangle(x, y, x + (int)(30 * percent), y + 10);
	}
	PaintingSwitch(stat, prop.width);
}

void Sprite::SetPaintIndexMax(std::vector<int> vec)
{
	copyVec(paintIndexMax, vec);
}

void Sprite::SetPaintIntervaltime(int t)
{ 
	paintIntervaltime = t;
}

void Sprite::SetStatOffset(std::vector<int> vec)
{
	copyVec(statOffset, vec);
}

void Sprite::Set_yOffset(int y)
{
	yOffset = y;
}

void Sprite::Set_px(std::vector<int> vec)
{
	copyVec(px, vec);
}

void Sprite::Set_py(int val)
{
	py = val;
}

void Sprite::Set_pWidth(int i)
{
	pWidth = i;
}

void Sprite::Set_pHeight(int i)
{
	pHeight = i;
}

