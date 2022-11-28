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
* �������л�ȡ��ָ��ľ���ظ����ã�û�п��þ���������
* �ٴ����µľ��
*/
int FightEntityCreator::GetEmptyIndex() {
	int tmp = index;
	//�ӵ�ǰλ��������Ѱ
	while (tmp < ptrVec.size() && ptrVec[tmp] != NULL) {
		tmp++;
	}
	//�޿��þ��,���ͷ��ʼ��
	int hasEmpty = 0;
	if (tmp >= ptrVec.size()) {
		for (tmp = 0; tmp < index; tmp++) {
			if (ptrVec[tmp] == NULL) {
				index = tmp;
				hasEmpty = 1;
				break;
			}
		}
		//���κο��þ���������ݾ������
		if (!hasEmpty) {
			index = (int)ptrVec.size();
			ptrVec.resize(ptrVec.size() * 2);
		}
	}
	else {
		index = tmp;
	}
	cout << "++��� ��" << index << endl;
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
	cout << "--��� ��" << handle << endl;
	return 0;
}
