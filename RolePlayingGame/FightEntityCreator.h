#pragma once


#include <queue>
#include <map>
#include <vector>

#include "FightEntity.h"
#include "Board.h"
class FightEntityCreator
{
	
public:
	friend class FightEntityManager;
private:
	std::vector<FightEntity*> ptrVec;
	int index;
private:
	FightEntityCreator();
	~FightEntityCreator();

public:
	int CreateMonster(int typeID, int x, int y);
	int CreateRole();
	int GetEmptyIndex();
	FightEntity* GetPointer(int handler);
	int Release(int handle);
	static FightEntityCreator* GetInstance() {
		static FightEntityCreator single;
		return &single;
	}
};

