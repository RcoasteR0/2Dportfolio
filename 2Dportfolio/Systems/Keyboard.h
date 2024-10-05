#pragma once

#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8

#define KeyDown_Up Keyboard::Get()->Down('W')
#define KeyDown_Down Keyboard::Get()->Down('S')
#define KeyDown_Left Keyboard::Get()->Down('A')
#define KeyDown_Right Keyboard::Get()->Down('D')

#define KeyPress_Up Keyboard::Get()->Press('W')
#define KeyPress_Down Keyboard::Get()->Press('S')
#define KeyPress_Left Keyboard::Get()->Press('A')
#define KeyPress_Right Keyboard::Get()->Press('D')

#define KeyDown_Lane1 Keyboard::Get()->Down('A')
#define KeyDown_Lane2 Keyboard::Get()->Down('S')
#define KeyDown_Lane3 Keyboard::Get()->Down('D')
#define KeyDown_Lane4 Keyboard::Get()->Down('L')
#define KeyDown_Lane5 Keyboard::Get()->Down(VK_OEM_1)
#define KeyDown_Lane6 Keyboard::Get()->Down(VK_OEM_7)

#define KeyPress_Lane1 Keyboard::Get()->Press('A')
#define KeyPress_Lane2 Keyboard::Get()->Press('S')
#define KeyPress_Lane3 Keyboard::Get()->Press('D')
#define KeyPress_Lane4 Keyboard::Get()->Press('L')
#define KeyPress_Lane5 Keyboard::Get()->Press(VK_OEM_1)
#define KeyPress_Lane6 Keyboard::Get()->Press(VK_OEM_7)

#define KeyUp_Lane1 Keyboard::Get()->Up('A')
#define KeyUp_Lane2 Keyboard::Get()->Up('S')
#define KeyUp_Lane3 Keyboard::Get()->Up('D')
#define KeyUp_Lane4 Keyboard::Get()->Up('L')
#define KeyUp_Lane5 Keyboard::Get()->Up(VK_OEM_1)
#define KeyUp_Lane6 Keyboard::Get()->Up(VK_OEM_7)

class Keyboard : public Singleton<Keyboard>
{
public:
	friend class Singleton<Keyboard>;

	void Update();
	
	bool Down(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool Up(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool Press(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }
private:
	Keyboard();
	~Keyboard();

	static Keyboard* instance;

	byte keyState[MAX_INPUT_KEY];
	byte keyOldState[MAX_INPUT_KEY];
	byte keyMap[MAX_INPUT_KEY];

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS
	};
};