#include "stdafx.h"
#include "Scene/SceneList.h"
#include "Program.h"

Program::Program()
{
	Camera::Create();
}

//�Ҹ���
Program::~Program()
{
	Camera::Delete();
}

//�� ����
void Program::Init()
{
	mainscene = new MainScene();
	playscene = new PlayScene();
	resultscene = new ResultScene();
	currentScene = mainscene;
	currentScene->Init();
}

void Program::Update()
{
	Camera::Get()->Update();

	if (mainscene->ChangeScene)
	{
		mainscene->ChangeScene = false;
		currentScene = playscene;
		currentScene->Init();
	}
	if (playscene->ChangeScene)
	{
		playscene->ChangeScene = false;
		currentScene = resultscene;
		currentScene->Init();
	}
	if (playscene->BacktoMain)
	{
		playscene->BacktoMain = false;
		currentScene = mainscene;
		currentScene->Init();
	}
	if (resultscene->ChangeScene)
	{
		resultscene->ChangeScene = false;
		currentScene = mainscene;
		currentScene->Init();
	}
		
		currentScene->Update();	//���� �� ������Ʈ
}

void Program::PreRender()
{
	currentScene->PreRender();
}

//������
void Program::Render()
{
	Camera::Get()->Render();
	currentScene->Render();	//���� �� ������
}

void Program::PostRender()
{
	Gui::Get()->PrintFrame();
	currentScene->PostRender();
}
