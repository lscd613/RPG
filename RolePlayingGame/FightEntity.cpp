#include "pch.h"
#include "FightEntity.h"

FightEntity::FightEntity(int id):Entity(id),fight(*this)
{
}


void FightEntity::Attack(Board & b)
{
	fight.Attack(b);
}

bool FightEntity::DeadJudge(Board & b)
{
	if (prop.HP > 0)
		return false;
	//HP<0之后开始计时
	if (stat.moveStatus != dead) {
		stat.moveStatus = dead;
		
		deadTimeIndex = GetTickCount();
	}
	//计时结束后移除死亡entity，不再绘制尸体
	if (stat.moveStatus == dead
		&& (int)(GetTickCount() - deadTimeIndex) > deadInterval
		&& !_isDead) {
		_isDead = 1;
	}
	return true;
}

int FightEntity::IsDead()
{
	return _isDead;
}
