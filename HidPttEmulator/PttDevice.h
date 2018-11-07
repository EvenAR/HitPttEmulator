#pragma once
#include <Windows.h>
#include "MyForm.h"
#include "hidapi.h"

ref class UiController;

ref class PttDevice
{
public:
	PttDevice();
	void startListening(Object^ obj);
	void stopListening();
	WORD scancode;
	bool scancodeExtended;
private:
	hid_device *handle;
	bool run;
	
};

ref struct ButtonParameters
{
	UiController^ controller;
	int vid;
	int pid;
	int gpio_id;
	wchar_t* serial;
};