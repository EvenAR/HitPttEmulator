#include "PttDevice.h"
#include "Controller.h"

#define BIT_IS_SET(var, bit) ((1 << bit - 1) & var)

PttDevice::PttDevice() {
}

void PttDevice::startListening(Object^obj)
{
	OutputDebugString("Starting\n");
	DeviceParameters^ bp = (DeviceParameters^)obj;
	Controller^ controller = bp->controller;
	unsigned char buffer[17];
	
	run = true;
	
	while (run)
	{
		hidHandle = hid_open(bp->vid, bp->pid, bp->serial);

		if (!hidHandle) {
			Sleep(500);
			continue;
		}

		controller->onPttDeviceConnected();

		memset(buffer, 0x00, sizeof(buffer));
		
		int result;
		bool previousState = true;
		while (run) {
			buffer[0] = REPORT_NUMBER;
			result = hid_get_input_report(hidHandle, buffer, 9);

			if (result < 0) {
				controller->onPttDeviceLost();
				break;
			}

			if (buffer[0] == REPORT_NUMBER) {
				bool input = BIT_IS_SET(buffer[2], bp->gpio_pin);
				bool isPressed = bp->reverseInput ? !input : input;

				if (isPressed != previousState) {
					isPressed ? bp->controller->onPttReleased() : controller->onPttPressed();
					previousState = isPressed;
				}
			}
			Sleep(10);
		}

		hid_close(hidHandle);
		hid_exit();
	}
}

void PttDevice::stopListening()
{
	run = false;
}