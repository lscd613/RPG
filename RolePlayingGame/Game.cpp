#include "pch.h"
#include "Game.h"
#include "Data.h"
#include "Items.h"
#include "FightEntityCreator.h"
extern Data g_data;
Game::Game():role(nullptr)
{
	itemCreator = baseItemCreator::GetInstance();
	fightEntityManager = new FightEntityManager(map.GetBoard());
	FightEntityCreator* creator = FightEntityCreator::GetInstance();
	if (creator) {
		role = dynamic_cast<Role*>(creator->GetPointer(0));
	}
}


Game::~Game()
{
	SAFE_DELETE(fightEntityManager);
}

int Game::Loop()
{
	srand((unsigned int)time(0));
	//��������
	initgraph(g_data.screenWidth, g_data.screenHeight, SHOWCONSOLE); 

	while (true) {
		//ESC���˳���Ϸ
		if (IsKeyDown(VK_ESCAPE)) {
			return 0;
		}
		//�����߼�
		
		if (itemCreator) {
			itemCreator->Run(map.GetBoard());
		}
		if (fightEntityManager) {
			fightEntityManager->Run(msg, map.GetBoard());
		}
		
		//��ͼ
		if (role) {
			renderer.Render(*role, camera, map);
		}
		Sleep(15);
	}
	//�رմ���
	closegraph(); 
}