#include "pch.h"
//#include "EntityCreator.h"
//
//#include "CsvReader.h"
//#include <iostream>
//#include "Config.h"
//#include "Data.h"
//
//
//EntityCreator::EntityCreator()
//{
//}
//
//EntityCreator::~EntityCreator()
//{
//	for (auto& item : pItems) {
//		SAFE_DELETE(item);
//		ptrCount--;
//	}
//}
//
//baseItem* baseItemCreator::GetItemPointer(int handler)
//{
//	if (handler >= 0 && handler < pItems.size()) {
//		return pItems[handler];
//	}
//	return nullptr;
//}
//
//void baseItemCreator::Run(Board& b)
//{
//	Config* cfg = Config::GetInstance();
//	if (!cfg) {
//		return;
//	}
//	while (!_queue.empty()) {
//		int timeIndex2 = GetTickCount();
//		itemRequest& req = _queue.front();
//
//		std::string prStr = "";
//		cfg->GetConfig("pr")->GetString(req.typeId, 2, prStr);
//		stringReplace(prStr, ":", " ");
//		stringReplace(prStr, "&", " ");
//		stringReplace(prStr, ";", " ");
//		istringstream pr(prStr);
//		int count, itemID, num, prob;
//		pr >> count;
//		while (count--) {
//			pr >> itemID >> num >> prob;
//			//根据概率获得最终物品数量
//			int total = 0;
//			while (num--) {
//				int r1 = rand() % 100;
//				if (r1 <= prob - 1) {
//					total++;
//				}
//			}
//			//获取可用位置
//			std::vector<pair<int, int>> vec;
//			GetAllEmptyPos(req.gridX, req.gridY, total, vec, b);
//			//生成物品
//			int timeIndex = GetTickCount();
//			for (int i = 0; i < total; i++) {
//				Item* item = new Item(itemID, 0, vec[i].first, vec[i].second);
//				if (item) {
//					pItems.push_back(item);
//					ptrCount++;
//					int handler = (int)pItems.size() - 1;
//					b.AddItem(vec[i].first, vec[i].second, handler);
//				}
//			}
//		}
//		std::cout << "总：" << GetTickCount() - timeIndex2 << std::endl;
//		_queue.pop();
//	}
//}



