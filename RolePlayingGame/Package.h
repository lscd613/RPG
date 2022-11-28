#pragma once
#include <vector>
#include "baseItem.h"
#include "Board.h"
#include "common.h"
#include "Entity.h"
#include <memory>
class Package
{
public:
	Package(Entity*);
	bool Full() {
		return size == capacity ? true : false;
	}
	bool AddItem(shared_ptr<baseItem> ptr);
	void Run(Board& b);
	void Show();
private:
	Entity* _entity;
	int size = 0;
	int capacity = 6;
	std::vector<shared_ptr<baseItem>> itemsVec;
};

