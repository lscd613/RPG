#pragma once
#include "CsvReader.h"
#include <map>
#include <string>
class Config
{
private:
	std::map<std::string, CsvReader*> configMap;
private:
	Config();
	void LoadConfig(std::string type,const char*);
public:
	~Config();
	static Config* GetInstance() {
		static Config cfg;
		return &cfg;
	}

	CsvReader* GetConfig(std::string type) {
		if (configMap.find(type) == configMap.end()) {
			return nullptr;
		}
		return configMap[type];
	}
};
