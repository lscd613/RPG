#include "pch.h"
#include "baseItemCreator.h"
#include "CsvReader.h"
#include <iostream>
#include "Config.h"
#include "Items.h"
#include "Data.h"

void stringReplace(std::string& str, std::string str1, std::string str2)
{
	auto pos = str.find(str1);
	while (pos != -1) {
		str.replace(pos, std::string(str1).length(), str2);
		pos = str.find(str1);
	}
}

baseItemCreator::baseItemCreator()
{
}

baseItemCreator::~baseItemCreator()
{
	for (auto &item : pItems) {
		SAFE_DELETE(item);
		ptrCount--;
	}
}

int squareSum(int n) {
	int sum = 0;
	for (int i = 3; i <= n; i++) {
		sum += i * i;
	}
	return sum;
}

void baseItemCreator::GetAllEmptyPos(int x, int y, int total, std::vector<pair<int, int>>& vec, Board& b)
{
	//从内向外，顺时针一圈圈遍历
	/*
									   -->
			 -->					1 1 1 1 2
		 *	1 1 2				*	4       2
		 |	4   2  |	 ===》	|	4       2  |
			4 3 3  *				4		2  *
			 <--					4 3 3 3 3
									   <--
	*/
	int Radius = 8, oRadius = Radius;
	int length = 2;
	int startX = x - 1;
	int startY = y - 1;
	int i, j;
	
	while (total > 0 && Radius--) {
		i = startX;
		j = startY;
		int k = 0;
		for (; i < startX + length; i++) {
			GetEmptyPos(i, j, total, vec, b);
		}
		for (; j < startY + length; j++) {
			GetEmptyPos(i, j, total, vec, b);
		}
		for (; i > startX; i--) {
			GetEmptyPos(i, j, total, vec, b);
		}
		for (; j > startY; j--) {
			GetEmptyPos(i, j, total, vec, b);
		}	
		startX--;
		startY--;
		length += 2;
	}
	//选好位置后随机打乱指定位置
	int delta = oRadius - Radius;
	int start;
	start = delta == 1 ? 0 : squareSum(delta + 1) - 1;
	RandVector(vec, start, (int)vec.size() - 1);
}

void baseItemCreator::GetEmptyPos(int x, int y, int& total, std::vector<pair<int, int>>& vec, Board& b)
{
	auto cell = b.GetCell(x, y);
	if (cell) {
		if (!cell->HasObstacle() && !cell->HasItem()) {
			vec.push_back({ x,y });
			total--;
		}
	}
}

baseItem* baseItemCreator::GetItemPointer(int handler)
{
	if (handler >= 0 && handler < pItems.size()) {
		return pItems[handler];
	}
	return nullptr;
}

void baseItemCreator::Run(Board &b)
{
	Config* cfg = Config::GetInstance();
	if (!cfg) {
		return;
	}
	while (!_queue.empty()) {
		int timeIndex2 = GetTickCount();
		itemRequest& req = _queue.front();
		
		std::string prStr = "";
  		cfg->GetConfig("pr")->GetString(req.typeId, 2, prStr);
		stringReplace(prStr, ":", " ");
		stringReplace(prStr, "&", " ");
		stringReplace(prStr, ";", " ");
		istringstream pr(prStr);
		int count,itemID,num,prob;
		pr >> count;
		while (count--) {
			pr >> itemID >> num >> prob;
			//根据概率获得最终物品数量
			int total = 0;
			while (num--) {
				int r1 = rand() % 100;
				if (r1 <= prob - 1) {
					total++;
				}
			}
			//获取可用位置
			std::vector<pair<int, int>> vec;
			GetAllEmptyPos(req.gridX, req.gridY, total, vec, b);
			//生成物品
			int timeIndex = GetTickCount();
			for (int i = 0; i < total; i++) {
				Item* item = new Item(itemID, 0, vec[i].first, vec[i].second);
				if (item) {
					pItems.push_back(item);
					ptrCount++;
					int handler = (int)pItems.size() - 1;
					b.AddItem(vec[i].first, vec[i].second, handler);
				}	
			}
		}
		std::cout <<"总："<< GetTickCount() - timeIndex2 << std::endl;
		_queue.pop();
	}
}



