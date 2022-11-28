#pragma once
#include "FightEntityCreator.h"
#include "Board.h"
class FightEntityManager
{
private:
	FightEntityCreator* creator;
	Board& board;
	int createTimeIndex = GetTickCount();
private:
	void Init();
	void RunEntities(MOUSEMSG& msg,Board& board);
public:
	FightEntityManager(Board& board);
	void Run(MOUSEMSG& msg,Board& board);
	void CreateMonster();
};

