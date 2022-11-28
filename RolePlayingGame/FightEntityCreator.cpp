#include "pch.h"
#include "FightEntityCreator.h"
#include "Monster.h"
#include "Role.h"

FightEntityCreator::FightEntityCreator():ptrVec(vector<FightEntity*>(1,NULL)),index(0)
{
	
}

FightEntityCreator::~FightEntityCreator()
{
	for (auto ptr : ptrVec) {
		SAFE_DELETE(ptr);
	}
}

int FightEntityCreator::CreateMonster(int typeID, int x, int y)
{
	int handle = GetEmptyIndex();
	Monster* m = new Monster(typeID, handle, x, y);
	if (!m) { return -1; }
	ptrVec[handle] = m;
	return handle;
}

int FightEntityCreator::CreateRole()
{
	int handle = GetEmptyIndex();
	Role* m = new Role(handle);
	if (!m) { return -1; }
	ptrVec[handle] = m;
	return handle;
}

/*
* 从容器中获取空指针的句柄重复利用，没有可用句柄的情况下
* 再创建新的句柄
*/
int FightEntityCreator::GetEmptyIndex() {
	int tmp = index;
	//从当前位置往后搜寻
	while (tmp < ptrVec.size() && ptrVec[tmp] != NULL) {
		tmp++;
	}
	//无可用句柄,则从头开始找
	int hasEmpty = 0;
	if (tmp >= ptrVec.size()) {
		for (tmp = 0; tmp < index; tmp++) {
			if (ptrVec[tmp] == NULL) {
				index = tmp;
				hasEmpty = 1;
				break;
			}
		}
		//无任何可用句柄，则扩容句柄容器
		if (!hasEmpty) {
			index = (int)ptrVec.size();
			ptrVec.resize(ptrVec.size() * 2);
		}
	}
	else {
		index = tmp;
	}
	cout << "++句柄 ：" << index << endl;
	return index++;
}

FightEntity* FightEntityCreator::GetPointer(int handle)
{
	if (handle < 0 || handle >= ptrVec.size()) {
		return nullptr;
	}
	return ptrVec[handle];
}

int FightEntityCreator::Release(int handle)
{
	if (handle < 0 || handle >= ptrVec.size()) {
		return -1;
	}
	SAFE_DELETE(ptrVec[handle]);
	cout << "--句柄 ：" << handle << endl;
	return 0;
}
