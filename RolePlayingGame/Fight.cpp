#include "pch.h"
#include "Fight.h"
#include "Data.h"
#include "FightEntityCreator.h"
Fight::Fight(Entity & e) :self(e),enermy(nullptr)
{
	
}

void Fight::Attack(Board& b)
{
	if ((self.GetMoveStatus() == attack || Ready(b))
		&&enermy != nullptr) {
		if ((int)(GetTickCount() - timeIndex) > attackInterval) {
			enermy->GetProperty().HP -= self.GetProperty().damage;
			timeIndex = GetTickCount();
		}
	}
}

bool Fight::Ready(Board& b)
{
	if (self.GetMoveStatus() != moveStatus::stay) {
		return false;
	}
	auto gridX = self.GetPos().grid_x,
		gridY = self.GetPos().grid_y;
	//检测四周是否有敌人
	for (int i = 0; i < 8; i++) {
		int _x = gridX + g_data.x[i];
		int _y = gridY + g_data.y[i];
		auto cell = b.GetCell(_x, _y);
		if (cell && cell->HasEntity()){
			FightEntityCreator* f_creator = FightEntityCreator::GetInstance();
			if (f_creator) {
				auto entity = f_creator->GetPointer(cell->GetEntity());
				if (entity
					&& self.GetType() != entity->GetType()
					&& (entity->GetType() == role || entity->GetType() == monster)) {
					enermy = entity;
					self.GetStatus().moveStatus = attack;
					self.GetProperty().direction = i;
					return true;
				}	
			}
		}
	}
	return false;
}

void Fight::SetEnermy(Entity *e)
{
	if (!e) {
		return;
	}
	enermy = e;
}

