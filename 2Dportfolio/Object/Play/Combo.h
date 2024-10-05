#pragma once

class Combo : public TextureRect
{
public:
	Combo();
	~Combo();

	virtual void Update();
	virtual void Render();

private:
	float display;
	int combo;
	vector<int> num;
	vector<wstring> texture;

	const Vector3 position = { 0, 200, 0 };
	const Vector3 size = { 30, 40, 1 };
};