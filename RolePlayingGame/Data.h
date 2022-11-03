#pragma once
#ifndef DATA_H
#define DATA_H


#include <fstream>
#include <vector>

#define STATE_NUM 4
#define DIRECT 8
#define SAFE_DELETE(ptr) do{delete ptr; ptr = NULL;} while(false);
static int ptrCount = 0;
struct Data
{
	int cameraBlockWidth = 3, cameraBlockHeight = 3;
	int renderBlockWidth = 5, renderBlockHeight = 5;
	int imgWidth = 320, imgHeight = 180;
	int screenWidth = cameraBlockWidth * imgWidth, 
		screenHeight = cameraBlockHeight * imgHeight;//���ڿ��
	int gridWidth = 40, gridHeight = 40;
	int mapWidth = 7, mapHeight = 7;
	int indexWidth = imgWidth / gridWidth,
		indexHeight = imgHeight / gridHeight;
	int mapGridWidth = mapWidth * indexWidth,
		mapGridHeight = mapHeight * indexHeight;
	int screenGridWidth = cameraBlockWidth * indexWidth,
		screenGridHeight = cameraBlockHeight * indexHeight;
	int cameraCenter[2] = {480, 270};
	int index(int x, int y) {
		return x + y * indexWidth * mapWidth;
	}
	//�ඨ���в��ܳ�ʼ����Ա������Ҫ�ó�ʼ���б�
	int x[DIRECT] = {0,1,-1,1,-1,1,-1,0};
	int y[DIRECT] = {-1,-1,-1,0,0,1,1,1};
};
extern Data g_data;

enum entityType {
	role,
	monster,
	weapon,
	item
};
enum direct
{
	up,
	rightup,
	leftup,
	right,
	left,
	rightdown,
	leftdown,
	down,
};
enum moveStatus
{
	stay,
	run,
	attack,
	dead
};

struct position {
	int x = -1;
	int y = -1;
	int grid_x = -1;
	int grid_y = -1;
};

struct property {
	int HP = 100;
	int max_HP = HP;
	int damage = 5;
	int width = -1, height = -1;
	int speed = 5;
	int direction = direct::down;
	void SetSpeed(int s) {
		speed = s;
	}
	void SetWidth(int w) {
		width = w;
	}
	void SetHeight(int h) {
		height = h;
	}
	void SetDirection(direct d) {
		direction = d;
	}
	void SetMaxHP(int d) {
		max_HP = d;
		HP = d;
	}
	void SetDamage(int d) {
		damage = d;
	}
};
struct status {
	moveStatus moveStatus = stay;
};

void UpdateGridPos(position& pos);

template<typename T>
inline void RandVector(std::vector<T>& vec, int start, int end)
{
	if (vec.empty())
		return;
	if (start <= end && start >= 0 && end < vec.size()) {
		for (int i = start; i <= end; i++) {
			int r1 = (rand() % (end - start + 1)) + start;
			int r2 = (rand() % (end - start + 1)) + start;
			std::swap(vec[r1], vec[r2]);
		}
	}

/*
	����һ����Χ�������ͨ�ñ�ʾ��ʽ
	Ҫȡ��[a, b)�����������ʹ��(rand() % (b - a)) + a;
	Ҫȡ��[a, b]�����������ʹ��(rand() % (b - a + 1)) + a;
	Ҫȡ��(a, b]�����������ʹ��(rand() % (b - a)) + a + 1;
	ͨ�ù�ʽ:a + rand() % n�����е�a����ʼֵ��n�������ķ�Χ��
	Ҫȡ��a��b֮��������������һ�ֱ�ʾ��a + (int)b * rand() / (RAND_MAX + 1)��
	Ҫȡ��0��1֮��ĸ�����������ʹ��rand() / double(RAND_MAX)��
*/
}

#endif // !DATA_H


