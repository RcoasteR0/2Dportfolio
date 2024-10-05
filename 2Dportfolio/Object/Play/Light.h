#pragma once

class Light : public TextureRect
{
public:
	Light(Vector3 position, Vector3 size, Button color);
	~Light();

	virtual void Update();

	void setPress(bool press) { this->press = press; }

private:
	bool press = false;
};