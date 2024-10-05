#pragma once

#define JUDGE_TIME 0.03334f
#define MAX_SCORE 1000000.0f

enum Judge
{
	NONE = 0,
	PERFECT,
	GREAT,
	GOOD,
	BAD,
	MISS
};

enum NoteType
{
	Short,
	Long_Start,
	Long_Hold,
	Long_End
};

enum Achievement
{
	Nothing = 0,
	NoMiss,
	FullCombo,
	AllPerfect
};

struct HoldTime
{
	int line;
	float Start;
	float End;
};

struct Result
{
	int Score, Perfect, Great, Good, Bad, Miss, BestCombo;
};

class Judgement : public Singleton<Judgement>
{
public:
	void LoadChart(Info song);

	int GetNoteCount() { return timing.size(); }
	int GetHoldCount() { return holdTiming.size(); }
	int GetLine(int index) { return line[index]; }
	int GetProgress() { return Progress; }
	int GetLongProgress() { return LongProgress; }
	int GetCombo() { return Combo; }
	float GetTiming(int index) { return timing[index]; }
	NoteType GetType(int index) { return type[index]; }
	HoldTime GetHoldTime(int index) { return holdTiming[index]; }
	vector<float> GetBeatline() { return beatline; }
	Result GetResult();
	
	void SetJudge(Judge judge);
	void CountScore();
	Achievement CheckAchieve();

	bool CheckFinish() { return Time::Get()->Running() > FinTime; }
	bool CheckNoteHit(int line, int index, NoteType type);
	bool CheckLongHold(int line, int index);
	int FindLongNote(int index);
	int FindLongEnd(int index);
	Judge CheckJudgement(int index);
	Judge CheckMiss();

	void Initialize(int index);

	void Update();

private:
	int Perfect;
	int Great;
	int Good;
	int Bad;
	int Miss;
	int Combo;
	int Progress;
	int LongProgress;
	int MaxCombo;
	int BestCombo;
	float NoteScore;
	float Score;
	float FinTime;

	vector<bool> hit;
	vector<int> line;
	vector<float> timing;
	vector<float> beatline;
	vector<HoldTime> holdTiming;
	vector<NoteType> type;
};