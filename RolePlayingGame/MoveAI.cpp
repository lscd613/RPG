#include "pch.h"
#include "MoveAI.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Data.h"
#include "Role.h"
#include "AStar.h"
#include "FightEntityCreator.h"
bool MoveAI::IsOutOfMovingRange(int x, int y)
{
	if (x >= centerX - radius && x <= centerX + radius
		&& y >= centerY - radius && y <= centerY + radius) {
		return false;
	}
	return true;
}

MoveAI::MoveAI(position& pos,int hdl) : base(pos, hdl),centerX(pos.grid_x),centerY(pos.grid_y)
{
	
}

MoveAI::~MoveAI()
{
}

void MoveAI::GetRandomPos(Board & b)
{
	if (!base.GetPath().empty())
		return;
	if ((int)(GetTickCount() - timeIndex) < realInterval) {
		return;
	}

	FightEntityCreator* f_creator = FightEntityCreator::GetInstance();
	if (!f_creator) {
		return ;
	}
	auto e = f_creator->GetPointer(base.GetHandle());
	if (!e) {
		return ;
	}
	position& pos = e->GetPos();

	realInterval = baseInterval + rand() % intervalRange;
	timeIndex = GetTickCount();
	
	int x[8] = { -1,0,1,-1,1,-1,0,1 };
	int y[8] = { -1,-1,-1,0,0,1,1,1 };

	//随机打乱邻近八个位置
	vector<int> order = { 0,1,2,3,4,5,6,7 };
	RandVector(order, 0, (int)order.size() - 1);

	//遍历找到符合要求的位置就加入path
	auto gridX = pos.grid_x,
		gridY = pos.grid_y;
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


void MoveAI::UpdatePath(Board & b)
{
	FightEntityCreator* f_creator = FightEntityCreator::GetInstance();
	if (!f_creator) {
		return;
	}
	auto e = f_creator->GetPointer(base.GetHandle());
	if (!e) {
		return;
	}
	position& pos = e->GetPos();

	UpdateGridPos(pos);
	base.UpdatePath(b);

	if (base.GetLocker() || !base.GetPath().empty()) {
		return;
	}

	auto &path = base.GetPath();
	int x = pos.grid_x;
	int y = pos.grid_y;
	int stop = 0;
	for (int i = x - attackRadius; i <= x + attackRadius; i++) {
		for (int j = y - attackRadius; j <= y + attackRadius; j++) {
			auto cell = b.GetCell(i, j);
			if (cell) {
				FightEntityCreator* f_creator = FightEntityCreator::GetInstance();
				if (f_creator) {
					auto enermy = f_creator->GetPointer(cell->GetEntity());
					if (cell->HasEntity() && dynamic_cast<Role*>(enermy) != nullptr) {
						//点击位置合法则重新规划路线，清空path
						vector<int> temp = { i,j };
						base.ClearPath(b);
						AStar astar;
						path = astar.GetPath(pos, temp, b);
						//找到立刻返回
						stop = 1;
						break;
					}
				}
			}
		}
		if (stop) {
			break;
		}
	}
}
