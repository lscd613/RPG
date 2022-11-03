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
	void HandleKeyboard(Role & role);//���̿���
	void HandleMouse(Role & role, Camera & data, MOUSEMSG & msg);//������
	void HandleRoleMove(Role &role, Camera & data, MOUSEMSG & msg, Map & map);//�ܿ���

private:
	int clickIndex = FALSE;//��������
	int timeIndex = GetTickCount();

};

