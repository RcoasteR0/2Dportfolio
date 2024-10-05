#include "stdafx.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
	song = new SoundSystem();
	lane = new Lane();
	frame = new Frame();
	judgementline = new JudgementLine();
	accurate = new Accurate();
	combo = new Combo();
	back = new BackMain({ -600, 320, 0 }, Button_Back);
}

PlayScene::~PlayScene()
{
	for (BeatLine* beatline : beatlines)
		SAFE_DELETE(beatline);
	for (LongNote* longnote : longNotes)
		SAFE_DELETE(longnote);
	for (Note* note: notes)
		SAFE_DELETE(note);
	for (HitEffect* effect : effects)
		SAFE_DELETE(effect);
	for (Light* lane : laneLights)
		SAFE_DELETE(lane);
	for (Key* key : keyLights)
		SAFE_DELETE(key);
	SAFE_DELETE(combo);
	SAFE_DELETE(accurate);
	SAFE_DELETE(judgementline);
	SAFE_DELETE(frame);
	SAFE_DELETE(lane);
	SAFE_DELETE(song);
}

void PlayScene::Init()
{
	CurrentSong = Setting::Get()->GetCurrentSong();
	Time::Get()->Stop();
	Time::Get()->Initialize();
	loading = true;
	play = true;
	song->CreateBGSound(CurrentSong.Song);
	JUDGEMENT->LoadChart(CurrentSong);

	longJudge.assign(6, NONE);

	keyLights.assign(6, nullptr);
	keyLights[0] = new Key({ Lane1Pos, 0, 0 }, { WhlteLaneSize, WinMaxHeight, 1 }, White_Lane);
	keyLights[1] = new Key({ Lane2Pos, 0, 0 }, { BlackLaneSize, WinMaxHeight, 1 }, Black_Lane);
	keyLights[2] = new Key({ Lane3Pos, 0, 0 }, { WhlteLaneSize, WinMaxHeight, 1 }, White_Lane);
	keyLights[3] = new Key({ Lane4Pos, 0, 0 }, { WhlteLaneSize, WinMaxHeight, 1 }, White_Lane);
	keyLights[4] = new Key({ Lane5Pos, 0, 0 }, { BlackLaneSize, WinMaxHeight, 1 }, Black_Lane);
	keyLights[5] = new Key({ Lane6Pos, 0, 0 }, { WhlteLaneSize, WinMaxHeight, 1 }, White_Lane);

	laneLights.assign(6, nullptr);
	laneLights[0] = new Light({ Lane1Pos, 0, 0 }, { WhlteLaneSize, WinMaxHeight, 1 }, White_Lane);
	laneLights[1] = new Light({ Lane2Pos, 0, 0 }, { BlackLaneSize, WinMaxHeight, 1 }, Black_Lane);
	laneLights[2] = new Light({ Lane3Pos, 0, 0 }, { WhlteLaneSize, WinMaxHeight, 1 }, White_Lane);
	laneLights[3] = new Light({ Lane4Pos, 0, 0 }, { WhlteLaneSize, WinMaxHeight, 1 }, White_Lane);
	laneLights[4] = new Light({ Lane5Pos, 0, 0 }, { BlackLaneSize, WinMaxHeight, 1 }, Black_Lane);
	laneLights[5] = new Light({ Lane6Pos, 0, 0 }, { WhlteLaneSize, WinMaxHeight, 1 }, White_Lane);

	effects.assign(6, nullptr);
	effects[0] = new HitEffect(1);
	effects[1] = new HitEffect(2);
	effects[2] = new HitEffect(3);
	effects[3] = new HitEffect(4);
	effects[4] = new HitEffect(5);
	effects[5] = new HitEffect(6);

	//노트 생성
	notes.assign(JUDGEMENT->GetNoteCount(), nullptr);
	for (UINT i = 0; i < notes.size(); i++)
	{
		int line = JUDGEMENT->GetLine(i);
		float timing = JUDGEMENT->GetTiming(i);
		NoteType type = JUDGEMENT->GetType(i);
		notes[i] = new Note(line, timing, type);
	}

	longNotes.assign(JUDGEMENT->GetHoldCount(), nullptr);
	for (UINT i = 0; i < longNotes.size(); i++)
	{
		HoldTime temp = JUDGEMENT->GetHoldTime(i);
		longNotes[i] = new LongNote(temp.line, temp.Start, temp.End - temp.Start);
	}

	vector<float> temp = JUDGEMENT->GetBeatline();
	beatlines.assign(temp.size(), nullptr);
	for (UINT i = 0; i < beatlines.size(); i++)
	{
		beatlines[i] = new BeatLine(temp[i]);
	}
}

