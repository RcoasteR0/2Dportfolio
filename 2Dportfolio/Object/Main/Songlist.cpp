#include "stdafx.h"
#include "stdafx.h"

Songlist::Songlist(Vector3 position, Info song, ImVec2 text)
	:TextureRect(position, { 500, 75, 1 }, 0)
	, song(song)
	, text(text)
{
	SetSRV(L"./_Textures/songlist.png");
}

Songlist::~Songlist()
{
}

void Songlist::SongSelect()
{
	Setting::Get()->SetCurrentSong(song);
	cout << "current song : " << song.Name << endl;
}

void Songlist::Update()
{
	mouse = { Mouse::Get()->GetPosition().x - WinMaxWidth / 2, Mouse::Get()->GetPosition().y - WinMaxHeight / 2, 0 };

	if (Mouse::Get()->Down(0) && Math::Intersect(this, mouse))
		SongSelect();
}

void Songlist::GUI()
{
	bool temp = true;
	if (ImGui::Begin(song.Name.c_str(), &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::SetWindowPos(text);
		ImGui::SetWindowSize({ 500, 70 });

		ImGui::SetWindowFontScale(3);
		ImGui::TextColored(ImVec4(0,0,0,1) ,song.Name.c_str());
		ImGui::SameLine();
		ImGui::SetWindowFontScale(1.5);
		ImGui::SetCursorPos({ ImGui::GetCursorPosX() + 10 ,ImGui::GetCursorPosY() + 15 });
		ImGui::TextColored(ImVec4(0,0,0,0.5f) ,song.Artist.c_str());
	}
	ImGui::End();
}
