#pragma once

class ResultScene : public Scene
{
public:
	ResultScene();
	~ResultScene();

	void Init() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	ResultUI* result;
	BackMain* home;

};