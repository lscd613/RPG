#include "pch.h"
#include "ImageManager.h"
#include <fstream>
#include "Config.h"
void ImageManager::LoadSingleImg(std::string type, int id, std::string path, int status)
{

	if (imageMap[type][id].size() < STATE_NUM) {
		imageMap[type][id].resize(STATE_NUM);
	}
	if (status >= 0 && status < imageMap[type][id].size()) {
		IMAGE* img = new IMAGE;
		if (img) {
			ptrCount++;
			loadimagex(*img, path.c_str());
			imageMap[type][id][status].push_back(img);
		}
	}
}

void ImageManager::LoadOneStateImgs(std::string type, int id, std::string path, int status)
{
	if (status < 0 || status >= STATE_NUM) {
		return;
	}

	std::ifstream file(path);
	std::string str, imgType = "";
	int count = 0;
	if (imageMap[type][id].size() < STATE_NUM) {
		imageMap[type][id].resize(STATE_NUM);
	}
	auto& vec = imageMap[type][id][status];
	vec = std::vector<IMAGE*>{};
	while (getline(file, str)) {
		if ("up" == str || "down" == str || "rightdown" == str || "rightup" == str || "right" == str) {
			if ("rightdown" == imgType || "rightup" == imgType || "right" == imgType) {
				int size = (int)vec.size();
				for (int i = 0; i < count; i++) {
					//m
					IMAGE* img2 = new IMAGE;
					if (img2) {
						ptrCount++;
						mirrorimage(*vec[size - (count - i)], *img2);
						vec.push_back(img2);
					}
				}
			}
			count = 0;
			imgType = str;
			continue;
		}
		if ("rightdown" == imgType || "rightup" == imgType || "right" == imgType) {
			count++;
		}
		//m
		IMAGE* img = new IMAGE;
		ptrCount++;
		loadimagex(*img, str.c_str());
		imageMap[type][id][status].push_back(img);
	}
	file.close();
}

void ImageManager::LoadImgs(std::string type, int id, std::string path)
{
	LoadOneStateImgs(type, id, path + type + "StayImage.txt", moveStatus::stay);
	LoadOneStateImgs(type, id, path + type+ "RunImage.txt", moveStatus::run);
	LoadOneStateImgs(type, id, path + type + "AttackImage.txt", moveStatus::attack);
	LoadOneStateImgs(type, id, path + type + "DeadImage.txt", moveStatus::dead);
}

ImageManager::ImageManager()
{
	LoadImgs("role", -1, "res/");
	LoadImgs("monster", 1, "res/");
	LoadImgs("weapon", 1, "res/");

	CsvReader* reader = Config::GetInstance()->GetConfig("item");
	if (reader != nullptr) {
		for (int id = 1; id <= reader->Size(); id++) {
			std::string path;
			reader->GetString(id, 4, path);
			LoadSingleImg("item", id, path, moveStatus::stay);
		}
	}
}

bool ImageManager::HasImage(std::string type, int id)
{
	if (imageMap.find(type) == imageMap.end()
		|| imageMap[type].find(id) == imageMap[type].end()) {
		return false;
	}
	return true;
}

ImageManager::~ImageManager()
{
	for (auto typeIter : imageMap) {
		for (auto idIter : typeIter.second){
			for (auto imgVec : idIter.second) {
				for (auto imgPtr : imgVec) {
					SAFE_DELETE(imgPtr);
					ptrCount--;
				}
			}
		}
	}
	std::cout << ptrCount << std::endl;
}

std::vector<std::vector<IMAGE*>>* ImageManager::GetImage(std::string type, int id)
{
	if (HasImage(type,id)) {
		return &imageMap[type][id];
	}
	return nullptr;
}


