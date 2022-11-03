#pragma once
#include <map>
#include <vector>
#include <string>
#include "common.h"
#include "Data.h"
#include "Sprite.h"
#include "CsvReader.h"
extern Data g_data;

class Entity
{	
protected:

protected:	
	position pos;
	property prop;
	status stat;
	Sprite sprite;
	entityType type = entityType::role;
	int id;
	int typeID;
	std::string name = "-";
protected:
	Entity(int id);
	virtual ~Entity();

public:	


public:
	int GetMoveStatus();//获取角色移动状态
	int GetID();
	position& GetPos();
	property& GetProperty();
	status& GetStatus();
	std::string GetName();
	void SetPos(int, int);
	void SetGridPos(int, int);
	virtual void Render(int centerX, int centerY);
	entityType GetType();//获取entity指针实际指向的子类
	
};

