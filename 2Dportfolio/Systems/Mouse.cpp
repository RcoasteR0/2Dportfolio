#include "stdafx.h"
#include "Mouse.h"

Mouse::Mouse()
{
	position = Vector3(0.0f, 0.0f, 0.0f);

	wheelStatus = Vector3(0.0f, 0.0f, 0.0f);
	wheelOldStatus = Vector3(0.0f, 0.0f, 0.0f);
	wheelMoveValue= Vector3(0.0f, 0.0f, 0.0f);

	ZeroMemory(buttonStatus, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonOldStatus, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonMap, sizeof(byte) * MAX_INPUT_MOUSE);
	
	ZeroMemory(startDblclk, sizeof(DWORD) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonCount, sizeof(int) * MAX_INPUT_MOUSE);

	timeDblclk = GetDoubleClickTime();
	startDblclk[0] = GetTickCount();

	for (int i = 1; i < MAX_INPUT_MOUSE; ++i)
		startDblclk[i] = startDblclk[0];

	DWORD tLine = 0;
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &tLine, 0);
}

Mouse::~Mouse()
{
}

void Mouse::Update()
{
	memcpy(buttonOldStatus, buttonStatus, sizeof(buttonOldStatus));

	ZeroMemory(buttonStatus, sizeof(buttonStatus));
	ZeroMemory(buttonMap, sizeof(buttonMap));

	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;

	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		int tOldStatus = buttonOldStatus[i];
		int tStatus = buttonStatus[i];

		if (tOldStatus == 0 && tStatus == 1)
			buttonMap[i] = BUTTON_INPUT_STATUS_DOWN;
		else if (tOldStatus == 1 && tStatus == 0)
			buttonMap[i] = BUTTON_INPUT_STATUS_UP;
		else if (tOldStatus == 1 && tStatus == 1)
			buttonMap[i] = BUTTON_INPUT_STATUS_PRESS;
		else
			buttonMap[i] = BUTTON_INPUT_STATUS_NONE;
	}

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(handle, &point);
	
	wheelOldStatus.x = wheelStatus.x;
	wheelOldStatus.y = wheelStatus.y;

	wheelStatus.x = float(point.x);
	wheelStatus.y = float(point.y);

	wheelMoveValue = wheelStatus - wheelOldStatus;
	wheelOldStatus.z = wheelStatus.z;

	DWORD tButtonStatus = GetTickCount();
	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		if (buttonMap[i] == 1)
		{
			if ((tButtonStatus - startDblclk[i]) >= timeDblclk)
				buttonCount[i] = 0;

			buttonCount[i]++;


			if (buttonCount[i] == 1)
				startDblclk[i] = tButtonStatus;
		}


		if (buttonMap[i] == BUTTON_INPUT_STATUS_UP)
		{
			if ((tButtonStatus - startDblclk[i]) >= timeDblclk)
				buttonCount[i] = 0;
			else if (buttonCount[i] == 2)
			{
				if ((tButtonStatus - startDblclk[i]) < timeDblclk)
					buttonMap[i] = BUTTON_INPUT_STATUS_DBLCLK;

				buttonCount[i] = 0;
			}
		}//if
	}//for(i)
}


LRESULT Mouse::inputProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN || message == WM_MOUSEMOVE)
	{
		position.x = (float)LOWORD(lParam);
		position.y = WinMaxHeight - (float)HIWORD(lParam);
	}

	if (message == WM_MOUSEHWHEEL)
	{
		short tWheelValue = (short)HIWORD(wParam);

		wheelOldStatus.z = wheelStatus.z;
		wheelStatus.z += (float)tWheelValue;
	}
	
	return LRESULT();
}