#include "stdafx.h"
#include "Frame.h"
#include "Geometry/TextureRect.h"

Frame::Frame()
	:TextureRect({ 0, 0, 0 }, { 300, WinMaxHeight, 1 }, 0)
{
	SetSRV(L"./_Textures/frame.png");
}

Frame::~Frame()
{
}

void Frame::Update()
{
	
}
