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
	void AddItem(int x, int y, shared_ptr<baseItem> handle);
private:
	Board board;
	std::map<int, IMAGE*> imgMap;
	
};

