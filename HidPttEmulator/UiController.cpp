#include "UiController.h"

using namespace System::Windows::Forms;

using namespace System::Diagnostics;

UiController::UiController(PttDevice^ button, HidPttEmulator::MyForm^ form)
{
	TCHAR   inBuf[80];
	this->button = button;
	this->form = form;

	this->form->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &UiController::onFormClosing);
	this->form->setKeyButton->Click += gcnew System::EventHandler(this, &UiController::setKeyButton_Click);
	this->form->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &UiController::comboBox2_SelectedIndexChanged);
	this->form->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &UiController::radioButton1_CheckedChanged);
	this->form->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &UiController::radioButton2_CheckedChanged);

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

	GetPrivateProfileString(TEXT("DEVICE"), TEXT("gpio_id"), TEXT("0x0"), inBuf, 80, TEXT(iniFilePath));
	int gpio_id = std::stoul(inBuf, nullptr, 16);

	ButtonParameters bp;
	bp.controller = this;
	bp.vid = vid;
	bp.pid = pid;
	bp.gpio_id = gpio_id;
	bp.serial = NULL;

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

	this->t1 = gcnew Thread(gcnew ParameterizedThreadStart(this->button, &PttDevice::startListening));
	this->t1->Start(%bp);

	Application::Run(this->form);
};


void UiController::onFormClosing(System::Object ^sender, System::Windows::Forms::FormClosingEventArgs ^e)
{
	this->button->stopListening();
};

void UiController::onPttPressed()
{
	this->form->onPttPressed();
};

void UiController::onPttReleased()
{
	this->form->onPttReleased();
};

void UiController::onPttDeviceLost() {
	this->form->onPttDeviceLost();
};

void UiController::onPttDeviceConnected() {
	this->form->onPttDeviceConnected();
};

void UiController::setEmulationKey(WORD scancode, bool extended) {
	LONG lparam = 0x00000001 | (LPARAM)(scancode << 16);

	if (extended == true)
		lparam = lparam | 0x01000000;       // Extended code if required

	this->button->scancode = scancode;
	this->button->scancodeExtended = extended;

	if (this->form->radioButton1->Checked) {
		TCHAR *lpszName = new TCHAR[16];
		GetKeyNameText(lparam, lpszName, 16);
		this->form->textBox1->Text = gcnew System::String(lpszName);

		char buf[16];
		WritePrivateProfileString(TEXT("USER_SETTINGS"), TEXT("key"), itoa(scancode, buf, 10), iniFilePath);
		WritePrivateProfileString(TEXT("USER_SETTINGS"), TEXT("ex"), itoa(extended, buf, 10), iniFilePath);
	}
};