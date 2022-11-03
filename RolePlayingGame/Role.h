#pragma once
#include <time.h>
#include "common.h"
#include <list>
#include <map>
#include <unordered_map>
#include "FightEntity.h"
#include "Board.h"
#include "MoveController.h"
#include "Fight.h"
#include "Weapon.h"
#include "Package.h"
class Role : public FightEntity
{
private:
	MoveController _moveController;
	Weapon *_weapon;
	Package _package;
public:

public:
	Role(int id);
	~Role();
	void Move(MOUSEMSG& msg, Board& b);
	Package& GetPackage();
public:
	virtual void Attack(Board& b);
	virtual void Render(int centerX, int centerY);
	virtual void Run(MOUSEMSG& msg, Board& b);
	virtual void Release(Board& b);
};

