#pragma once

class StartButton : public TextureRect
{
public:
	StartButton();
	~StartButton();

	virtual void Update();

	bool start;
};