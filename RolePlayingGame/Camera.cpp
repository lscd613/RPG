#include "pch.h"
#include "Camera.h"
#include "common.h"
#include <iostream>
#include "Board.h"
#include "Data.h"
#include "baseItemCreator.h"
#include "FightEntityCreator.h"
extern Data g_data;


void Camera::Render(std::map<int, IMAGE*>&imgMap, position& pos,Board &b)
{
	int imgWidth = g_data.imgWidth;
	int imgHeight = g_data.imgHeight;
	int blockX = pos.x / imgWidth - 2 + 1;
	int blockY = (pos.y / imgHeight - 2 + 1) * 9;
 	int centerPos[2] = { pos.x / imgWidth * imgWidth + imgWidth / 2, pos.y / imgHeight * imgHeight + imgHeight / 2 };

	for (int i = -1; i <= g_data.cameraBlockHeight; ++i)
	{
		for (int j = -1; j <= g_data.cameraBlockWidth; j++, blockX++)
		{
			if (blockX >= 0 && blockX < 9 && blockY >= 0 && blockY <= 72) {
				int offsetX = centerPos[0] - pos.x;
				int offsetY = centerPos[1] - pos.y;
				putimagex(-20+imgWidth * j + offsetX, -20+imgHeight * i + offsetY, imgWidth, imgHeight, *imgMap[blockX + blockY], 0, 0);
			}
		}
		blockX = pos.x / imgWidth - 2 + 1;
		blockY += 9;
	}
	RenderGrid(pos,b);
}

void Camera::RenderGrid(const position& pos, Board& b)
{
	int width = g_data.gridWidth, height = g_data.gridHeight;
	int gridX = pos.x / width - g_data.screenGridWidth / 2;
	int gridY = (pos.y / height - g_data.screenGridHeight / 2) * g_data.mapGridWidth;
	int centerPos[2] = { pos.x / width * width + width / 2, pos.y / height * height + height / 2 };

	//绘制各种网格
	for (int i = 10; i < (g_data.screenGridHeight + 1 ) * height; i += height) {
		for (int j = -20; j < (g_data.screenGridWidth + 1 ) * width; j += width, gridX++) {
			if (gridX >= 0 && gridX < g_data.mapGridWidth
				&& gridY >= 0 && gridY <= g_data.mapGridWidth * (g_data.mapGridHeight - 1)) {
				int offsetX = centerPos[0] - pos.x;
				int offsetY = centerPos[1] - pos.y;
				auto cell = b.GetCell(gridX+gridY);		
				////////////////////////////////
				if (cell && cell->HasObstacle() 
					|| cell->inPath
					|| cell->HasEntity()) {
					if (cell->inPath) {
						setfillcolor(BLUE);
					}
					else if(cell->HasObstacle()) {
						setfillcolor(DARKGRAY);
					}
					else
						setfillcolor(GREEN);
					fillrectangle(j + offsetX, i + offsetY, j + width + offsetX, i + height + offsetY);
				}
				if (cell->GetID()>= -1) {
					setfillcolor(YELLOW);
					fillrectangle(j + offsetX, i + offsetY, j + width + offsetX, i + height + offsetY);
				}
				/*else {
					rectangle(j + offsetX, i + offsetY, j + g_data.gridWidth + offsetX, i + g_data.gridHeight + offsetY);
				}*/
			}
		}
		gridX = pos.x / width - g_data.screenGridWidth / 2;
		gridY += g_data.mapGridWidth;
	}
	//绘制人物和怪物
	gridX = pos.x / width - g_data.screenGridWidth / 2;
	gridY = (pos.y / height - g_data.screenGridHeight / 2) * g_data.mapGridWidth;
	for (int i = 10; i < (g_data.screenGridHeight + 1) * height; i += height) {
		for (int j = -20; j < (g_data.screenGridWidth + 1) * width; j += width, gridX++) {
			if (gridX >= 0 && gridX < g_data.mapGridWidth
				&& gridY >= 0 && gridY <= g_data.mapGridWidth * (g_data.mapGridHeight - 1)) {
				Cell* cell = b.GetCell(gridX + gridY);
				if (cell) {
					auto item = cell->GetItem();
					if (item && cell->HasItem()) {
						item->Render(pos.x, pos.y);
					}
					FightEntityCreator* f_creator = FightEntityCreator::GetInstance();
					if (f_creator) {
						auto e = f_creator->GetPointer(cell->GetEntity());
						if (e && cell->HasEntity()) {
							e->Render(pos.x, pos.y);
						}
					}
				}
			}
		}
		gridX = pos.x / width - g_data.screenGridWidth / 2;
		gridY += g_data.mapGridWidth;
	}
}

Camera::Camera()
{
	
}


Camera::~Camera()
{
	
}


