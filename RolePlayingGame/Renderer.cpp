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


void Renderer::Render(Role & role, Camera & camera, Map &map)
{
	//??ʼ??ͼ
	BeginBatchDraw(); 

	//????
	clearrectangle(0, 0, g_data.screenWidth, g_data.screenHeight);

	//
	camera.Render(map.GetImages(), role.GetPos(), map.GetBoard());
	role.GetPackage().Show();

	// ??????ͼ
	EndBatchDraw(); 
}


