#include "pch.h"
#include "Config.h"
#include <iostream>
#include "Data.h"
Config::Config()
{
	LoadConfig("monster", "./monster.csv");
	LoadConfig("item", "./item.csv");
	LoadConfig("pr", "./PR.csv");
}

void Config::LoadConfig(std::string type, const char* path)
{
	CsvReader *reader = new CsvReader;
	if (reader) {
		reader->Open(path);
		configMap[type] = reader;
	}
}

Config::~Config()
{
	for (auto &cfg : configMap) {
		SAFE_DELETE(cfg.second);
	}
}
