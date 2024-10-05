#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene()
{
	songs.push_back(new Songlist({ -320, 300, 0 }, test, { 80,32 }));
	songs.push_back(new Songlist({ -320, 200, 0 }, So_Happy, { 80,132 }));
	songs.push_back(new Songlist({ -320, 100, 0 }, Alone, { 80,232 }));
	songs.push_back(new Songlist({ -320, 000, 0 }, MilK, { 80,332 }));
	songs.push_back(new Songlist({ -320, -100, 0 }, Infinity, { 80,432 }));
	songs.push_back(new Songlist({ -320, -200, 0 }, IWantYou, { 80,532 }));
	songs.push_back(new Songlist({ -320, -300, 0 }, BrainPower, { 80,632 }));
}

MainScene::~MainScene()
{
	SAFE_DELETE(start);
	SAFE_DELETE(setting);
	SAFE_DELETE(info);
	for (Songlist* song : songs)
		SAFE_DELETE(song);
}

void MainScene::Init()
{
	info = new SongInfo();
	setting = new SettingUI();
	start = new StartButton();
}

void MainScene::Update()
{
	for (Songlist* song : songs)
		song->Update();
	info->Update();
	start->Update();
	
	if (start->start == true)
		ChangeScene = true;
}

void MainScene::PreRender()
{
}

void MainScene::Render()
{
	for (Songlist* song : songs)
	{
		song->Render();
		song->GUI();
	}
	info->Render();
	info->GUI();
	setting->GUI();
	start->Render();
}

void MainScene::PostRender()
{
}
