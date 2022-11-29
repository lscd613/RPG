#pragma once
#include "common.h"
#include <list>
#include "Entity.h"
#include <iostream>
#include "baseItem.h"
using namespace std;
class Cell
{
private:
	int obstacle;
	int hEntity;
	int hItem;
	int locked;
	int id;
	shared_ptr<Entity> entityPtr;
	shared_ptr<baseItem> item;
public:
	int inPath;
	Cell(int hasE = 0);
	int HasItem();
	int HasEntity();
	int HasObstacle();
	int Islocked();
	bool IsBlocked();
	void SetBlocked(int val);
	shared_ptr<Entity> GetEntity();
	shared_ptr<baseItem> GetItem();
	void AddItem(shared_ptr<baseItem> itemHandle);
	void AddEntity(shared_ptr<Entity> &ptr);
	
	shared_ptr<Entity>  RemoveEntity();
	bool Lock(int _id);
	void Unlock(int _id);
	int GetID();
	shared_ptr<baseItem> Pick();
};

