#include "pch.h"
#include "MoveBase.h"

MoveBase::MoveBase(Entity * e = nullptr)
	:entity(e)
{

}

MoveBase::~MoveBase()
{

}

void MoveBase::MoveOneCell(Board& b)
{
	if (!entity) {
		return;
	}
	position& pos = entity->GetPos();
	status& stat = entity->GetStatus();
	property& prop = entity->GetProperty();

	int deltaX = (int)((nextPos[0] + 1 / 2.0) * ::g_data.gridWidth - pos.x);
	int deltaY = (int)((nextPos[1] + 1 / 2.0) * ::g_data.gridHeight - pos.y);
	if (deltaX == 0 && deltaY == 0) {
		stat.moveStatus = stay;

		return;
	}
	if (abs(deltaX) > abs(deltaY)) {
		pos.x += deltaX / abs(deltaX) * prop.speed;
		prop.direction = directHash[directX * deltaX / abs(deltaX)];

	}
	else if (abs(deltaX) < abs(deltaY)) {
		pos.y += deltaY / abs(deltaY) * prop.speed;
		prop.direction = directHash[directY * deltaY / abs(deltaY)];
	}
	else {
		pos.x += (deltaX / abs(deltaX)) * prop.speed;
		pos.y += (deltaY / abs(deltaY)) * prop.speed;
		prop.direction = directHash[directX * deltaX / abs(deltaX) + directY * deltaY / abs(deltaY)];
	}
	stat.moveStatus = run;
}

bool MoveBase::ReadyToMove() {
	if (!entity) {
		return false;
	}
	position& pos = entity->GetPos();
	return pos.x == (nextPos[0] + 1 / 2.0) * g_data.gridWidth
		&& pos.y == (nextPos[1] + 1 / 2.0) * g_data.gridHeight;
}

void MoveBase::ClearPath(Board& b)
{
	if (!entity) {
		return;
	}
	for (auto i : path)
	{
		auto cell = b.GetCell(i.first, i.second);
		if (cell) {
			cell->inPath = 0;
		}
		
	}
	b.UnlockCell(nextPos[0], nextPos[1],entity->GetID());
	path.clear();
}

std::vector<pair<int, int>>& MoveBase::GetPath()
{
	return path;
}

Entity* MoveBase::GetEntity()
{
	return entity;
}

void MoveBase::Start()
{
	if (!entity) {
		return;
	}
	position& pos = entity->GetPos();
	moveLocker = 0;
	prePos[0] = nextPos[0] = pos.grid_x;
	prePos[1] = nextPos[1] = pos.grid_y;
}

int MoveBase::GetLocker()
{
	return moveLocker;
}

std::vector<int>& MoveBase::GetNextPos()
{
	return nextPos;
}

std::vector<int>& MoveBase::GetPrePos()
{
	return prePos;
}


void MoveBase::UpdatePath(Board& b) {
	if (!entity) {
		return;
	}
	position& pos = entity->GetPos();
	//��֤�����ƶ�ԭ����
	if (ReadyToMove()) {
		if (!path.empty()) {
			nextPos[0] = path.back().first;
			nextPos[1] = path.back().second;
			//����Ŀ��λ��
			int deltaX = (int)((pos.grid_x + 1 / 2.0) * ::g_data.gridWidth - pos.x);
			int deltaY = (int)((pos.grid_y + 1 / 2.0) * ::g_data.gridHeight - pos.y);
			if (pos.grid_x == nextPos[0] && pos.grid_y == nextPos[1]) {
				//�������Ƴ���һ��
				Cell* preCell, * curCell;
				preCell = b.GetCell(prePos[0], prePos[1]);
				curCell = b.GetCell(nextPos[0], nextPos[1]);
				if (!preCell || !curCell) {
					return;
				}
				preCell->RemoveEntity();
						
				curCell->inPath = 0;
				path.pop_back();
				b.UnlockCell(nextPos[0], nextPos[1],entity->GetID());
				//prePosָ��ǰλ��
				prePos[0] = nextPos[0];
				prePos[1] = nextPos[1];
				//��ȡpath��һλ��
				if (!path.empty()) {
					nextPos[0] = path.back().first;
					nextPos[1] = path.back().second;
				}
				else {
					nextPos[0] = pos.grid_x;
					nextPos[1] = pos.grid_y;
				}
			}
		}
		//���Խ��ܼ������
		moveLocker = 0;
		//�������뵱ǰ��
		Cell* cell = b.GetCell(prePos[0], prePos[1]);
		if (cell && !cell->HasEntity()) {
			cell->AddEntity(entity);
			
		}
	}
	//δ��ɵ����ƶ�ʱ�����ᱻ��������������
	else {
		moveLocker = 1;
		//ͬʱҲ�����޸�·�ߣ�ֱ��return
		return;
	}
	auto cell = b.GetCell(nextPos[0], nextPos[1]);
	//��һ��Ϊ�Ƿ�λ����ֹͣ�ڵ�ǰλ��
	if (cell && !b.IsEmptyCell(nextPos[0], nextPos[1])
		|| (!b.LockCell(nextPos[0], nextPos[1], entity->GetID())
		&& cell->Islocked() )) {
		ClearPath(b);
		nextPos[0] = prePos[0];
		nextPos[1] = prePos[1];
	}

}