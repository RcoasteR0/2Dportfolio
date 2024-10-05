#include "stdafx.h"
#include "Accurate.h"

Accurate::Accurate()
	:TextureRect({ 0, 0, 0 }, { 0, 0, 1 }, 0)
{
	display = 0;
	tsize = size;
	SetPos(position);
	SetSize(size);
}

Accurate::~Accurate()
{
}

void Accurate::DisplayJudge(Judge recentJudgement)
{
	if (recentJudgement == NONE)
		return;

	display = 1;
	switch (recentJudgement)
	{
	case PERFECT:
		SetSRV(L"./_Textures/judgement_perfect.png");
		break;
	case GREAT:
		SetSRV(L"./_Textures/judgement_great.png");
		break;
	case GOOD:
		SetSRV(L"./_Textures/judgement_good.png");
		break;
	case BAD:
		SetSRV(L"./_Textures/judgement_bad.png");
		break;
	case MISS:
		SetSRV(L"./_Textures/judgement_miss.png");
		break;
	}
}

void Accurate::Update()
{
	if (display > 0)
	{
		tsize.x = 225 - 750 * (1 - display);
		tsize.y = 75 - 250 * (1 - display);
		if (display < 0.9f)
			tsize = size;
		SetSize(tsize);

		display -= Time::Get()->Delta();
		InvisibleTexture(false);
	}
	else
		InvisibleTexture(true);
}

