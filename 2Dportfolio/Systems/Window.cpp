#include "stdafx.h"
#include "window.h"
#include "../Program.h"

WinDesc Window::desc;
Program* Window::program = nullptr;
Graphics* Window::graphics = nullptr;

HINSTANCE instance;
Window::Window(WinDesc desc)
{
	WNDCLASSEX wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = desc.instance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);


	WORD wHr = RegisterClassEx(& wndClass);
	assert(wHr != 0);

	desc.handle = CreateWindowEx
	(
		WS_EX_APPWINDOW
		, desc.AppName.c_str()
		, desc.AppName.c_str()
		, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, NULL
		, (HMENU)NULL
		, desc.instance
		, NULL
	);

	RECT rect = { 0, 0, (LONG)desc.width, (LONG)desc.height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow
	(
		desc.handle
		, centerX
		, centerY
		, rect.right - rect.left, rect.bottom - rect.top
		, TRUE
	);

	ShowWindow(desc.handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.handle);
	SetFocus(desc.handle);

	ShowCursor(true);

	Window::desc = desc;
	instance = desc.instance;
}

Window::~Window()
{
	DestroyWindow(desc.handle);
	UnregisterClass(desc.AppName.c_str(), desc.instance);
}

WPARAM Window::Run()
{
	MSG msg = { 0 };

	Graphics::Create();
	Keyboard::Create();
	Mouse::Create();
	Time::Create();
	Gui::Create();
	Setting::Create();
	Judgement::Create();

	Time::Get()->Start();

	program = new Program();
	program->Init();

	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Time::Get()->Update();
			if (ImGui::IsMouseHoveringAnyWindow() == false)
			{
				Keyboard::Get()->Update();
				Mouse::Get()->Update();
			}
			Gui::Get()->Update();
			

			program->Update();

			program->PreRender();
			Graphics::Get()->Begin();
			{
				program->Render();
				program->PostRender();
				Gui::Get()->Render();
			}
			Graphics::Get()->End();
		}
	}
	SAFE_DELETE(program);

	Judgement::Delete();
	Setting::Delete();
	Gui::Delete();
	Time::Delete();
	Mouse::Delete();
	Keyboard::Delete();
	Graphics::Delete();

	return msg.wParam;
}

HWND handle;
LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	Mouse::Get()->inputProc(message, wParam, lParam);
	if (Gui::Get()->MsgProc(handle, message, wParam, lParam))
		return true;
	
	if (message == WM_CREATE)
		::handle = handle;

	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
