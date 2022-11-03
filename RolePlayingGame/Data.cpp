#include "pch.h"
#include "Data.h"
Data g_data;

void UpdateGridPos(position& pos)
{
	pos.grid_x = pos.x / g_data.gridWidth;
	pos.grid_y = pos.y / g_data.gridHeight;
}