#include "stdafx.h"
#include "SongInfo.h"

SongInfo::SongInfo()
	:TextureRect({ 320, 180, 0 }, { 600, 300, 1 }, 0)
{
	SetSRV(L"./_Textures/songInfo.png");
}

SongInfo::~SongInfo()
{
}

void SongInfo::Update()
{
	Info song = Setting::Get()->GetCurrentSong();
	name = "Name : " + song.Name;
	artist = "Artist : " + song.Artist;
	bpm = "BPM : " + to_string(int(song.BPM));
	level = "LV : " + to_string(song.Level);
}

void SongInfo::GUI()
{
	bool temp = true;
	if (ImGui::Begin("SongInfo", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMouseInputs))
	{
		ImGui::SetWindowPos({ 680, 50 });
		ImGui::SetWindowSize({ size.x, size.y });
		ImGui::SetWindowFontScale(2.25f);

		ImGui::Text(name.c_str());
		ImGui::NewLine();
		ImGui::Text(artist.c_str());
		ImGui::NewLine();
		ImGui::Text(bpm.c_str());
		ImGui::NewLine();
		ImGui::Text(level.c_str());
	}
	ImGui::End();
}
