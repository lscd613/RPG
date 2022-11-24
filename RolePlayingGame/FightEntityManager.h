#pragma once
#include "FightEntityCreator.h"
#include "Board.h"
class FightEntityManager
{
private:
	FightEntityCreator* creator;
	Board& board;
private:
	void Init();
public:
	FightEntityManager(Board& board);
	
};

