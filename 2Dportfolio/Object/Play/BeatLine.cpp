#include "stdafx.h"
#include "BeatLine.h"

BeatLine::BeatLine(float position)
	:TextureRect({ 0,position * Common_Speed * Setting::Get()->GetNoteSpeed() + Common_Pos + Setting::Get()->GetJudgementLinePos() ,0 }, { 250, 2, 1 }, 0)
{
	SetSRV(L"./_Textures/beatline.png");
}

BeatLine::~BeatLine()
{
}

void BeatLine::Update()
{
	Move({ 0, -Common_Speed * Time::Get()->Delta() * Setting::Get()->GetNoteSpeed() , 0 });
}
