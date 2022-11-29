#pragma once
#include "MoveBase.h"
#include "Data.h"
class MoveController
{
private:
	
	int keyBoardInterval = 100;
	decltype(GetTickCount()) timeIndex = GetTickCount();
	int clickIndex = 0;
	
public:
	MoveBase base;
	int clickPos[2] = { -1,-1 };
	void Move(MOUSEMSG& msg, Board& b);
	void HandleMouse(MOUSEMSG& msg, Board& b);
	void HandleKeyboard(Board& b);

	MoveController(position& pos);
	~MoveController();
};

