#pragma once
#include "Items.h"
#include "Weapon.h"
#include "Board.h"
#include <queue>
#include <map>
#include <vector>
#include "baseItem.h"
#include <memory>
struct itemRequest {
	int gridX;
	int gridY;
	int typeId;
};

class baseItemCreator
{
public:
	std::queue<itemRequest> _queue;
private:

private:
	baseItemCreator();
	~baseItemCreator();
	void GetAllEmptyPos(int x, int y, int total,std::vector<pair<int,int>>&, Board& b);
	void GetEmptyPos(int x, int y, int& total, std::vector<pair<int, int>>&, Board& b);
	
public:
	void Run(Board &);

	static baseItemCreator* GetInstance() {
		static baseItemCreator single;
		return &single;
	}
};

