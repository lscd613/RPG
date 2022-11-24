#include "pch.h"
#include "Cell.h"
#include <iostream>
#include "baseItemCreator.h"
Cell::Cell(int hasE):obstacle(hasE), hEntity(0), inPath(0), locked(0), hItem(0), entity(nullptr), itemHandle(-1)
, id(-2) 
{

}
int Cell::HasItem() {
	return hItem;
}
int Cell::HasEntity() {
	return hEntity;
}
int Cell::HasObstacle() {
	return obstacle;
}
int Cell::Islocked() {
	return locked;
}
bool Cell::IsBlocked() {
	if (obstacle || hEntity)
		return true;
	return false;
}
void Cell::SetBlocked(int val) {
	hEntity = val;
}
Entity* Cell::GetEntity() {
	return entity;
}
int Cell::GetItem() {
	return itemHandle;
}
void Cell::AddItem(int itemHandle) {
	auto creator = baseItemCreator::GetInstance();
	if(this->itemHandle == itemHandle || !creator) {
		return;
	}
	auto e = creator->GetItemPointer(itemHandle);
	if (!e) {
		return;
	}
	this->itemHandle = itemHandle;
	hItem = 1;
}
void Cell::AddEntity(Entity* e) {
	if (!e || e == entity) {
		return;
	}
	entity = e;
	hEntity = 1;
}

void Cell::AddEntity(int hndl) {
	/*if (!e || e == entity) {
		return;
	}
	entity = e;
	hEntity = 1;*/
}

Entity* Cell::RemoveEntity() {
	hEntity = 0;
	Entity* temp = entity;
	entity = nullptr;
	return temp;
}
bool Cell::Lock(int _id) {
	if (locked) {
		if (this->id == _id) {
			return true;
		}
		return false;
	}
	locked = 1;
	id = _id;
	return true;

}
void Cell::Unlock(int _id) {
	if (this->id != _id) {
		return;
	}
	id = -99;
	locked = 0;
}
int Cell::GetID() {
	return id;
}
int Cell::Pick() {
	int tmp = itemHandle;
	itemHandle = -1;
	if (tmp != -1) {
		std::cout << "CellÒÆ³ýÎïÆ·" << std::endl;
	}
	return tmp;
}

