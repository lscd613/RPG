#include "pch.h"
#include "AStar.h"
#include <unordered_map>
#include <map>
#include "Data.h"
int memCount = 0;
//cache记录new 和 delete
std::vector<pair<int,int>> AStar::GetPath(position& pos, vector<int>& target, Board& board) {

	//为什么用unordered_map不行？
	std::map<pair<int, int>, Node*> toSearch;
	std::map<pair<int,int>,Node*> processed;

	Node *start =  new Node(pos.grid_x, pos.grid_y);
	if (!start) {
		return{};
	}
	start->G = 0;
	toSearch[{start->x, start->y}] = start;
	//无处理节点则退出循环

	while (!toSearch.empty()) {
		//选出F值最小的结点
		Node* cur = (* toSearch.begin()).second;
		if (!cur) {
			continue;
		}
		for (auto node : toSearch) {
			if (node.second) {
				if (node.second->F < cur->F || node.second->F == cur->F && node.second->H < cur->H) {
					cur = node.second;
				}
			}	
		}
		//标记为已处理
		processed[{cur->x, cur->y}] = cur;
		auto iter = toSearch.find({ cur->x,cur->y });
		toSearch.erase(iter);

		//如果cur是目标节点，说明找到了路径
		if (cur->x == target[0] && cur->y == target[1]) {
			vector<pair<int,int>> path;
			//根据pre指针依次存放路径节点
			while (cur->pre != nullptr) {
				path.push_back({ cur->x ,cur->y});
				Cell* cell = board.GetCell(cur->x, cur->y);
				if (cell) {
					cell->inPath = 1;
				}	
				cur = cur->pre;	
			}
			for (auto i : processed) {
				SAFE_DELETE(i.second);
			}
			for (auto i : toSearch) {
				SAFE_DELETE(i.second);
			}
			//返回结果
			//cout << memCount << endl;
			return path;
		}
		//遍历cur邻居
		for (auto node : cur->Neighbors()) {
			if (!node) {
				continue;
			}
			int index = node->x + node->y * g_data.mapWidth * g_data.indexWidth;
			if (board.IsNoObstackleCell(node->x, node->y)
				&& processed.find({ node->x,node->y }) == processed.end()) {

				bool inSearch = false;
				if (toSearch.find({ node->x ,node->y }) != toSearch.end()) {
					Node* temp = node;
					node = toSearch[{ node->x, node->y }];
					SAFE_DELETE(temp);
					inSearch = true;
				}	
				int costToNeighbour = cur->G + cur->GetDistance(node);
				//未经处理或者节点G值更小
				if (!inSearch || costToNeighbour < node->G) {
					node->G = costToNeighbour;
					node->pre = cur;
					if (!inSearch) {
						Node temp(target[0], target[1]);
						node->H = node->GetDistance(&temp);
						node->F = node->H + node->G;
						toSearch[{node->x, node->y}] = node;
					}
				}
			}
			else {
				SAFE_DELETE(node);
			}
		}
	}
	
	for (auto i : processed) {
		SAFE_DELETE(i.second);
	}
	return std::vector<pair<int, int>>{};
}

vector<AStar::Node*> AStar::Node::Neighbors()
{
	//节点8个邻居
	vector<Node*> neighbors;
	for (int j = y - 1; j < y + 2; j++) {
		for (int i = x - 1; i < x + 2; i++) {
			if (i == x && j == y) {
				continue;
			}
			auto node = new Node(i, j);
			if (!node) {
				break;
			}
			neighbors.push_back(node);
		}
	}
	return neighbors;
}
