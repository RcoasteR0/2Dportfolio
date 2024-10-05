#pragma once

class Songlist : public TextureRect
{
public:
	Songlist(Vector3 position, Info song, ImVec2 text);
	~Songlist();

	void SongSelect();

	virtual void Update();

	void GUI();

private:
	Info song;
	Vector3 mouse;
	ImVec2 text;
};