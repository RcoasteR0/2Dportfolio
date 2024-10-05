#include "stdafx.h"
#include "SettingUI.h"

SettingUI::SettingUI()
{
	speed = Setting::Get()->GetNoteSpeed();
	timing = Setting::Get()->GetJudgementPos();
	line = Setting::Get()->GetJudgementLinePos();
	effect = Setting::Get()->GetNoteEffect();
	random = Setting::Get()->GetNoteRandom();
}

SettingUI::~SettingUI()
{
}

void SettingUI::GUI()
{
	bool temp = true;
	string Cspeed = to_string((int)speed) + "." + to_string((int)(speed * 10) - (int)speed * 10);
	string Ctiming;
	if(timing > -1 && timing < 0)
		Ctiming = "-" + to_string((int)timing) + "." + to_string(-((int)(timing * 10) - (int)timing * 10));
	else if(timing <= -1)
		Ctiming = to_string((int)timing) + "." + to_string(-((int)(timing * 10) - (int)timing * 10));
	else
		Ctiming = to_string((int)timing) + "." + to_string((int)(timing * 10) - (int)timing * 10);

	using namespace ImGui;
	if (Begin("SettingUI", &temp, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
	{
		SetWindowPos({ 660, 350 });
		SetWindowSize({ 600, 200 });

		SetCursorPos({ 30,20 });
		SetWindowFontScale(2);
		Text("Speed");
		SameLine();
		SetCursorPosX(GetCursorPosX() + 20);
		Text("Timing");
		SameLine();
		SetCursorPosX(GetCursorPosX() + 30);
		Text("Line");

		SetWindowFontScale(2);
		SetCursorPos({GetCursorPosX() + 40, GetCursorPosY() + 10});
		if (ArrowButton("speed up", ImGuiDir_Up))
		{
			if (speed < 9)
				speed += 0.1f;
		}
		SameLine();
		SetCursorPosX(GetCursorPosX() + 60);
		if (ArrowButton("timing up", ImGuiDir_Up))
		{
			if (timing < 0.2)
				timing += 0.01f;
		}
		SameLine();
		SetCursorPosX(GetCursorPosX() + 60);
		if(ArrowButton("line up", ImGuiDir_Up))
			line += 10;

		SetWindowFontScale(1.5f);
		SetCursorPosX(GetCursorPosX() + 39);
		ImGui::Button(to_string(speed).c_str(), { 38,30 });
		SameLine();
		SetCursorPosX(GetCursorPosX() + 46);
		ImGui::Button(to_string(timing).c_str(), { 58,30 });
		SameLine();
		SetCursorPosX(GetCursorPosX() + 46);
		ImGui::Button(to_string(line).c_str(), { 48,30 });

		SetWindowFontScale(2);
		SetCursorPosX(GetCursorPosX() + 40);
		if (ArrowButton("speed down", ImGuiDir_Down))
		{
			if (speed > 1)
				speed -= 0.1f;
		}
		SameLine();
		SetCursorPosX(GetCursorPosX() + 60);
		if (ArrowButton("timing down", ImGuiDir_Down))
		{
			if (timing > -0.2)
				timing -= 0.01f;
		}
		SameLine();
		SetCursorPosX(GetCursorPosX() + 60);
		if (ArrowButton("line down", ImGuiDir_Down))
			line -= 10;

	}
	End();

	Setting::Get()->SetNoteSpeed(speed);
	Setting::Get()->SetJudgementPos(timing);
	Setting::Get()->SetJudgementLinePos(line);
}
