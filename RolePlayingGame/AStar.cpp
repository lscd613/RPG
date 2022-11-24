#include "pch.h"
#include "AStar.h"
#include <unordered_map>
#include <map>
#include "Data.h"
int memCount = 0;
//cache��¼new �� delete
std::vector<pair<int,int>> AStar::GetPath(position& pos, vector<int>& target, Board& board) {

	//Ϊʲô��unordered_map���У�
	std::map<pair<int, int>, Node*> toSearch;
	std::map<pair<int,int>,Node*> processed;

	Node *start =  new Node(pos.grid_x, pos.grid_y);
	if (!start) {
		return{};
	}
	start->G = 0;
	toSearch[{start->x, start->y}] = start;
	//�޴���ڵ����˳�ѭ��

	while (!toSearch.empty()) {
		//ѡ��Fֵ��С�Ľ��
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
		//���Ϊ�Ѵ���
		processed[{cur->x, cur->y}] = cur;
		auto iter = toSearch.find({ cur->x,cur->y });
		toSearch.erase(iter);

		//���cur��Ŀ��ڵ㣬˵���ҵ���·��
		if (cur->x == target[0] && cur->y == target[1]) {
			vector<pair<int,int>> path;
			//����preָ�����δ��·���ڵ�
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
			//���ؽ��
			//cout << memCount << endl;
			return path;
		}
		//����cur�ھ�
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
				//δ��������߽ڵ�Gֵ��С
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
	//�ڵ�8���ھ�
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
