#include "pch.h"
#include "Entity.h"
#include <fstream>
#include <iostream>
Entity::Entity(int _id):sprite(pos,stat.moveStatus,prop),id(_id) {
	
}

Entity::~Entity()
{

}

int Entity::GetMoveStatus()
{
	return stat.moveStatus;
}

int Entity::GetID()
{
	return id;
}

position& Entity::GetPos()
{
	UpdateGridPos(pos);
	return pos;
}

void Entity::SetPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
	UpdateGridPos(pos);
}

void Entity::SetGridPos(int x, int y)
{
	pos.grid_x = x;
	pos.grid_y = y;

	pos.x = (int)((x + 1 / 2.0) * g_data.gridWidth);
	pos.y = (int)((y + 1 / 2.0) * g_data.gridHeight);
}

void Entity::Render(int centerX, int centerY)
{
	sprite.Render(centerX, centerY);
}
entityType Entity::GetType()
{
	return type;
}




property& Entity::GetProperty() {
	return prop;
}
status& Entity::GetStatus() {
	return stat;
}

std::string Entity::GetName()
{
	return name;
}
