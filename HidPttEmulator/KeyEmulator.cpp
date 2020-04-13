#include "KeyEmulator.h"

KeyEmulator::KeyEmulator() {
	this->input = new INPUT;
	this->input->type = INPUT_KEYBOARD;
	this->input->ki.time = 0;
	this->input->ki.wVk = 0; //We're doing scan codes instead
	this->input->ki.dwExtraInfo = 0;
}

void KeyEmulator::emulatePress() {
	this->input->ki.dwFlags = this->baseFlags;
	SendInput(1, this->input, sizeof(INPUT));
}

void KeyEmulator::emulateRelease() {
	this->input->ki.dwFlags = this->baseFlags | KEYEVENTF_KEYUP;
	SendInput(1, this->input, sizeof(INPUT));
}

void KeyEmulator::setKey(WORD scanCode, bool extended) {
	this->input->ki.wScan = scanCode;
	this->scancodeExtended = extended;
	this->baseFlags = extended ? KEYEVENTF_SCANCODE | KEYEVENTF_EXTENDEDKEY : KEYEVENTF_SCANCODE;
}