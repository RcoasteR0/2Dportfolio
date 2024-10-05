#include "stdafx.h"
#include "JudgementLine.h"
#include "Geometry/TextureRect.h"

JudgementLine::JudgementLine()
	:TextureRect({ 0, (float)Setting::Get()->GetJudgementLinePos() - 200, 0 }, { 250, 25, 1 }, 0)
{
	SetSRV(L"./_Textures/judgement_line.png");
}

JudgementLine::~JudgementLine()
{
}

void JudgementLine::Update()
{

}
