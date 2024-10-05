#pragma once

class ResultUI : public TextureRect
{
public:
	ResultUI();
	~ResultUI();

	virtual void Update();
	void GUI();

private:
	Result result;
	string songname;
};