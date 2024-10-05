#include "stdafx.h"
#include "BackMain.h"

BackMain::BackMain(Vector3 position, BackButtonType type)
	:TextureRect(position, { 80, 80, 1 }, 0)
	, back(false)
{
	switch (type)
	{
	case Button_Back:
		SetSRV(L"./_Textures/back.png");
		break;
	case Button_Home:
		SetSRV(L"./_Textures/home.png");
		break;
	}
	
}

BackMain::~BackMain()
{
}

void BackMain::Update()
{
	Vector3 mouse = { Mouse::Get()->GetPosition().x - WinMaxWidth / 2, Mouse::Get()->GetPosition().y - WinMaxHeight / 2, 0 };

	if (Mouse::Get()->Down(0) && Math::Intersect(this, mouse))
	{
		back = true;
	}
}
