#include "stdafx.h"
#include "Light.h"
#include "Geometry/TextureRect.h"

Light::Light(Vector3 position, Vector3 size, Button color)
	:TextureRect(position, size, 0)
{
	switch (color)
	{
	case(White_Lane):
		SetSRV(L"./_Textures/white_lane_glow.png");
		break;
	case(Black_Lane):
		SetSRV(L"./_Textures/black_lane_glow.png");
		break;
	}
}

Light::~Light()
{
}

void Light::Update()
{
	InvisibleTexture(!press);
}
