#include "stdafx.h"
#include "Combo.h"

Combo::Combo()
	: TextureRect({ 0,0,0 }, { 0,0,0 }, 0)
{
	combo = 0;
	display = 0;
	num.assign(4, NULL);
	texture.assign(10, L"");
	texture[0] = L"./_Textures/combo_0.png";
	texture[1] = L"./_Textures/combo_1.png";
	texture[2] = L"./_Textures/combo_2.png";
	texture[3] = L"./_Textures/combo_3.png";
	texture[4] = L"./_Textures/combo_4.png";
	texture[5] = L"./_Textures/combo_5.png";
	texture[6] = L"./_Textures/combo_6.png";
	texture[7] = L"./_Textures/combo_7.png";
	texture[8] = L"./_Textures/combo_8.png";
	texture[9] = L"./_Textures/combo_9.png";
	SetSRV(L"./_Textures/combo_0.png");

	SetPos(position);
	SetSize(size);
}

Combo::~Combo()
{
}

void Combo::Update()
{
	combo = JUDGEMENT->GetCombo();
	if (combo > 1)
	{
		InvisibleTexture(false);
		if (combo >= 1000)
		{
			num[3] = combo / 1000;
		}
		if (combo >= 100)
		{
			num[2] = combo / 100 - combo / 1000 * 10;
		}
		if (combo >= 10)
		{
			num[1] = combo / 10 - combo / 100 * 10;
		}
		num[0] = combo - combo / 10 * 10;
	}
	else
		InvisibleTexture(true);
	display -= Time::Get()->Delta();
}

void Combo::Render()
{
	if (combo >= 1000)
	{
		for (int i = 0; i < 4; i++)
		{
			SetPos({ size.x / 2 * 3 - size.x * i, position.y, position.z });
			SetSRV(texture[num[i]]);
			TextureRect::Render();
		}
	}
	else if (combo >= 100)
	{
		for (int i = 0; i < 3; i++)
		{
			SetPos({ size.x - size.x * i, position.y, position.z });
			SetSRV(texture[num[i]]);
			TextureRect::Render();
		}
	}
	else if (combo >= 10)
	{
		for (int i = 0; i < 2; i++)
		{
			SetPos({ size.x / 2 - size.x * i, position.y, position.z });
			SetSRV(texture[num[i]]);
			TextureRect::Render();
		}
	}
	else
	{
		SetPos(position);
		SetSRV(texture[num[0]]);
		TextureRect::Render();
	}
}
