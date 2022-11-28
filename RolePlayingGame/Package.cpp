#include "pch.h"
#include "Package.h"
#include <string>
#include "baseItemCreator.h"
Package::Package(Entity *r = nullptr):_entity(r)
{
	
}
bool Package::AddItem(shared_ptr<baseItem> ptr)
{
	if (!ptr)
		return false;
	if (Full()) {
		return false;
	}
	itemsVec.push_back(ptr);
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
	auto item = cell->Pick();
	if (item != nullptr) {
		if (AddItem(item)) {
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
		auto item = itemsVec[i];
		if (item) {
			outtextxy((int)(g_data.screenWidth * 0.7 + 5), (int)(g_data.screenHeight * 0.7 + 5 + vertical),
				(std::to_string(i + 1) + ":" + item->GetName()).c_str());
			vertical += space;
		}
	}
}
