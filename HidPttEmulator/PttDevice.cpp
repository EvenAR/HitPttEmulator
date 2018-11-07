#include "PttDevice.h"
#include "UiController.h"

PttDevice::PttDevice()
{
}

void PttDevice::startListening(Object^obj)
{
	OutputDebugString("Starting\n");
	ButtonParameters^ bp = (ButtonParameters^)obj;
	UiController^ controller = bp->controller;
	run = true;
	
	while (run) 
	{
		handle = hid_open(bp->vid, bp->pid, bp->serial);
		OutputDebugString("Running\n");
		//handle = hid_open_path("\\\\?\\hid#vid_0d8c&pid_0008&mi_03#8&171c3164&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}");
		if (!handle) {
			Sleep(500);
			continue;
		}
		
		controller->onPttDeviceConnected();

		unsigned char buf[256];
		memset(buf, 0, sizeof(buf));
		buf[0] = 0x1;
		buf[1] = 0x81;

		// KEYBOARD KEY //////////////////////////
		INPUT input;
		//input.type = INPUT_KEYBOARD;
		input.type = INPUT_KEYBOARD;
		input.ki.time = 0;
		input.ki.wVk = 0; //We're doing scan codes instead
		input.ki.dwExtraInfo = 0;

		input.ki.wScan = this->scancode; //MapVirtualKey(VK_CONTROL, MAPVK_VK_TO_VSC);;
		//////////////////////////////////////////


		int res;
		while (run) {
			OutputDebugString("Open!!!!!!!!!\n");
			res = 0;
			while (res == 0 && run) {
				res = hid_read_timeout(handle, buf, sizeof(buf), 500);
				if (res < 0) {
					controller->onPttDeviceLost();
					break;
				}

			}
			if (res < 0) {
				break;
			}
			
			input.ki.wScan = this->scancode;
			bool extendedKey = this->scancodeExtended;

			if (buf[0] == 0) {
				if (buf[1] == bp->gpio_id) {
					if (extendedKey)
						input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_EXTENDEDKEY;				// key down
					else
						input.ki.dwFlags = KEYEVENTF_SCANCODE;

					SendInput(1, &input, sizeof(INPUT));
					controller->onPttPressed();
				}
				else {
					if (extendedKey)
						input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
					else
						input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					
					SendInput(1, &input, sizeof(INPUT));
					controller->onPttReleased();
				}
			}
		}

		hid_close(handle);
		hid_exit();
	}
}

void PttDevice::stopListening()
{
	run = false;
}