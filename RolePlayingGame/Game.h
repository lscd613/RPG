#pragma once
#include "common.h"
#include <iostream>
#include "Renderer.h"
#include "Map.h"
#include "Monster.h"
#include <vector>
#include "baseItemCreator.h"
#include "FightEntityManager.h"
class Game
{
private:
	Camera camera;
	Role *role;
	Renderer renderer;
	MOUSEMSG msg;
	Map map;
	baseItemCreator *itemCreator;
	FightEntityManager* fightEntityManager;
public:
	Game();
	~Game();
	int Loop();
};

