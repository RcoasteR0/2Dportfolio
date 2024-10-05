#include "stdafx.h"
#include "Key.h"
#include "Geometry/TextureRect.h"

Key::Key(Vector3 position, Vector3 size, Button color)
	:TextureRect(position, size, 0)
{
	switch (color)
	{
	case(White_Lane):
		SetSRV(L"./_Textures/white_key_glow.png");
		break;
	case(Black_Lane):
		SetSRV(L"./_Textures/black_key_glow.png");
		break;
	}
}

Key::~Key()
{
}

void Key::Update()
{
	InvisibleTexture(!press);
}
