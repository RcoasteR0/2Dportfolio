#include "stdafx.h"
#include "Lane.h"
#include "Geometry/TextureRect.h"

Lane::Lane()
	:TextureRect({ 0, 0, 0 }, { 300, WinMaxHeight, 1 }, 0)
{
	SetSRV(L"./_Textures/lane.png");
}

Lane::~Lane()
{
}

void Lane::Update()
{
	
}
