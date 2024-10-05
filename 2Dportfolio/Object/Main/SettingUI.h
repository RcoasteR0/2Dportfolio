#pragma once

class SettingUI
{
public:
	SettingUI();
	~SettingUI();

	void GUI();

private:
	float speed;
	float timing;
	int line;
	Effect effect;
	Random random;
};