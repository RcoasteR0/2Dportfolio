#pragma once

class Note : public TextureRect
{
public:
	Note(int line, float timing, NoteType type);
	~Note();

	void HitNote(bool hit) { this->hit = hit; }

	virtual void Update();

private:
	bool hit = false;
};