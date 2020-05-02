#pragma once
#include "MyForm.h"
#include "hidapi.h"

ref class Controller;
ref class KeyEmulator;

#define REPORT_NUMBER 0

ref class PttDevice
{
public:
	PttDevice();
	void startListening(Object^ obj);
	void stopListening();

private:
	hid_device *hidHandle;
	bool run;
	
};

ref struct DeviceParameters
{
	Controller^ controller;
	int vid;
	int pid;
	int gpio_pin;
	bool reverseInput;
	wchar_t* serial;
};