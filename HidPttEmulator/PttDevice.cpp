#include "PttDevice.h"
#include "Controller.h"


PttDevice::PttDevice() {
}

void PttDevice::startListening(Object^obj)
{
	OutputDebugString("Starting\n");
	DeviceParameters^ bp = (DeviceParameters^)obj;
	Controller^ controller = bp->controller;
	unsigned char buffer[256];
	run = true;

	while (run) 
	{
		hidHandle = hid_open(bp->vid, bp->pid, bp->serial);
		
		if (!hidHandle) {
			Sleep(500);
			continue;
		}
		
		controller->onPttDeviceConnected();
		
		// Set up the command buffer.
		memset(buffer, 0x00, sizeof(buffer));
		buffer[0] = 0x0;
		buffer[1] = 0x81;
		
		int result;
		while (run) {
			result = 0;
			while (result == 0 && run) {
				result = hid_read(hidHandle, buffer, 256);
				if (result < 0) {
					controller->onPttDeviceLost();
					break;
				}
			}
			if (result < 0) {
				break;
			}

			if (buffer[0] == REPORT_NUMBER) {
				if (buffer[1] == bp->gpio_id) {
					controller->onPttPressed();
				}
				else {
					controller->onPttReleased();
				}
			}
		}

		hid_close(hidHandle);
		hid_exit();
	}
}

void PttDevice::stopListening()
{
	run = false;
}