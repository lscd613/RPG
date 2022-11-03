#pragma once
#include "Role.h"
#include "common.h"
#include "Camera.h"
#include <iostream>
#include "Map.h"
class Control
{

public:
	Control();
	~Control();
	void HandleKeyboard(Role & role);//键盘控制
	void HandleMouse(Role & role, Camera & data, MOUSEMSG & msg);//鼠标控制
	void HandleRoleMove(Role &role, Camera & data, MOUSEMSG & msg, Map & map);//总控制

private:
	int clickIndex = FALSE;//鼠标点击标记
	int timeIndex = GetTickCount();

};

