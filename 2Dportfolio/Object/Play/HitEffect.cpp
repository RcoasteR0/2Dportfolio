#include "stdafx.h"
#include "HitEffect.h"

HitEffect::HitEffect(int line)
	: AnimationRect({ 0, 0, 0 }, { 80, 80, 1 }, 0)
{
	if(line == 1 || line == 3 || line == 4 || line == 6)
		texture = new Texture2D(L"./_Textures/white_note_hit.png");
	else if (line == 2 || line == 5)
		texture = new Texture2D(L"./_Textures/black_note_hit.png");

	switch (line)
	{
	case(1):
		SetPos({ Lane1Pos, Common_Pos + (float)Setting::Get()->GetJudgementLinePos() , 0 });
		break;
	case(2):
		SetPos({ Lane2Pos, Common_Pos + (float)Setting::Get()->GetJudgementLinePos() , 0 });
		break;
	case(3):
		SetPos({ Lane3Pos, Common_Pos + (float)Setting::Get()->GetJudgementLinePos() , 0 });
		break;
	case(4):
		SetPos({ Lane4Pos, Common_Pos + (float)Setting::Get()->GetJudgementLinePos() , 0 });
		break;
	case(5):
		SetPos({ Lane5Pos, Common_Pos + (float)Setting::Get()->GetJudgementLinePos() , 0 });
		break;
	case(6):
		SetPos({ Lane6Pos, Common_Pos + (float)Setting::Get()->GetJudgementLinePos() , 0 });
		break;
	}

	animClips.push_back(new AnimationClip(L"Effect", texture, 13, { 0, 0 }, { (float)texture->GetWidth(), (float)texture->GetHeight() }));
	animator = new Animator(animClips);
	animator->bLoop = false;
	animator->playRate = -1.0f;
	animator->bStop = true;
}

HitEffect::~HitEffect()
{
	SAFE_DELETE(animator);
	SAFE_DELETE(animClips[0]);
	SAFE_DELETE(texture);
}

void HitEffect::ShortEffect()
{
	animator->SetCurrentFrameIndex();
	animator->playonce = true;
	animator->bStop = false;
}

void HitEffect::LongEffect(bool on)
{
	if (on)
	{
		animator->SetCurrentFrameIndex();
		animator->bLoop = true;
		animator->bStop = false;
	}
	else
	{
		animator->bLoop = false;
		animator->playonce = true;
	}
}

void HitEffect::EndEffect()
{
	animator->bStop = true;
	animator->bLoop = false;
}

void HitEffect::Update()
{
	AnimationRect::Update();
	if (animator->bStop == true)
		SetSize( { 0, 0, 0 } );
	else
		SetSize( { 80, 80, 1 } );
}
