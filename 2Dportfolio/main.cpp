#include "stdafx.h"
#include "Systems/Window.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((unsigned int)time(NULL));

	WinDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Window* window = new Window(desc);
	WPARAM wParam = window->Run();
	delete(window);

	return wParam;
}