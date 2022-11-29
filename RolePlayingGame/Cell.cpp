#include "pch.h"
#include "Cell.h"
#include <iostream>
#include "baseItemCreator.h"
#include "FightEntityCreator.h"
Cell::Cell(int hasE):obstacle(hasE), hEntity(0), inPath(0), locked(0), hItem(0)
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
shared_ptr<Entity> Cell::GetEntity() {
	return entityPtr;
}
shared_ptr<baseItem> Cell::GetItem() {
	return item;
}
void Cell::AddItem(shared_ptr<baseItem> itemHandle) {
	if(this->item == itemHandle || !itemHandle) {
		return;
	}
	this->item = itemHandle;
	hItem = 1;
}

void Cell::AddEntity(shared_ptr<Entity> &ptr) {
	if (ptr) {
		entityPtr = ptr;
		hEntity = 1;
	}		
}

shared_ptr<Entity> Cell::RemoveEntity() {

	hEntity = 0;
	auto temp = entityPtr;
	entityPtr.reset();
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
shared_ptr<baseItem> Cell::Pick() {
	auto tmp = item;
	item.reset();	
	return tmp;
}

