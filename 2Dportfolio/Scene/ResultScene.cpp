#include "stdafx.h"
#include "ResultScene.h"

ResultScene::ResultScene()
{
	home = new BackMain({0, -300, 0}, Button_Home);
}

ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
	result = new ResultUI();
}

void ResultScene::Update()
{
	home->Update();
	if (home->back)
	{
		home->back = false;
		ChangeScene = true;
	}
}

void ResultScene::PreRender()
{
}

void ResultScene::Render()
{
	result->Render();
	home->Render();
	result->GUI();
}

void ResultScene::PostRender()
{
}
