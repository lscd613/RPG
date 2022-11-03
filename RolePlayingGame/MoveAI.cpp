#include "pch.h"
#include "MoveAI.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Data.h"
#include "Role.h"
#include "AStar.h"
bool MoveAI::IsOutOfMovingRange(int x, int y)
{
	if (x >= centerX - radius && x <= centerX + radius
		&& y >= centerY - radius && y <= centerY + radius) {
		return false;
	}
	return true;
}

MoveAI::MoveAI(Entity * entity) : base(entity)
{
	
}

MoveAI::~MoveAI()
{
}

void MoveAI::GetRandomPos(Board & b)
{
	if (!base.GetPath().empty() || base.GetEntity() == nullptr)
		return;
	if ((int)(GetTickCount() - timeIndex) < realInterval) {
		return;
	}
	Entity* entity = base.GetEntity();
	realInterval = baseInterval + rand() % intervalRange;
	timeIndex = GetTickCount();
	
	int x[8] = { -1,0,1,-1,1,-1,0,1 };
	int y[8] = { -1,-1,-1,0,0,1,1,1 };

	//随机打乱邻近八个位置
	vector<int> order = { 0,1,2,3,4,5,6,7 };
	RandVector(order, 0, (int)order.size() - 1);

	//遍历找到符合要求的位置就加入path
	auto gridX = entity->GetPos().grid_x,
		gridY = entity->GetPos().grid_y;
	for (auto i : order) {
		int _x = gridX + x[i];
		int _y = gridY + y[i];
		if (b.IsEmptyCell(_x, _y)) {
			base.GetPath().push_back({ _x,_y });
			break;
		}
	}
}

void MoveAI::Move(Board & b)
{
	GetRandomPos(b);
	UpdatePath(b);
	base.MoveOneCell(b);
}

void MoveAI::Start()
{
	base.Start();
	Entity* entity = base.GetEntity();
	if (entity) {
		centerX = entity->GetPos().grid_x;
		centerY = entity->GetPos().grid_y;
	}
}

void MoveAI::UpdatePath(Board & b)
{
	if (!base.GetEntity())
		return;
	Entity* entity = base.GetEntity();
	UpdateGridPos(entity->GetPos());
	base.UpdatePath(b);

	if (base.GetLocker() || !base.GetPath().empty()) {
		return;
	}

	auto &path = base.GetPath();
	int x = entity->GetPos().grid_x;
	int y = entity->GetPos().grid_y;
	for (int i = x - attackRadius; i <= x + attackRadius; i++) {
		for (int j = y - attackRadius; j <= y + attackRadius; j++) {
			auto cell = b.GetCell(i, j);
			if (cell) {
				if (cell->HasEntity() && dynamic_cast<Role*>(cell->GetEntity()) != nullptr){
					//点击位置合法则重新规划路线，清空path
					vector<int> temp = { i,j };
					base.ClearPath(b);
					AStar astar;
					path = astar.GetPath(entity->GetPos(), temp, b);
				}
			}
		}
	}
}
