#include "pch.h"
#include "MoveController.h"
#include "AStar.h"
#include "Entity.h"
#include <iostream>

void MoveController::Move(MOUSEMSG &msg, Board &b)
{
	if (!base.GetEntity())
		return;

	base.UpdatePath(b);
	HandleKeyboard(b);
	HandleMouse(msg, b);
	UpdateGridPos(base.GetEntity()->GetPos());
	base.MoveOneCell(b);
}



void MoveController::HandleMouse(MOUSEMSG& msg, Board& b)
{
	Entity* entity = base.GetEntity();
	if (!entity) {
		return;
	}
	position& pos = entity->GetPos();
	UpdateGridPos(pos);
	if (base.GetLocker()) {
		return;
	}
	while (MouseHit()) //判断是否有鼠标消息
	{
		msg = GetMouseMsg(); // 取出一个鼠标消息
		if ((int)((GetTickCount() - timeIndex)) < keyBoardInterval) {
			return;
		}
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:// 左键按下			
			clickIndex = TRUE;			
			break;
		case WM_LBUTTONUP:// 左键松开	
			if (clickIndex)
			{			
				double deltaX = msg.x - g_data.cameraCenter[0];
				double deltaY = msg.y - g_data.cameraCenter[1];

				clickPos[0] = pos.grid_x + (int)(deltaX / ::g_data.gridWidth + deltaX / (2 * abs(deltaX)));
				clickPos[1] = pos.grid_y + (int)(deltaY / ::g_data.gridHeight + deltaY / (2 * abs(deltaY)));
				//点击位置合法则重新规划路线，清空path
				if (b.IsNoObstackleCell(clickPos[0], clickPos[1]) && !base.GetLocker()) {
					vector<int> temp = { clickPos[0],clickPos[1] };
					base.ClearPath(b);
					AStar astar;
					auto& lastPos = base.GetNextPos();
					auto& path = base.GetPath();
					path = astar.GetPath(pos, temp, b);
					path.push_back({ lastPos[0] ,lastPos[1] });
					timeIndex = GetTickCount();
				}
				clickIndex = FALSE;			//重置标记
			}
			break;
		default:
			break;
		}
	}
}

void MoveController::HandleKeyboard(Board& b)
{
	Entity* entity = base.GetEntity();
	if (!entity) {
		return;
	}
	position& pos = entity->GetPos();
	UpdateGridPos(pos);
	if (base.GetLocker()) {
		return;
	}
	int tempX = pos.grid_x, tempY = pos.grid_y;

	if (IsKeyDown('S'))
	{
		tempY = pos.grid_y + 1;
	}
	else if (IsKeyDown('W'))
	{
		tempY = pos.grid_y - 1;
	}
	if (IsKeyDown('A'))
	{
		tempX = pos.grid_x - 1;
	}
	else if (IsKeyDown('D'))
	{
		tempX = pos.grid_x + 1;
	}
	if (tempX == pos.grid_x && tempY == pos.grid_y) {
		return;
	}
	if (b.IsEmptyCell(tempX, tempY)
		&& (int)(GetTickCount() - timeIndex) > keyBoardInterval) {
		timeIndex = GetTickCount();
		base.ClearPath(b);
		base.GetPath().push_back({tempX, tempY});
	}
}

void MoveController::Start()
{
	base.Start();
}








MoveController::MoveController(Entity* e = nullptr):base(e)
{
	
}

MoveController::~MoveController()
{
}
