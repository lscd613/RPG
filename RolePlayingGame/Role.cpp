#include "pch.h"
#include "Role.h"
#include <iostream>
#include <map>
#include <cmath>
#include "Data.h"
#include "AStar.h"
using namespace std;
extern Data g_data;



Role::Role(int id):FightEntity(id),_moveController(this),_weapon(new Weapon(-99)),_package(this)
{
	ptrCount++;
	SetPos(1140, 660);
	prop.SetWidth(50);
	prop.SetHeight(50);
	prop.SetSpeed(4);
	prop.SetMaxHP(100);
	prop.SetDamage(15);
	sprite.SetImages("role", -1);
	_moveController.Start();
	type = entityType::role;
}

Role::~Role()
{
	if (_weapon) {
		SAFE_DELETE (_weapon);
		ptrCount--;
	}
	cout << "~Role()" << endl;
}

void Role::Move(MOUSEMSG& msg, Board& b)
{
	_moveController.Move(msg, b);
}


Package& Role::GetPackage()
{
	return _package;
}

void Role::Attack(Board & b)
{
	if (IsKeyDown('F')) {
		fight.Attack(b);
	}
}

void Role::Render(int x, int y)
{
	Entity::Render(x, y);
	if (_weapon) {
		_weapon->SetPos(pos.x, pos.y);
		_weapon->GetStatus().moveStatus = stat.moveStatus;
		_weapon->GetProperty().direction = prop.direction;
		_weapon->Render(x, y);
	}
}

void Role::Run(MOUSEMSG & msg, Board & b)
{
	if (DeadJudge(b)) {
		return;
	}
	Move(msg, b);
	Attack(b);
	_package.Run(b);
}

void Role::Release(Board& b)
{
	UpdateGridPos(pos);
	auto cell = b.GetCell(pos.grid_x, pos.grid_y);
	if (cell) {
		cell->RemoveEntity();
	}
}
