#include "Controller.h"
#include "MyForm.h"
#include "KeyEmulator.h"

using namespace System::Windows::Forms;

using namespace System::Diagnostics;

Controller::Controller(PttDevice^ pttDevice, HidPttEmulator::MyForm^ form)
{
	TCHAR   inBuf[80];
	this->keyEmulator = gcnew KeyEmulator();
	this->pttDevice = pttDevice;
	this->form = form;

	this->form->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Controller::onFormClosing);
	this->form->setKeyButton->Click += gcnew System::EventHandler(this, &Controller::setKeyButton_Click);
	this->form->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &Controller::comboBox2_SelectedIndexChanged);
	this->form->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Controller::radioButton1_CheckedChanged);
	this->form->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Controller::radioButton2_CheckedChanged);

	// Find path of this exe
	TCHAR *pBuf = new TCHAR[FILENAME_MAX];
	int bytes = GetModuleFileName(NULL, pBuf, FILENAME_MAX);
	std::string s = pBuf;
	s = s.substr(0, s.find_last_of("\\/")) + "\\settings.ini";
	iniFilePath = new char[s.length()];
	iniFilePath = strcpy(iniFilePath, s.c_str());

	GetPrivateProfileString(TEXT("DEVICE"), TEXT("vid"), TEXT("0x0"), inBuf, 80, TEXT(iniFilePath));
	int vid = std::stoul(inBuf, nullptr, 16);

	GetPrivateProfileString(TEXT("DEVICE"), TEXT("pid"), TEXT("0x0"), inBuf, 80, TEXT(iniFilePath));
	int pid = std::stoul(inBuf, nullptr, 16);

	GetPrivateProfileString(TEXT("DEVICE"), TEXT("gpio_pin"), TEXT("4"), inBuf, 80, TEXT(iniFilePath));
	int gpio_pin = std::stoul(inBuf, nullptr, 10);

	GetPrivateProfileString(TEXT("DEVICE"), TEXT("reverse_input"), TEXT("0"), inBuf, 80, TEXT(iniFilePath));
	bool reverseInput = std::stoul(inBuf, nullptr, 10);

	DeviceParameters btnParams;
	btnParams.controller = this;
	btnParams.vid = vid;
	btnParams.pid = pid;
	btnParams.gpio_pin = gpio_pin;
	btnParams.reverseInput = reverseInput;
	btnParams.serial = NULL;

	bool useCustom = GetPrivateProfileInt(TEXT("USER_SETTINGS"), TEXT("custom"), 1, TEXT(iniFilePath));
	int keyFromFile = GetPrivateProfileInt(TEXT("USER_SETTINGS"), TEXT("key"), 0, TEXT(iniFilePath));
	bool extendedFromFile = GetPrivateProfileInt(TEXT("USER_SETTINGS"), TEXT("ex"), 0, TEXT(iniFilePath));

	this->form->comboBox2->SelectedIndex = GetPrivateProfileInt(TEXT("USER_SETTINGS"), TEXT("cbidx"), 0, TEXT(iniFilePath));


	if (useCustom) {
		setEmulationKey(keyFromFile, extendedFromFile);
		this->form->radioButton1->Checked = true;
	}
	else {
		setEmulationKey(keyFromFile, extendedFromFile);
		this->form->radioButton2->Checked = true;
	}

	this->pttDeviceThread = gcnew Thread(gcnew ParameterizedThreadStart(this->pttDevice, &PttDevice::startListening));
	this->pttDeviceThread->Start(%btnParams);

	Application::Run(this->form);
};


void Controller::onFormClosing(System::Object ^sender, System::Windows::Forms::FormClosingEventArgs ^e)
{
	this->pttDevice->stopListening();
};

void Controller::onPttPressed()
{
	this->keyEmulator->emulatePress();
	this->form->onPttPressed();
};

void Controller::onPttReleased()
{
	this->keyEmulator->emulateRelease();
	this->form->onPttReleased();
};

void Controller::onPttDeviceLost() {
	this->form->onPttDeviceLost();
};

void Controller::onPttDeviceConnected() {
	this->form->onPttDeviceConnected();
};

void Controller::setEmulationKey(WORD scancode, bool extended) {
	LONG lparam = 0x00000001 | (LPARAM)(scancode << 16);

	if (extended == true)
		lparam = lparam | 0x01000000;       // Extended code if required

	this->keyEmulator->setKey(scancode, extended);

	if (this->form->radioButton1->Checked) {
		TCHAR *lpszName = new TCHAR[16];
		GetKeyNameText(lparam, lpszName, 16);
		this->form->textBox1->Text = gcnew System::String(lpszName);

		char buf[16];
		WritePrivateProfileString(TEXT("USER_SETTINGS"), TEXT("key"), itoa(scancode, buf, 10), iniFilePath);
		WritePrivateProfileString(TEXT("USER_SETTINGS"), TEXT("ex"), itoa(extended, buf, 10), iniFilePath);
	}
};