#pragma once
#include "Entity.h"
#include "Fight.h"
#include "Board.h"
#include <vector>
class FightEntity :
	public Entity
{
protected:
	Fight fight;
	int _isDead = 0;
	int deadInterval =2500;
	decltype(GetTickCount()) deadTimeIndex = GetTickCount();
public:
	FightEntity(int id);
	bool DeadJudge(Board& b);
	int IsDead();
public:
	virtual void Run(MOUSEMSG& msg, Board& b) = 0;
	virtual void Attack(Board& b);
	virtual void Release(Board& b) = 0;
};

