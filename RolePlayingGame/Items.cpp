#include "pch.h"
#include "Items.h"
#include "Config.h"
#include <string>
Item::Item(int typeID, int id, int x, int y):baseItem(id)
{
	Config* config = Config::GetInstance();
	if (config != nullptr) {
		CsvReader* reader = config->GetConfig("item");
		if (reader != nullptr) {
			reader->GetString(typeID, 2, name);
		}
	}
	SetGridPos(x, y);
	prop.SetMaxHP(0);
	sprite.SetImages("item", typeID);
	sprite.Set_pWidth(50);
	sprite.Set_pHeight(50);
	sprite.SetStatOffset(std::vector<int>{ -25, -95, -160, -130 });
	sprite.Set_yOffset(28);
	sprite.SetPaintIndexMax({0});
	sprite.Set_px({ 0 });
	sprite.Set_py(0);
	type = entityType::item;
	this->typeID = typeID;
}
