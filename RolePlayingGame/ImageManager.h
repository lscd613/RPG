#pragma once
#include <vector>
#include <map>
#include <string>
#include "common.h"
#include "Data.h"

class ImageManager
{
	std::map<std::string, std::map<int, std::vector<std::vector<IMAGE*>>>> imageMap;
	void LoadSingleImg(std::string type, int id, std::string path, int status);
	void LoadOneStateImgs(std::string type, int id, std::string path, int status);
	void LoadImgs(std::string type, int id, std::string path);
private:
	ImageManager();
	bool HasImage(std::string, int);
public:
	static ImageManager* GetInstance() {
		static ImageManager imgManager;
		return &imgManager;
	}
	~ImageManager();
	std::vector<std::vector<IMAGE*>>* GetImage(std::string, int);
};

