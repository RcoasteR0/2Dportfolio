#include "stdafx.h"
#include "Judgement.h"

void Judgement::LoadChart(Info song)
{
	FinTime = FLT_MAX;
	Score = 0;
	BestCombo = 0;
	MaxCombo = 0;
	Progress = 0;
	LongProgress = 0;
	Combo = 0;
	Perfect = 0;
	Great = 0;
	Good = 0;
	Bad = 0;
	Miss = 0;

	line.clear();
	timing.clear();
	type.clear();
	holdTiming.clear();
	beatline.clear();

	ifstream in(song.Chart);
	char temp;
	wstring sChart = L"";

	if (in.is_open()) {
		while (true) {
			in >> temp;
			if (in.eof()) break;
			sChart.push_back(temp);
		}
		in.close();
	}
	vector<wstring> vChart;
	String::SplitString(&vChart, sChart, L"/");

	float BPM = test.BPM;
	int beat = 4;
	float term = 60 / BPM * 4 / beat;
	float time = song.NoteDelay + Setting::Get()->GetJudgementPos() + 0.23f;
	float beatterm = 0;
	for (wstring chart : vChart)
	{
		if (String::Contain(chart, L"(") && String::Contain(chart, L")"))
		{
			wchar_t temp[4] = L"\0";
			chart.copy(temp, chart.find(L")") - chart.find(L"(") - 1, chart.find(L"(") + 1);
			chart.erase(chart.find(L"("), chart.find(L")") - chart.find(L"(") + 1);
			BPM = (float)_wtof(temp);
			beatline.push_back(time);
			beatterm = 0;
		}
		if (String::Contain(chart, L"[") && String::Contain(chart, L"]"))
		{
			wchar_t temp[4] = L"\0";
			chart.copy(temp, chart.find(L"]") - chart.find(L"[") - 1, chart.find(L"[") + 1);
			chart.erase(chart.find(L"["), chart.find(L"]") - chart.find(L"[") + 1);
			beat = _wtoi(temp);
			beatline.push_back(time);
			beatterm = 0;
		}
		for (int i = 1; i < 7; i++)
		{
			if (String::Contain(chart, to_wstring(i)))
			{
				line.push_back(i);
				timing.push_back(time);
				if (chart.find(L"S") == chart.find(to_wstring(i)) + 1)
				{
					chart.erase(chart.find(to_wstring(i)), 2);
					type.push_back(Long_Start);
				}
				else if (chart.find(L"E") == chart.find(to_wstring(i)) + 1)
				{
					chart.erase(chart.find(to_wstring(i)) , 2);
					type.push_back(Long_End);
				}
				else
				{
					type.push_back(Short);
					++MaxCombo;
				}
			}
		}
		if (String::Contain(chart, L"F"))
		{
			FinTime = time;
		}
		term = 60 / BPM * 4 / beat;
		time += term;
		beatterm += 1.0f / beat;
		if (beatterm >= 1.0f)
		{
			beatline.push_back(time);
			beatterm = 0;
		}
	}

	for (UINT i = 0; i < line.size(); i++)
	{
		if (type[i] == Long_Start)
		{
			for (UINT j = i; j < line.size(); j++)
			{
				if (type[j] == Long_End && line[i] == line[j])
				{
					holdTiming.push_back({ line[i], timing[i], timing[j] });
					++MaxCombo;
					break;
				}
			}
		}
	}

	hit.assign(line.size(), false);

	NoteScore = MAX_SCORE / (float)MaxCombo;
}

Result Judgement::GetResult()
{
	Result temp{ Score, Perfect, Great, Good, Bad, Miss, BestCombo };
	return temp;
}

void Judgement::SetJudge(Judge judge)
{
	switch (judge)
	{
	case PERFECT:
		++Perfect;
		++Combo;
		break;
	case GREAT:
		++Great;
		++Combo;
		break;
	case GOOD:
		++Good;
		++Combo;
		break;
	case BAD:
		++Bad;
		Combo = 0;
		break;
	}

	cout << Combo << "Combo" << endl << endl;
	if (BestCombo < Combo)
		BestCombo = Combo;
}

