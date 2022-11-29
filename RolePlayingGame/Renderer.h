#pragma once
#include "Role.h"
#include "Camera.h"
#include "Map.h"
#include <map>
#include <string>
#include <vector>
#include "Monster.h"
class Renderer
{

public:
	Renderer();
	~Renderer();
	void Render(shared_ptr<Role> role, Camera & data, Map &map);
};

