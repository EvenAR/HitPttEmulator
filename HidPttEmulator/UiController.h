#pragma once
#include "PttDevice.h"
#include "MyForm.h"

#include <vcclr.h>
#include <sstream>

using namespace System::Threading;

ref class UiController
{
private:
	HidPttEmulator::MyForm^ form;
	PttDevice^ button;
	char* iniFilePath;
	Thread^ t1;

public:
	UiController(PttDevice^ button, HidPttEmulator::MyForm^ form);
	void onFormClosing(System::Object ^sender, System::Windows::Forms::FormClosingEventArgs ^e);

	void onPttPressed();
	void onPttReleased();
	void onPttDeviceLost();
	void onPttDeviceConnected();
	void setEmulationKey(WORD scancode, bool extended);


private: 
	System::Void setKeyButton_Click(System::Object^  sender, System::EventArgs^  e) {
		form->textBox1->Text = "Press a key...";

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			if (msg.message == WM_KEYDOWN) {
				int scancode = (msg.lParam & 0x01FF0000) >> 16;
				bool extended = msg.lParam & 0x01000000;
				setEmulationKey(scancode, extended);
				return;
			}
		}
	};

	System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		form->comboBox2->Enabled = false;
		form->setKeyButton->Enabled = true;
		form->textBox1->Enabled = true;

		if (form->radioButton1->Checked) {
			char buf[16];
			WritePrivateProfileString(TEXT("USER_SETTINGS"), TEXT("custom"), itoa(1, buf, 10), iniFilePath);
			int keyFromFile = GetPrivateProfileInt(TEXT("USER_SETTINGS"), TEXT("key"), 0, TEXT(iniFilePath));
			bool extendedFromFile = GetPrivateProfileInt(TEXT("USER_SETTINGS"), TEXT("ex"), 0, TEXT(iniFilePath));
			setEmulationKey(keyFromFile, extendedFromFile);
		}
	};

	System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		form->comboBox2->Enabled = true;
		form->setKeyButton->Enabled = false;
		form->textBox1->Enabled = false;

		if (form->radioButton2->Checked) {
			char buf[16];
			WritePrivateProfileString(TEXT("USER_SETTINGS"), TEXT("custom"), itoa(0, buf, 10), iniFilePath);
			int scancode = MapVirtualKey(VK_F20 + form->comboBox2->SelectedIndex, MAPVK_VK_TO_VSC);
			WritePrivateProfileString(TEXT("USER_SETTINGS"), TEXT("cbidx"), itoa(form->comboBox2->SelectedIndex, buf, 10), iniFilePath);
			setEmulationKey(scancode, 0);
		}
	};

	System::Void comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (form->radioButton2->Checked) {
			char buf[16];
			int scancode = MapVirtualKey(VK_F20 + form->comboBox2->SelectedIndex, MAPVK_VK_TO_VSC);
			WritePrivateProfileString(TEXT("USER_SETTINGS"), TEXT("cbidx"), itoa(form->comboBox2->SelectedIndex, buf, 10), iniFilePath);
			setEmulationKey(scancode, 0);
		}
	};
};

