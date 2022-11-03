#pragma once
#include <map>
#include "common.h"
#include "Role.h"
#include "Board.h"
class Camera
{
public:

	void Render(std::map<int, IMAGE*>&, position& pos,Board& b);
	void RenderGrid(const position& pos, Board& b);
	Camera();
	~Camera();
private:
};

