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
	//HP<0֮��ʼ��ʱ
	if (stat.moveStatus != dead) {
		stat.moveStatus = dead;
		
		deadTimeIndex = GetTickCount();
	}
	//��ʱ�������Ƴ�����entity�����ٻ���ʬ��
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