void PlayScene::Update()
{
	if (loading)
	{
		Time::Get()->Start();
		loading = false;
	}
	if (Time::Get()->Running() >= CurrentSong.SongDelay && play)
	{
		song->Play();
		//Time::Get()->Initialize(CurrentSong.SongDelay);
		play = false;
	}
	progress = JUDGEMENT->GetProgress();
	longprogress = JUDGEMENT->GetLongProgress();
	Judge recentJudge = NONE;

	//레인 강조
	keyLights[0]->setPress(KeyPress_Lane1);
	keyLights[1]->setPress(KeyPress_Lane2);
	keyLights[2]->setPress(KeyPress_Lane3);
	keyLights[3]->setPress(KeyPress_Lane4);
	keyLights[4]->setPress(KeyPress_Lane5);
	keyLights[5]->setPress(KeyPress_Lane6);

	laneLights[0]->setPress(KeyPress_Lane1);
	laneLights[1]->setPress(KeyPress_Lane2);
	laneLights[2]->setPress(KeyPress_Lane3);
	laneLights[3]->setPress(KeyPress_Lane4);
	laneLights[4]->setPress(KeyPress_Lane5);
	laneLights[5]->setPress(KeyPress_Lane6);

	//객체 업데이트
	if (!Time::Get()->Stopped())
	{
		for (Key* key : keyLights)
			key->Update();
		for (Light* laneLight : laneLights)
			laneLight->Update();
		for (Note* note : notes)
			note->Update();
		for (LongNote* longnote : longNotes)
			longnote->Update();
		for (BeatLine* beatline : beatlines)
			beatline->Update();
		for (HitEffect* effect : effects)
			effect->Update();
	}

	//KeyDown
	if (KeyDown_Lane1)
	{
		for (UINT i = progress; i < notes.size() && i < (UINT)(progress + 100); i++)
		{
			if (JUDGEMENT->CheckNoteHit(1, i, Short))
			{
				notes[i]->HitNote(true);
				recentJudge = JUDGEMENT->CheckJudgement(i);
				JUDGEMENT->SetJudge(recentJudge);
				effects[LANE1]->ShortEffect();
				break;
			}
			else if (JUDGEMENT->CheckNoteHit(1, i, Long_Start))
			{
				notes[i]->HitNote(true);
				longJudge[LANE1] = JUDGEMENT->CheckJudgement(i);
				longNotes[JUDGEMENT->FindLongNote(i)]->SetHold(true);
				effects[LANE1]->LongEffect(true);
				break;
			}
		}
	}
	if (KeyDown_Lane2)
	{
		for (UINT i = progress; i < notes.size() && i < (UINT)(progress + 100); i++)
		{
			if (JUDGEMENT->CheckNoteHit(2, i, Short))
			{
				notes[i]->HitNote(true);
				recentJudge = JUDGEMENT->CheckJudgement(i);
				JUDGEMENT->SetJudge(recentJudge);
				effects[LANE2]->ShortEffect();
				break;
			}
			else if (JUDGEMENT->CheckNoteHit(2, i, Long_Start))
			{
				notes[i]->HitNote(true);
				longJudge[LANE2] = JUDGEMENT->CheckJudgement(i);
				longNotes[JUDGEMENT->FindLongNote(i)]->SetHold(true);
				effects[LANE2]->LongEffect(true);
				break;
			}
		}
	}
	if (KeyDown_Lane3)
	{
		for (UINT i = progress; i < notes.size() && i < (UINT)(progress + 100); i++)
		{
			if (JUDGEMENT->CheckNoteHit(3, i, Short))
			{
				notes[i]->HitNote(true);
				recentJudge = JUDGEMENT->CheckJudgement(i);
				JUDGEMENT->SetJudge(recentJudge);
				effects[LANE3]->ShortEffect();
				break;
			}
			else if (JUDGEMENT->CheckNoteHit(3, i, Long_Start))
			{
				notes[i]->HitNote(true);
				longJudge[LANE3] = JUDGEMENT->CheckJudgement(i);
				longNotes[JUDGEMENT->FindLongNote(i)]->SetHold(true);
				effects[LANE3]->LongEffect(true);
				break;
			}
		}
	}
	if (KeyDown_Lane4)
	{
		for (UINT i = progress; i < notes.size() && i < (UINT)(progress + 100); i++)
		{
			if (JUDGEMENT->CheckNoteHit(4, i, Short))
			{
				notes[i]->HitNote(true);
				recentJudge = JUDGEMENT->CheckJudgement(i);
				JUDGEMENT->SetJudge(recentJudge);
				effects[LANE4]->ShortEffect();
				break;
			}
			else if (JUDGEMENT->CheckNoteHit(4, i, Long_Start))
			{
				notes[i]->HitNote(true);
				longJudge[LANE4] = JUDGEMENT->CheckJudgement(i);
				longNotes[JUDGEMENT->FindLongNote(i)]->SetHold(true);
				effects[LANE4]->LongEffect(true);
				break;
			}
		}
	}
	if (KeyDown_Lane5)
	{
		for (UINT i = progress; i < notes.size() && i < (UINT)(progress + 100); i++)
		{
			if (JUDGEMENT->CheckNoteHit(5, i, Short))
			{
				notes[i]->HitNote(true);
				recentJudge = JUDGEMENT->CheckJudgement(i);
				JUDGEMENT->SetJudge(recentJudge);
				effects[LANE5]->ShortEffect();
				break;
			}
			else if (JUDGEMENT->CheckNoteHit(5, i, Long_Start))
			{
				notes[i]->HitNote(true);
				longJudge[LANE5] = JUDGEMENT->CheckJudgement(i);
				longNotes[JUDGEMENT->FindLongNote(i)]->SetHold(true);
				effects[LANE5]->LongEffect(true);
				break;
			}
		}
	}
	if (KeyDown_Lane6)
	{
		for (UINT i = progress; i < notes.size() && i < (UINT)(progress + 100); i++)
		{
			if (JUDGEMENT->CheckNoteHit(6, i, Short))
			{
				notes[i]->HitNote(true);
				recentJudge = JUDGEMENT->CheckJudgement(i);
				JUDGEMENT->SetJudge(recentJudge);
				effects[LANE6]->ShortEffect();
				break;
			}
			else if (JUDGEMENT->CheckNoteHit(6, i, Long_Start))
			{
				notes[i]->HitNote(true);
				longJudge[LANE6] = JUDGEMENT->CheckJudgement(i);
				longNotes[JUDGEMENT->FindLongNote(i)]->SetHold(true);
				effects[LANE6]->LongEffect(true);
				break;
			}
		}
	}

	//KeyUp
	if (KeyUp_Lane1)
	{
		for (UINT i = longprogress; i < longNotes.size() && i < (UINT)(longprogress + 100); i++)
			if (JUDGEMENT->CheckLongHold(1, i) && longNotes[i]->GetHold())
			{
				int index = JUDGEMENT->FindLongEnd(i);
				longNotes[i]->SetHold(false);
				if (JUDGEMENT->CheckJudgement(index) != BAD)
				{
					recentJudge = longJudge[LANE1];
					JUDGEMENT->SetJudge(recentJudge);
					notes[index]->HitNote(true);
					longNotes[i]->HitNote(true);
				}
				else
				{
					recentJudge = BAD;
					JUDGEMENT->SetJudge(recentJudge);
				}
				longJudge[LANE1] = NONE;
				effects[LANE1]->EndEffect();
				break;
			}
	}
	if (KeyUp_Lane2)
	{
		for (UINT i = longprogress; i < longNotes.size() && i < (UINT)(longprogress + 100); i++)
			if (JUDGEMENT->CheckLongHold(2, i) && longNotes[i]->GetHold())
			{
				int index = JUDGEMENT->FindLongEnd(i);
				longNotes[i]->SetHold(false);
				if (JUDGEMENT->CheckJudgement(index) != BAD)
				{
					recentJudge = longJudge[LANE2];
					JUDGEMENT->SetJudge(recentJudge);
					notes[index]->HitNote(true);
					longNotes[i]->HitNote(true);
				}
				else
				{
					recentJudge = BAD;
					JUDGEMENT->SetJudge(recentJudge);
				}
				longJudge[LANE2] = NONE;
				effects[LANE2]->EndEffect();
				break;
			}
	}
	if (KeyUp_Lane3)
	{
		for (UINT i = longprogress; i < longNotes.size() && i < (UINT)(longprogress + 100); i++)
			if (JUDGEMENT->CheckLongHold(3, i) && longNotes[i]->GetHold())
			{
				int index = JUDGEMENT->FindLongEnd(i);
				longNotes[i]->SetHold(false);
				if (JUDGEMENT->CheckJudgement(index) != BAD)
				{
					recentJudge = longJudge[LANE3];
					JUDGEMENT->SetJudge(recentJudge);
					notes[index]->HitNote(true);
					longNotes[i]->HitNote(true);
				}
				else
				{
					recentJudge = BAD;
					JUDGEMENT->SetJudge(recentJudge);
				}
				longJudge[LANE3] = NONE;
				effects[LANE3]->EndEffect();
				break;
			}
	}
	if (KeyUp_Lane4)
	{
		for (UINT i = longprogress; i < longNotes.size() && i < (UINT)(longprogress + 100); i++)
			if (JUDGEMENT->CheckLongHold(4, i) && longNotes[i]->GetHold())
			{
				int index = JUDGEMENT->FindLongEnd(i);
				longNotes[i]->SetHold(false);
				if (JUDGEMENT->CheckJudgement(index) != BAD)
				{
					recentJudge = longJudge[LANE4];
					JUDGEMENT->SetJudge(recentJudge);
					notes[index]->HitNote(true);
					longNotes[i]->HitNote(true);
				}
				else
				{
					recentJudge = BAD;
					JUDGEMENT->SetJudge(recentJudge);
				}
				longJudge[LANE4] = NONE;
				effects[LANE4]->EndEffect();
				break;
			}
	}
	if (KeyUp_Lane5)
	{
		for (UINT i = longprogress; i < longNotes.size() && i < (UINT)(longprogress + 100); i++)
			if (JUDGEMENT->CheckLongHold(5, i) && longNotes[i]->GetHold())
			{
				int index = JUDGEMENT->FindLongEnd(i);
				longNotes[i]->SetHold(false);
				if (JUDGEMENT->CheckJudgement(index) != BAD)
				{
					recentJudge = longJudge[LANE5];
					JUDGEMENT->SetJudge(recentJudge);
					notes[index]->HitNote(true);
					longNotes[i]->HitNote(true);
				}
				else
				{
					recentJudge = BAD;
					JUDGEMENT->SetJudge(recentJudge);
				}
				longJudge[LANE5] = NONE;
				effects[LANE5]->EndEffect();
				break;
			}
	}
	if (KeyUp_Lane6)
	{
		for (UINT i = longprogress; i < longNotes.size() && i < (UINT)(longprogress + 100); i++)
			if (JUDGEMENT->CheckLongHold(6, i) && longNotes[i]->GetHold())
			{
				int index = JUDGEMENT->FindLongEnd(i);
				longNotes[i]->SetHold(false);
				if (JUDGEMENT->CheckJudgement(index) != BAD)
				{
					recentJudge = longJudge[LANE6];
					JUDGEMENT->SetJudge(recentJudge);
					notes[index]->HitNote(true);
					longNotes[i]->HitNote(true);
				}
				else
				{
					recentJudge = BAD;
					JUDGEMENT->SetJudge(recentJudge);
				}
				longJudge[LANE6] = NONE;
				effects[LANE6]->EndEffect();
				break;
			}
	}
	for (UINT i = 0; i < longNotes.size(); i++)
	{
		int index = JUDGEMENT->FindLongEnd(i);
		if (index == -1)
			continue;

		if (JUDGEMENT->GetTiming(index) < Time::Get()->Running() && longNotes[i]->GetHold())
		{
			effects[JUDGEMENT->GetLine(index) - 1]->LongEffect(false);
		}
	}

	if (Judge temp = JUDGEMENT->CheckMiss())
	{
		recentJudge = temp;
	}

	accurate->DisplayJudge(recentJudge);
	accurate->Update();
	combo->Update();
	back->Update();
	if (JUDGEMENT->CheckFinish())
	{
		song->Stop();
		ChangeScene = true;
	}
	if (back->back)
	{
		song->Stop();
		back->back = false;
		BacktoMain = true;
	}

	song->Update();
}

void PlayScene::PreRender()
{
}

void PlayScene::Render()
{
	lane->Render();
	for (BeatLine* beatline : beatlines)
		beatline->Render();
	for (Light* laneLight : laneLights)
		laneLight->Render();
	judgementline->Render();
	for (UINT i = longprogress; i < longNotes.size() && i < (UINT)(longprogress + 50); i++)
		longNotes[i]->Render();
	for (UINT i = progress; i < notes.size() && i < (UINT)(progress + 50); i++)
		notes[i]->Render();
	frame->Render();
	for (Key* keyLight : keyLights)
		keyLight->Render();
	for (HitEffect* effect : effects)
		effect->Render();
	accurate->Render();
	combo->Render();
	back->Render();
}

void PlayScene::PostRender()
{
}
