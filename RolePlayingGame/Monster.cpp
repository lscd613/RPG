#include "pch.h"
#include "Monster.h"
#include "Config.h"
#include <iostream>
#include "Data.h"
#include "baseItemCreator.h"
extern Data g_data;

Monster::Monster(int typeID,int handle,int x, int y):FightEntity(handle), moveAI(nullptr)
{
	
	Config* config = Config::GetInstance();
	assert(config != nullptr);
	CsvReader* reader = nullptr;
	reader = config->GetConfig("monster");
	assert(reader != nullptr);

	int hp, damage;

	reader->GetInt(1, 3, hp);
	reader->GetInt(1, 4, damage);

	SetGridPos(x, y);
	prop.SetWidth(150);
	prop.SetHeight(150);
	prop.SetSpeed(2);
	prop.SetMaxHP(hp);
	prop.SetDamage(damage);
	sprite.SetImages("monster", typeID);
	sprite.SetPaintIntervaltime(300);
	sprite.SetStatOffset(std::vector<int>{ -70, -95, -160, -130 });
	sprite.Set_yOffset(115);
	type = entityType::monster;
	this->typeID = typeID;
	moveAI = new MoveAI(GetPos());
}


Monster::~Monster()
{
	if (moveAI) {
		SAFE_DELETE(moveAI);
	}
	cout << "Monster::~Monster()" << endl;
}

void Monster::AutoMove(Board & b)
{
	moveAI->Move(b);
}

void Monster::SendItemRequest()
{
	itemRequest req;
	req.gridX = pos.grid_x;
	req.gridY = pos.grid_y;
	req.typeId = typeID;
	baseItemCreator* creator = baseItemCreator::GetInstance();
	if (creator) {
		creator->_queue.push(req);
	}
}

void Monster::Run(MOUSEMSG& msg, Board& b)
{
	if (DeadJudge(b)) {
		if (!isSendItem) {
			SendItemRequest();
			moveAI->UnlockNextPos(b, id);
			isSendItem = 1;
		}
		return;
	}
	AutoMove(b);
	Attack(b);
}

void Monster::Release(Board& b)
{
	auto curPos = moveAI->base.GetPrePos();
	auto cell = b.GetCell(curPos[0], curPos[1]);
	if (cell) {
		cell->RemoveEntity();
	}
}

void Monster::SetEntity(shared_ptr<Entity> e)
{
	moveAI->base.SetEntity(e);
}








