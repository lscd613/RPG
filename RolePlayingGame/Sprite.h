#pragma once
#include "common.h"
#include <vector>
#include "Data.h"
class Sprite
{
	//����
	std::vector<std::vector<IMAGE*>> *imgVecPtr;
	int pHeight = 300,pWidth = 300;
	std::vector<int> PaintIndex = { 0,0,0,0 };
	double runPointSum = 0;
	decltype(GetTickCount()) paintTimeIndex = GetTickCount();//�����л���ʱ���
	int paintIntervaltime = 130;//�����л����ʱ��
	int timeIndex = GetTickCount();
	std::vector<int>paintIndexMax = { 5,6,6,0 };//�ƶ�����������ֵ
	std::vector<int> statOffset = { -25,-45,-120,-100 };
	int yOffset = 115;
	std::vector<int> wBorder = { 0 ,30,200,0 };
	std::vector<int> px = { 105,85,5,0 };
	int py = 30;
	void PaintingSwitch(const moveStatus moveStatus, const int width);//���ﶯ���л�

	const position& pos;
	const moveStatus& stat;
	const property& prop;
public:
	Sprite(const position& p, const moveStatus& s, const property& prop);
	~Sprite();
	void SetImages(std::string type, int typeId);
	void Render(const int centerX, const int centerY);
	void SetPaintIndexMax(std::vector<int>);
	void SetPaintIntervaltime(int);
	void SetStatOffset(std::vector<int>);
	void Set_yOffset(int);
	void Set_px(std::vector<int>);
	void Set_py(int);
	void Set_pWidth(int);
	void Set_pHeight(int);
};

