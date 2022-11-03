#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <set>
#include "Board.h"

//A*Ѱ·�㷨
class AStar
{	
struct Node {
	int G, H, F;
	int x, y;
	Node* pre = nullptr;
	Node(int x, int y, Node* p = nullptr) :x(x), y(y), pre(p) {};
	int i();
	vector<Node*> Neighbors();
	int GetDistance(Node* node) {
		int absX = abs(x - node->x);
		int absY = abs(y - node->y);
		int low = min(absX, absY),
			high = max(absX, absY);
		return low * 14 + (high - low) * 10;
	}
};
public:
	std::vector<pair<int, int>> GetPath(position& pos, vector<int>& target, Board &board);
};


