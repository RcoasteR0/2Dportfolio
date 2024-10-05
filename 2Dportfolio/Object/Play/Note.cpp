#include "stdafx.h"
#include "Note.h"
#include "Geometry/TextureRect.h"

Note::Note(int line, float timing, NoteType type)
	:TextureRect({ 0, 0, 0 } , { 1, 1, 1 }, 0)
{
	switch (type)
	{
	case Short:
		if (line == 1 || line == 3 || line == 4 || line == 6)
		{
			SetSRV(L"./_Textures/white_note.png");
			SetSize({ WhlteLaneSize, 25, 1 });
		}
		else if (line == 2 || line == 5)
		{
			SetSRV(L"./_Textures/black_note.png");
			SetSize({ BlackLaneSize, 25, 1 });
		}
		break;
	case Long_Start:
		if (line == 1 || line == 3 || line == 4 || line == 6)
		{
			SetSRV(L"./_Textures/white_long_start.png");
			SetSize({ WhlteLaneSize, 25, 1 });
		}
		else if (line == 2 || line == 5)
		{
			SetSRV(L"./_Textures/black_long_start.png");
			SetSize({ BlackLaneSize, 25, 1 });
		}
		break;
	case Long_Hold:
		assert(false);
		break;
	case Long_End:
		if (line == 1 || line == 3 || line == 4 || line == 6)
		{
			SetSRV(L"./_Textures/white_long_end.png");
			SetSize({ WhlteLaneSize, 25, 1 });
		}
		else if (line == 2 || line == 5)
		{
			SetSRV(L"./_Textures/black_long_end.png");
			SetSize({ BlackLaneSize, 25, 1 });
		}
		break;
	}

	float linePos;
	switch (line)
	{
	case(1):
		linePos = Lane1Pos;
		break;
	case(2):
		linePos = Lane2Pos;
		break;
	case(3):
		linePos = Lane3Pos;
		break;
	case(4):
		linePos = Lane4Pos;
		break;
	case(5):
		linePos = Lane5Pos;
		break;
	case(6):
		linePos = Lane6Pos;
		break;
	}

	SetPos({ linePos, timing * Common_Speed * Setting::Get()->GetNoteSpeed() + Common_Pos + Setting::Get()->GetJudgementLinePos(), 0 });
}

Note::~Note()
{
}

void Note::Update()
{
	InvisibleTexture(hit);

	Move({ 0, -Common_Speed * Time::Get()->Delta() * Setting::Get()->GetNoteSpeed() , 0 });
}
