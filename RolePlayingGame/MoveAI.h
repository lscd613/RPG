#pragma once
#include "MoveBase.h"
#include <vector>
class MoveAI
{
	
	int centerX, centerY;
	int radius = 6;
	decltype(GetTickCount()) timeIndex = GetTickCount();
	int baseInterval = 3500;
	int intervalRange = 6000;
	int realInterval = baseInterval;
	int attackRadius = 4;
protected:
	bool IsOutOfMovingRange(int, int);
public:
	MoveBase base;
public:
	MoveAI(Entity* entity);
	~MoveAI();
	void GetRandomPos(Board& b);
	void Move(Board& b);
	void UnlockNextPos(Board& b, int id) {
		auto& pos = base.GetNextPos();
		if (pos.size() < 2) {
			return;
		}
		auto cell = b.GetCell(pos[0], pos[1]);
		if (cell) {
			cell->Unlock(id);
		}
	}
public:
	virtual void Start();
	virtual void UpdatePath(Board& b);
	
};

