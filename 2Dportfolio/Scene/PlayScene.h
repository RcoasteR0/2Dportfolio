#pragma once

#define LANE1 0
#define LANE2 1
#define LANE3 2
#define LANE4 3
#define LANE5 4
#define LANE6 5

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	void Init() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	Info CurrentSong;

	Lane* lane;
	Frame* frame;
	JudgementLine* judgementline;
	Accurate* accurate;
	Combo* combo;
	BackMain* back;
	vector<Key*> keyLights;
	vector<Light*> laneLights;
	vector<HitEffect*> effects;
	vector<Note*> notes;
	vector<LongNote*> longNotes;
	vector<BeatLine*> beatlines;

	SoundSystem* song;

	bool loading;
	bool play;
	int progress;
	int longprogress;
	vector<Judge> longJudge;
};