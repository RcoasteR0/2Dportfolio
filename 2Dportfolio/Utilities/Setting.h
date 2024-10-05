#pragma once

#include "stdafx.h"

#define Common_Speed 150
#define Common_Pos -200

enum Effect
{
	No_Effect,
	Sudden,
	Vanish,
	Hidden
};

enum Random
{
	No_Random,
	Swap_Random,
	Half_Random,
	Chaos_Random
};

class Setting : public Singleton<Setting>
{
public:
	void SetCurrentSong(Info CurrentSong) { this->CurrentSong = CurrentSong; }
	void SetNoteSpeed(float NoteSpeed) { this->NoteSpeed = NoteSpeed; }
	void SetJudgementPos(float JudgementPos) { this->JudgementPos = JudgementPos; }
	void SetJudgementLinePos(int JudgementLinePos) { this->JudgementLinePos = JudgementLinePos; }
	void SetNoteEffect(Effect NoteEffect) { this->NoteEffect = NoteEffect; }
	void SetNoteRandom(Random NoteRandom) { this->NoteRandom = NoteRandom; }

	Info GetCurrentSong() { return CurrentSong; }
	float GetNoteSpeed() { return NoteSpeed; }
	float GetJudgementPos() { return JudgementPos; }
	int GetJudgementLinePos() { return JudgementLinePos; }
	Effect GetNoteEffect() { return NoteEffect; }
	Random GetNoteRandom() { return NoteRandom; }

private:
	Info CurrentSong;

	float NoteSpeed = 5.0f;
	float JudgementPos = 0.0f;
	int JudgementLinePos = 0;
	
	Effect NoteEffect = No_Effect;
	Random NoteRandom = No_Random;
};