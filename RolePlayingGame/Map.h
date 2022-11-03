#pragma once
#include "Board.h"
#include "baseItem.h"
class Map
{

public:
	Map();
	~Map();
	void LoadImg();
	Board& GetBoard();
	std::map<int, IMAGE*>& GetImages();
	bool AddEntity(int x, int y, Entity* e);
	bool AddItem(int x, int y, baseItem* e);
private:
	Board board;
	std::map<int, IMAGE*> imgMap;
	
};

