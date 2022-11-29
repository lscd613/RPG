#include "pch.h"
#include "FightEntityManager.h"
#include <vector>
#include "Role.h"
#include <memory>
#include "Data.h"

void FightEntityManager::Init()
{
	creator = FightEntityCreator::GetInstance();
	if (!creator) {
		return;
	}
	//添加人物	
	shared_ptr<Role> role = make_shared<Role>(id++);
	this->role = role;
	role->SetEntity(role);
	board.AddEntity(role->GetPos().grid_x, role->GetPos().grid_y, role);
	ptrVec.push_back(role);

	cout << "//添加人" << role.use_count() << endl;
	
	

	////添加怪
	//std::vector<int> posVec{ 33,17 ,16,13,19,20,26,27,25,27 };
	//for (int i = 0; i < posVec.size(); i += 2) {
	//	shared_ptr<Monster> m = make_shared<Monster>(1,id++, posVec[i], posVec[i + 1]);
	//	if (m) {
	//		board.AddEntity(posVec[i], posVec[i + 1], m);
	//		ptrVec.push_back(m);
	//	}
	//}
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
			shared_ptr<Monster> m = make_shared<Monster>(1, id++, posVec[i], posVec[i + 1]);
			m->SetEntity(m);
			if (m) {
				cout << "m: " << m.use_count() << endl;
				if (!board.AddEntity(posVec[i], posVec[i + 1], m)) {
					return;
				}
				ptrVec.push_back(m);
				cout << "m: " << m.use_count() << endl;
			}	
		}
		createTimeIndex = GetTickCount();
		for (auto& ptr : ptrVec)
		{
			if (ptr) {
				cout << "mCnt: " << ptr.use_count() << endl;
			}
		}
	}
	
}

shared_ptr<Role> FightEntityManager::GetRole()
{
	return role.lock();
}

void FightEntityManager::RunEntities(MOUSEMSG &msg, Board& board)
{
	for (auto &ptr: ptrVec)
	{
		if (ptr) {
			if (ptr->IsDead())
			{
				ptr->Release(board);
				ptr.reset();
			}
			else {
				ptr->Run(msg, board);
			}
		}
	}
}


FightEntityManager::FightEntityManager(Board& b):board(b),id(0)
{
	Init();
}



