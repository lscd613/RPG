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
	int entityHandle;
	int itemHandle;
public:
	int inPath;
	Cell(int hasE = 0);
	int HasItem();
	int HasEntity();
	int HasObstacle();
	int Islocked();
	bool IsBlocked();
	void SetBlocked(int val);
	int GetEntity();
	int GetItem();
	void AddItem(int itemHandle);
	void AddEntity(int handle);
	
	int  RemoveEntity();
	bool Lock(int _id);
	void Unlock(int _id);
	int GetID();
	int Pick();
};

