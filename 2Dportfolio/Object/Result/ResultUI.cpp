#include "stdafx.h"
#include "ResultUI.h"

ResultUI::ResultUI()
	:TextureRect({ 0,0,0 }, { 1280,720,1 },0)
{
	SetSRV(L"./_Textures/result_bg.png");
	
	JUDGEMENT->CountScore();
	result = JUDGEMENT->GetResult();
	songname = Setting::Get()->GetCurrentSong().Name;
	cout << "Perfect : " << result.Perfect << endl;
	cout << "Great : " << result.Great << endl;
	cout << "Good : " << result.Good << endl;
	cout << "Bad : " << result.Bad << endl;
	cout << "Miss : " << result.Miss << endl;
	cout << "Max Combo : " << result.BestCombo << endl;
	cout << "Score : " << result.Score << endl;
}

ResultUI::~ResultUI()
{
}

void ResultUI::Update()
{
}

void ResultUI::GUI()
{
	bool temp = true;
	if (ImGui::Begin("score", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::SetWindowPos({ 566, 186 });
		ImGui::SetWindowSize({ 300, 50 });

		ImGui::SetWindowFontScale(3);
		ImGui::TextColored({ 1, 1, 1, 1 }, to_string(result.Score).c_str());
	}
	ImGui::End();

	if (ImGui::Begin("perfect", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::SetWindowPos({ 566, 236 });
		ImGui::SetWindowSize({ 300, 50 });

		ImGui::SetWindowFontScale(3);
		ImGui::TextColored({ 1, 1, 1, 1 }, to_string(result.Perfect).c_str());
	}
	ImGui::End();

	if (ImGui::Begin("great", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::SetWindowPos({ 566, 286 });
		ImGui::SetWindowSize({ 300, 50 });

		ImGui::SetWindowFontScale(3);
		ImGui::TextColored({ 1, 1, 1, 1 }, to_string(result.Great).c_str());
	}
	ImGui::End();

	if (ImGui::Begin("good", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::SetWindowPos({ 566, 336 });
		ImGui::SetWindowSize({ 300, 50 });

		ImGui::SetWindowFontScale(3);
		ImGui::TextColored({ 1, 1, 1, 1 }, to_string(result.Good).c_str());
	}
	ImGui::End();

	if (ImGui::Begin("bad", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::SetWindowPos({ 566, 386 });
		ImGui::SetWindowSize({ 300, 50 });

		ImGui::SetWindowFontScale(3);
		ImGui::TextColored({ 1, 1, 1, 1 }, to_string(result.Bad).c_str());
	}
	ImGui::End();

	if (ImGui::Begin("miss", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::SetWindowPos({ 566, 436 });
		ImGui::SetWindowSize({ 300, 50 });

		ImGui::SetWindowFontScale(3);
		ImGui::TextColored({ 1, 1, 1, 1 }, to_string(result.Miss).c_str());
	}
	ImGui::End();

	if (ImGui::Begin("max combo", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::SetWindowPos({ 566, 486 });
		ImGui::SetWindowSize({ 300, 50 });

		ImGui::SetWindowFontScale(3);
		ImGui::TextColored({ 1, 1, 1, 1 }, to_string(result.BestCombo).c_str());
	}
	ImGui::End();
}
