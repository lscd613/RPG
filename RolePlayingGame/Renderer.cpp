#include "pch.h"
#include "Renderer.h"
#include <iostream>
#include "Data.h"
#include "Monster.h"
extern Data g_data;
Renderer::Renderer()
{
	
}


Renderer::~Renderer()
{
	
}


void Renderer::Render(shared_ptr<Role> role, Camera & camera, Map &map)
{
	if (!role) {
		return;
	}
	//开始绘图
	BeginBatchDraw(); 

	//清屏
	clearrectangle(0, 0, g_data.screenWidth, g_data.screenHeight);

	//
	camera.Render(map.GetImages(), role->GetPos(), map.GetBoard());
	role->GetPackage().Show();

	// 结束绘图
	EndBatchDraw(); 
}


