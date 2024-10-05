#include "stdafx.h"
#include "StartButton.h"

StartButton::StartButton()
	:TextureRect({ 320, -270, 0 }, { 220, 60, 1 }, 0)
	, start(false)
{
	SetSRV(L"./_Textures/start.png");
}

StartButton::~StartButton()
{
}

void StartButton::Update()
{
	Vector3 mouse = { Mouse::Get()->GetPosition().x - WinMaxWidth / 2, Mouse::Get()->GetPosition().y - WinMaxHeight / 2, 0 };

	if (Mouse::Get()->Down(0) && Math::Intersect(this, mouse))
	{
		start = true;
	}
}
