#include "pch.h"
#include "Map.h"
#include <string>

Map::Map()
{
	LoadImg();
}


Map::~Map()
{
	for (int i = 0; i != 9 * 9; ++i)
	{
		SAFE_DELETE(imgMap[i]);
		ptrCount--;
	}
}


Board & Map::GetBoard() {
	return board;
}

std::map<int, IMAGE*>& Map::GetImages()
{
	return imgMap;
}

bool Map::AddEntity(int x, int y, Entity * e)
{
	if (e) {
		return board.AddEntity(x, y, e);
	}
	return false;
}

void Map::AddItem(int x, int y, int handle)
{
	board.AddItem(x, y, handle);
}

void Map::LoadImg()
{
	char imgPath[] = "res/scene_10240/0_0.jpg";
	int row = 16, colume = 18;
	for (int i = 0; i < 9; ++i, imgPath[row]++)
	{
		imgPath[18] = '0';
		for (int j = 0; j < 9; ++j, imgPath[colume]++)
		{
			IMAGE* img = new IMAGE;
			if (img) {
				loadimagex(*img, imgPath);
				imgMap[i * 9 + j] = img;
				ptrCount++;
			}
		}
	}
}
