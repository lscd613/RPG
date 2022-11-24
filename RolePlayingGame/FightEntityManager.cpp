#include "pch.h"
#include "FightEntityManager.h"
#include <vector>
void FightEntityManager::Init()
{
	creator = FightEntityCreator::GetInstance();
	if (!creator) {
		return;
	}
	////添加怪
	std::vector<int> posVec{ 33,17,20,11,22,22 };
	for (int i = 0; i < posVec.size(); i += 2) {
		int handle = creator->CreateMonster(1,posVec[i], posVec[i + 1]);
		if (!board.AddEntity(posVec[i], posVec[i + 1], handle)) {
			creator->ReleaseMonster(handle);
		}
	}

	////添加人物
	//if (role) {
	//	auto pos = role->GetPos();
	//	if (!map.AddEntity(pos.grid_x, pos.grid_y, role))
	//		return -1;
	//	pFightEntities.push_back(role);
	//}
}

FightEntityManager::FightEntityManager(Board& b):board(b)
{
	
}
