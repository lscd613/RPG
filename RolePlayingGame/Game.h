#pragma once
#include "common.h"
#include <iostream>
#include "Renderer.h"
#include "Map.h"
#include "Monster.h"
#include <vector>
#include "baseItemCreator.h"
class Game
{
private:
	Camera camera;
	Role *role;
	vector<FightEntity*> pFightEntities;
	Renderer renderer;
	MOUSEMSG msg;
	Map map;
	baseItemCreator *itemCreator;
public:
	Game();
	~Game();
	int Loop();
	int Init();
	void RunEntities();
	void CreateMonster();
};

