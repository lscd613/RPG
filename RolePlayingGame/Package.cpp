#include "pch.h"
#include "Package.h"
#include <string>
Package::Package(Entity *r = nullptr):_entity(r)
{
	
}
bool Package::AddItem(baseItem* pItem)
{
	if (pItem == nullptr || Full()) {
		return false;
	}
	itemsVec.push_back(pItem);
	size++;
	return true;
}

void Package::Run(Board& b)
{
	if (_entity == nullptr || !IsKeyDown(VK_SPACE)) {
		return;
	}
	auto pos = _entity->GetPos();
	UpdateGridPos(pos);
	Cell* cell = b.GetCell(pos.grid_x, pos.grid_y);
	if (cell == nullptr) {
		return ;
	}

	//与Package::AddItem的判断条件要一致
	if (Full()) {
		return ;
	}
	baseItem* pItem = cell->Pick();
	if (pItem != nullptr) {
		if (AddItem(pItem)) {
			std::cout << "背包拾取成功" << std::endl;
		}
	}
	return;
}

void Package::Show()
{
	setfillcolor(BLACK);
	fillrectangle((int)(g_data.screenWidth * 0.7), (int)(g_data.screenHeight * 0.7), (int)(g_data.screenWidth * 0.95), (int)(g_data.screenHeight * 0.95));
	int vertical = 0, space = 20;
	for (int i = 0; i < itemsVec.size(); i++) {
		if (itemsVec[i]) {
			outtextxy((int)(g_data.screenWidth * 0.7 + 5), (int)(g_data.screenHeight * 0.7 + 5 + vertical),
				(std::to_string(i + 1) + ":" + itemsVec[i]->GetName()).c_str());
			vertical += space;
		}
	}
}
