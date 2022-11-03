#include "pch.h"
#include "Cell.h"
#include <iostream>
Cell::Cell(int hasE):obstacle(hasE), hEntity(0), inPath(0), locked(0), hItem(0), entity(nullptr), pItem(nullptr)
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
baseItem* Cell::GetItem() {
	return pItem;
}
void Cell::AddItem(baseItem* e) {
	if (!e || e == pItem) {
		return;
	}
	pItem = e;
	hItem = 1;
}
void Cell::AddEntity(Entity* e) {
	if (!e || e == entity) {
		return;
	}
	entity = e;
	hEntity = 1;
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
baseItem* Cell::Pick() {
	baseItem* pTmp = pItem;
	pItem = nullptr;
	if (pTmp != nullptr) {
		std::cout << "CellÒÆ³ýÎïÆ·" << std::endl;
	}
	return pTmp;
}

