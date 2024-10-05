#pragma once
enum BackButtonType
{
	Button_Back,
	Button_Home
};

class BackMain : public TextureRect
{
public:
	BackMain(Vector3 position, BackButtonType type);
	~BackMain();

	virtual void Update();

	bool back;
private:
};