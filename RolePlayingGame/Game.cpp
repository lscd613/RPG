#include "pch.h"
#include "Game.h"
#include "Data.h"
#include "Items.h"
extern Data g_data;
Game::Game():role(new Role(-1))
{
	ptrCount++;
	itemCreator = baseItemCreator::GetInstance();
}


Game::~Game()
{
	for (int i = 0; i < pFightEntities.size(); i++) 
	{
		SAFE_DELETE(pFightEntities[i]);
		ptrCount--;
	}
	cout << "ptrCount : "<< ptrCount << endl;
}

int Game::Loop()
{
	srand((unsigned int)time(0));
	//��������
	initgraph(g_data.screenWidth, g_data.screenHeight, SHOWCONSOLE); 
	//��ӹ���
	if (-1 == Init())
		return -1;
	while (true) {
		//ESC���˳���Ϸ
		if (IsKeyDown(VK_ESCAPE)) {
			return 0;
		}
		//�����߼�
		RunEntities();
		if (itemCreator) {
			itemCreator->Run(map.GetBoard());
		}
		CreateMonster();
		//��ͼ		
		renderer.Render(*role, camera, map);
		
		Sleep(15);
	}
	//�رմ���
	closegraph(); 
}

int Game::Init() {

	////��ӹ�
	 
	vector<int> posVec{ 33,17,20,11,22,22};
	for (int i = 0; i < posVec.size(); i += 2) {

		Monster* m = new Monster(1,i,posVec[i], posVec[i + 1]); 
		if (!m) {
			break;
		}
		ptrCount++;
		auto pos = m->GetPos();
		if (!map.AddEntity(pos.grid_x, pos.grid_y, m)) {
			delete m;
			return -1;
		}
		pFightEntities.push_back(m);
	}
	 
	 
	//�������

	if (role) {
		auto pos = role->GetPos();
		if (!map.AddEntity(pos.grid_x, pos.grid_y, role))
			return -1;
		pFightEntities.push_back(role);
	}

	return 0;
}

void Game::RunEntities()
{
	for (auto e = pFightEntities.begin(); e != pFightEntities.end();)
	{
		if (*e) {
			if ((*e)->IsDead())
			{
				(*e)->Release(map.GetBoard());
				SAFE_DELETE(*e);
				ptrCount--;
				*e = nullptr;
				e = pFightEntities.erase(e);
			}
			else {
				(*e)->Run(msg, map.GetBoard());
				e++;
			}
		}
	}
}

void Game::CreateMonster()
{
	if (IsKeyDown('R')) {
		vector<int> posVec{ 33,17 };
		for (int i = 0; i < posVec.size(); i += 2) {
			Monster* m = new Monster(1, i, posVec[i], posVec[i + 1]);
			if (!m) {
				break;
			}
			auto pos = m->GetPos();
			if (!map.AddEntity(pos.grid_x, pos.grid_y, m)) {
				delete m;
				return;
			}
			pFightEntities.push_back(m);
			ptrCount++;
		}
	}
}
