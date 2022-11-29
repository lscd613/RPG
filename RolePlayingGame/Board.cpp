#include "pch.h"
#include "Board.h"
#include <iostream>
#include "Data.h"
extern Data g_data;
Board::Board()
{
	std::ifstream file("map.txt");
	int k = 0;
	for (int i = 0; i < g_data.mapGridHeight; ++i)
	{
		for (int j = 0; j < g_data.mapGridWidth; ++j)
		{
			k++;
			int temp = 0;
			file >> temp;
			Cell *cell = new Cell(temp);
			if (cell) {
				Cells.push_back(cell);
			}
		}
	}
	file.close();
}


Board::~Board()
{
	for (auto &cell : Cells) {
		SAFE_DELETE(cell);
	}
}

Cell* Board::GetCell(int x, int y)
{
	if (x >= 0 && x < ::g_data.mapGridWidth
		&& y >= 0 && y < ::g_data.mapGridHeight) {
		int index = g_data.index(x, y);
		return GetCell(index);
	}
	return nullptr;	
}

Cell* Board::GetCell(int index)
{
	
	if (index >= 0 && index < Cells.size()) {
		return Cells[index];
	}
	return nullptr;
}

bool Board::IsEmptyCell(int x, int y)
{
	Cell* cell = GetCell(x, y);
	if (cell && !cell->IsBlocked()) {
		return true;
	}
	return false;
}
bool Board::IsNoObstackleCell(int x, int y)
{
	Cell* cell = GetCell(x, y);
	if (cell && !cell->HasObstacle()) {
		return true;
	}
	return false;
}

bool Board::IsValidIndex(int x, int y)
{
	if (x >= 0 && x < ::g_data.mapGridWidth
		&& y >= 0 && y < ::g_data.mapGridHeight) {
		return true;
	}
	return false;
}



bool Board::AddEntity(int x, int y, shared_ptr<Entity> ptr)
{
	Cell* cell = GetCell(x, y);
	if (cell && !cell->HasEntity()) {
		cell->AddEntity(ptr);
		return true;
	}
	return false;
}

bool Board::AddItem(int x, int y, shared_ptr<baseItem> itemHandle)
{
	Cell* cell = GetCell(x, y);
	if (cell && !cell->HasItem()) {
		cell->AddItem(itemHandle);
		return true;
	}
	return false;
}

bool Board::LockCell(int x, int y, int id)
{
	if (GetCell(x, y) == nullptr) {
		return false;
	}
	return GetCell(x, y)->Lock(id);
}

void Board::UnlockCell(int x, int y, int id)
{
	if (GetCell(x, y) == nullptr) {
		return;
	}
	GetCell(x, y)->Unlock(id);
}


