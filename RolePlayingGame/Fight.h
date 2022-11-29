#pragma once
#include "Entity.h"
#include "Board.h"
class Fight
{
	weak_ptr<Entity> enermy;
	Entity& self;
	decltype(GetTickCount()) timeIndex = GetTickCount();
	int attackInterval = 800;
public:
	Fight(Entity&);
	void Attack(Board&);
	bool Ready(Board&);

};

