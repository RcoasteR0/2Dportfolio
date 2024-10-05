#pragma once
enum Button
{
	White_Lane,
	Black_Lane
};

class Key : public TextureRect
{
public:
	Key(Vector3 position, Vector3 size, Button color);
	~Key();

	virtual void Update();

	void setPress(bool press) { this->press = press; }

private:
	bool press = false;
};