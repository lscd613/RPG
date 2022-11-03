#pragma once
#include <fstream>
#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
class CsvReader
{
	std::vector<std::vector<std::string>> strVec;
	std::ifstream file;
public:
	CsvReader();
	CsvReader(const char* path);
	void Open(const char*);
	int GetInt(int row, int column, int& val);
	int GetString(int row, int column, std::string& str);
	int Size();
};

