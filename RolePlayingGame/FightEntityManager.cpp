#include "pch.h"
#include "FightEntityManager.h"
#include <vector>
#include "Role.h"
void FightEntityManager::Init()
{
	creator = FightEntityCreator::GetInstance();
	if (!creator) {
		return;
	}
	//添加人物
	int hdl = creator->CreateRole();
	FightEntity* r = creator->GetPointer(hdl);
	if (r) {
		board.AddEntity(r->GetPos().grid_x, r->GetPos().grid_y, hdl);
	}
	

	//添加怪
	std::vector<int> posVec{ 33,17 ,16,13,19,20,26,27,25,27 };
	for (int i = 0; i < posVec.size(); i += 2) {
		int handle = creator->CreateMonster(1,posVec[i], posVec[i + 1]);
		if (!board.AddEntity(posVec[i], posVec[i + 1], handle)) {
			creator->Release(handle);
		}
	}
}

void FightEntityManager::Run(MOUSEMSG& msg,Board& board)
{
	RunEntities(msg,board);
	CreateMonster();
}

void FightEntityManager::CreateMonster()
{
	if (IsKeyDown('R') && GetTickCount() - createTimeIndex > 300) {
		vector<int> posVec{ 33,17};
		for (int i = 0; i < posVec.size(); i += 2) {
			int handle = creator->CreateMonster(1, posVec[i], posVec[i + 1]);
			if (!board.AddEntity(posVec[i], posVec[i + 1], handle)) {
				creator->Release(handle);
			}
		}
		createTimeIndex = GetTickCount();
	}
}

void FightEntityManager::RunEntities(MOUSEMSG &msg, Board& board)
{
	creator = FightEntityCreator::GetInstance();
	if (!creator) {
		return;
	}
	auto vec = creator->ptrVec;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i]) {
			if ((vec[i])->IsDead())
			{
				vec[i]->Release(board);
				creator->Release(i);
			}
			else {
				(vec[i])->Run(msg, board);
			}
		}
	}
}


FightEntityManager::FightEntityManager(Board& b):board(b)
{
	Init();
}



