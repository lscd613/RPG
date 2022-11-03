#include "pch.h"
#include "Fight.h"
#include "Data.h"
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
		if (cell && cell->HasEntity() && cell->GetEntity()
			&& self.GetType() != cell->GetEntity()->GetType()
			&& (cell->GetEntity()->GetType() == role || cell->GetEntity()->GetType() == monster)) {
			enermy = cell->GetEntity();
			self.GetStatus().moveStatus = attack;
			self.GetProperty().direction = i;
			return true;
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

