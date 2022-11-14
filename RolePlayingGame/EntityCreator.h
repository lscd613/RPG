#pragma once


#include <queue>
#include <map>
#include <vector>

#include "Entity.h"
#include "Board.h"
class EntityCreator
{
public:
	
private:
	std::vector<int> handleVec;
private:
	EntityCreator();
	~EntityCreator();

public:
	void Run(Board&);
	baseItem* GetPointer(int handler);
	static EntityCreator* GetInstance() {
		static EntityCreator single;
		return &single;
	}
};

