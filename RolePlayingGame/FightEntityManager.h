#pragma once
#include "FightEntityCreator.h"
#include "Board.h"
#include "Monster.h"
#include "Role.h"
class FightEntityManager
{
private:
	FightEntityCreator* creator;
	Board& board;
	std::vector<std::shared_ptr<FightEntity>> ptrVec;
	int id;
	weak_ptr<Role> role;
	int createTimeIndex = GetTickCount();
private:
	void Init();
	void RunEntities(MOUSEMSG& msg,Board& board);
public:
	FightEntityManager(Board& board);
	void Run(MOUSEMSG& msg,Board& board);
	void CreateMonster();
	shared_ptr<Role> GetRole();
};

