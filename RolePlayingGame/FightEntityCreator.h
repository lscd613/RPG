#pragma once


#include <queue>
#include <map>
#include <vector>

#include "FightEntity.h"
#include "Board.h"
class FightEntityCreator
{
public:
	
private:
	std::vector<FightEntity*> ptrVec;
private:
	FightEntityCreator();
	~FightEntityCreator();

public:
	int CreateMonster(int typeID, int x, int y);
	void Run(Board&);
	FightEntity* GetPointer(int handler);
	int ReleaseMonster(int handle);
	static FightEntityCreator* GetInstance() {
		static FightEntityCreator single;
		return &single;
	}
};

