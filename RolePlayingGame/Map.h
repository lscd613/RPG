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
	void AddItem(int x, int y, int handle);
private:
	Board board;
	std::map<int, IMAGE*> imgMap;
	
};

