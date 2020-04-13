#pragma once
#include <Windows.h>

ref class KeyEmulator
{
private:
	INPUT* input;
	WORD scanCode;
	bool scancodeExtended;
	DWORD baseFlags;

public:
	KeyEmulator();
	void setKey(WORD scanCode, bool extended);
	void emulatePress();
	void emulateRelease();
};

