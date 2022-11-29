#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "Board.h"
#include "common.h"
#include "Data.h"
#include <memory>
class MoveBase
{
protected:
	vector<int> prePos = { -1,-1 };
	vector<int> nextPos = { -1,-1 };
	int moveLocker = 0;
	std::vector<pair<int, int>> path;
	int directX = 1, directY = 5;
	std::unordered_map<int, direct> directHash = {
		{directX,direct::right} ,{-directX,direct::left} ,
		{directY,direct::down} , {-directY,direct::up} ,
		{directX + directY,direct::rightdown} , {directX - directY,direct::rightup} ,
		{-directX + directY,direct::leftdown} , {-directX - directY,direct::leftup} };
	 
	std::weak_ptr<Entity> e;
public:
	
	MoveBase(position& pos);
	~MoveBase();
	void MoveOneCell(Board& b);
	bool ReadyToMove();
	void ClearPath(Board& b);
	std::vector<pair<int, int>>& GetPath();
	shared_ptr<Entity> GetEntity();
	void UpdatePath(Board& b);
	void SetEntity(shared_ptr<Entity>);
	int GetLocker();
	std::vector<int>& GetNextPos();
	std::vector<int>& GetPrePos();
};

