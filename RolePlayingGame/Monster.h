#pragma once
#include "FightEntity.h"
#include <map>
#include <vector>
#include "common.h"
#include <list>
#include "MoveAI.h"
class Monster :
    public FightEntity
{
	MoveAI moveAI;
	int isSendItem = 0;
public:	
    Monster(int typeID,int id,int x,int y);
    ~Monster();
	void AutoMove(Board & b);
	void SendItemRequest();
public:
	virtual void Run(MOUSEMSG& msg, Board& b);
	virtual void Release(Board& b);
};

