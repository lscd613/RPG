#include "pch.h"
#include "MoveController.h"
#include "AStar.h"
#include "Entity.h"
#include <iostream>
#include "FightEntityCreator.h"
void MoveController::Move(MOUSEMSG& msg, Board& b)
{

	auto e = base.GetEntity();
	if (!e) {
		return;
	}
	position& pos = e->GetPos();
	base.UpdatePath(b);
	HandleKeyboard(b);
	HandleMouse(msg, b);
	UpdateGridPos(pos);
	base.MoveOneCell(b);
}



void MoveController::HandleMouse(MOUSEMSG& msg, Board& b)
{
	auto e = base.GetEntity();
	if (!e) {
		return;
	}
	position& pos = e->GetPos();
	UpdateGridPos(pos);
	if (base.GetLocker()) {
		return;
	}
	while (MouseHit()) //�ж��Ƿ��������Ϣ
	{
		msg = GetMouseMsg(); // ȡ��һ�������Ϣ
		if ((int)((GetTickCount() - timeIndex)) < keyBoardInterval) {
			return;
		}
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:// �������			
			clickIndex = TRUE;			
			break;
		case WM_LBUTTONUP:// ����ɿ�	
			if (clickIndex)
			{			
				double deltaX = msg.x - g_data.cameraCenter[0];
				double deltaY = msg.y - g_data.cameraCenter[1];

				clickPos[0] = pos.grid_x + (int)(deltaX / ::g_data.gridWidth + deltaX / (2 * abs(deltaX)));
				clickPos[1] = pos.grid_y + (int)(deltaY / ::g_data.gridHeight + deltaY / (2 * abs(deltaY)));
				//���λ�úϷ������¹滮·�ߣ����path
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
				clickIndex = FALSE;			//���ñ��
			}
			break;
		default:
			break;
		}
	}
}

void MoveController::HandleKeyboard(Board& b)
{
	auto e = base.GetEntity();
	if (!e) {
		return;
	}
	position& pos = e->GetPos();
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






MoveController::MoveController(position& pos):base(pos)
{
	
}

MoveController::~MoveController()
{

}
