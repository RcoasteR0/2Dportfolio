#pragma once

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	void Init() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	vector<Songlist*> songs;
	SongInfo* info;
	SettingUI* setting;
	StartButton* start;
};