void Judgement::CountScore()
{
	Score = NoteScore * (Perfect + Great * 0.7f + Good * 0.4f + Bad * 0.1f);
}

Achievement Judgement::CheckAchieve()
{
	if (MaxCombo == Perfect)
	{
		cout << "All Perfect!" << endl;
		return AllPerfect;
	}
	else if (MaxCombo == Combo)
	{
		cout << "Full Combo!" << endl;
		return FullCombo; 
	}
	else if (Miss == 0)
	{
		cout << "No Miss!" << endl;
		return NoMiss;
	}
	else 
		return Nothing;
}

bool Judgement::CheckNoteHit(int line, int index, NoteType type)
{
	float time = Time::Get()->Running() - timing[index];

	if (time > -JUDGE_TIME * 4 && time < JUDGE_TIME * 4 && line == this->line[index] && type == this->type[index])
		return true;

	return false;
}

bool Judgement::CheckLongHold(int line, int index)
{
	if (Time::Get()->Running() > holdTiming[index].Start - JUDGE_TIME * 4 &&
		Time::Get()->Running() < holdTiming[index].End + JUDGE_TIME * 4 &&
		line == holdTiming[index].line)
		return true;

	return false;
}

int Judgement::FindLongNote(int index)
{
	for (UINT i = LongProgress; i < holdTiming.size() && i < (UINT)(LongProgress + 100); i++)
		if (timing[index] == holdTiming[i].Start && line[index] == holdTiming[i].line)
			return i;

	return -1;
}

int Judgement::FindLongEnd(int index)
{
	for (UINT i = Progress; i < timing.size() && i < (UINT)(Progress + 100); i++)
		if (holdTiming[index].End == timing[i] && type[i] == Long_End && holdTiming[index].line == line[i])
			return i;

	return -1;
}

Judge Judgement::CheckJudgement(int index)
{
	float time = Time::Get()->Running() - timing[index];
	hit[index] = true;

	if (time > -JUDGE_TIME && time < JUDGE_TIME)
	{
		cout << "Perfect(" << time << ")" << endl;
		return PERFECT;
	}
	else if (time > -JUDGE_TIME * 2 && time < JUDGE_TIME * 2)
	{
		cout << "Great(" << time << ")" << endl;
		return GREAT;
	}
	else if (time > -JUDGE_TIME * 3 && time < JUDGE_TIME * 3)
	{
		cout << "Good(" << time << ")" << endl;
		return GOOD;
	}
	else
	{
		cout << "Bad(" << time << ")" << endl;
		return BAD;
	}
}

Judge Judgement::CheckMiss()
{
	for (UINT i = Progress; i < timing.size() && i < (UINT)(Progress + 100); i++)
	{
		float time = Time::Get()->Running() - timing[i];

		if (time > 0.5f)
		{
			Progress++;
			if (type[i] == Long_End)
				LongProgress++;
		}
		else if (time > JUDGE_TIME * 6)
		{
			if (type[i] == Long_End)
			{
				if (!hit[i])
				{
					++Bad;
					Combo = 0;
					cout << "Bad" << endl;
					cout << Combo << "Combo" << endl << endl;
					hit[i] = true;
					return BAD;
				}
			}
			if (!hit[i])
			{
				++Miss;
				Combo = 0;
				cout << "Miss" << endl;
				cout << Combo << "Combo" << endl << endl;
				if (type[i] == Long_Start)
				{
					hit[FindLongEnd(FindLongNote(i))] = true;
				}
				hit[i] = true;
				return MISS;
			}
		}
	}
	return NONE;
}

void Judgement::Initialize(int index)
{
	timing[index] = FLT_MAX;
}

void Judgement::Update()
{

}
