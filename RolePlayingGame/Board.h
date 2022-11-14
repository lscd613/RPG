#pragma once

#include <vector>
#include <map>
#include <cmath>
#include "Entity.h"
#include "Cell.h"
#include "Data.h"
#include "baseItem.h"
extern Data g_data;
class Board
{
private:
	std::vector<Cell*> Cells;
public:
	Board();
	~Board();
	Cell* GetCell(int x,int y);
	Cell* GetCell(int index);
	bool IsEmptyCell(int x, int y);
	bool IsNoObstackleCell(int x, int y);
	bool IsValidIndex(int x, int y);
	bool AddEntity(int x, int y, Entity *e);
	bool AddItem(int x, int y, int itemHandle);
	bool LockCell(int x, int y, int id);
	void UnlockCell(int x, int y, int id);
};

