#include "pch.h"
#include "CsvReader.h"


void CsvReader::Open(const char* path)
{
	file.open(path);
	assert(file.good());
	std::string str;
	std::getline(file, str);
	while (std::getline(file, str)) {
		std::vector<std::string> vec;
		size_t cur = str.find(','),pre = 0;
		while (cur != -1) {	
			std::string str2(str.begin() + pre, str.begin() + cur);
			vec.push_back(str2);
			size_t tmp = str.find(',',cur+1);
			pre = cur + 1;
			cur = tmp;
		}
		vec.push_back(std::string(str.begin() + pre, str.begin() + str.size()));
		strVec.push_back(vec);
	}
}


CsvReader::CsvReader() {

}

CsvReader::CsvReader(const char* path) {
	Open(path);
}

int CsvReader::GetInt(int row, int column, int& val) {
	if (row < 1 || row >= strVec.size() + 1 || column < 1 || strVec[row].size() + 1 <= column) {
		return -1;
	}
	val = stoi(strVec[row - 1][column - 1]);
	return 1;
}

int CsvReader::GetString(int row, int column, std::string& str) {
	if (row < 1 || row >= strVec.size() + 1 || column < 1 || strVec[row - 1].size() + 1 <= column) {
		return -1;
	}
	str = strVec[row - 1][column - 1];
	return 1;
}

int CsvReader::Size() {
	return (int)strVec.size();
}


