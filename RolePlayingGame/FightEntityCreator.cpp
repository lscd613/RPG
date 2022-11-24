#include "pch.h"
#include "FightEntityCreator.h"
#include "Monster.h"
#include "Role.h"

FightEntityCreator::FightEntityCreator()
{
}

FightEntityCreator::~FightEntityCreator()
{
	for (auto ptr : ptrVec) {
		SAFE_DELETE(ptr);
	}
}

int FightEntityCreator::CreateMonster(int typeID, int x, int y)
{
	int id = (int)ptrVec.size();
	Monster* m = new Monster(typeID, id, x, y);
	if (m) {
		ptrVec.push_back(m);
		return id;
	}
	return -1;
}

void FightEntityCreator::Run(Board&)
{
}

FightEntity* FightEntityCreator::GetPointer(int handle)
{
	if (handle < 0 || handle >= ptrVec.size()) {
		return nullptr;
	}
	return ptrVec[handle];
}

int FightEntityCreator::ReleaseMonster(int handle)
{
	if (handle < 0 || handle >= ptrVec.size()) {
		return -1;
	}
	SAFE_DELETE(ptrVec[handle]);
	return 0;
}


//void Game::RunEntities()
//{
//	for (auto e = pFightEntities.begin(); e != pFightEntities.end();)
//	{
//		if (*e) {
//			if ((*e)->IsDead())
//			{
//				(*e)->Release(map.GetBoard());
//				SAFE_DELETE(*e);
//				*e = nullptr;
//				e = pFightEntities.erase(e);
//			}
//			else {
//				(*e)->Run(msg, map.GetBoard());
//				e++;
//			}
//		}
//	}
//}
//
//void Game::CreateMonster()
//{
//	if (IsKeyDown('R')) {
//		vector<int> posVec{ 33,17 };
//		for (int i = 0; i < posVec.size(); i += 2) {
//			Monster* m = new Monster(1, i, posVec[i], posVec[i + 1]);
//			if (!m) {
//				break;
//			}
//			auto pos = m->GetPos();
//			if (!map.AddEntity(pos.grid_x, pos.grid_y, m)) {
//				delete m;
//				return;
//			}
//			pFightEntities.push_back(m);
//		}
//	}
//}