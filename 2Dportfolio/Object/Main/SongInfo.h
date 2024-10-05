#pragma once

class SongInfo : public TextureRect
{
public:
	SongInfo();
	~SongInfo();

	virtual void Update();

	void GUI();

private:

	string name;
	string artist;
	string bpm;
	string level;

	const Vector3 position { 320, 180, 0 };
	const Vector3 size { 600, 300, 1 };
};