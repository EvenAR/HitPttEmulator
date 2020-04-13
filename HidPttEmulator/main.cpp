#include <vcclr.h>
#include <sstream>
#include "MyForm.h"
#include "PttDevice.h"
#include "Controller.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;
using namespace System::Diagnostics;

[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	HidPttEmulator::MyForm^ form = gcnew HidPttEmulator::MyForm();
	gcroot<PttDevice^> pttDevice = gcnew PttDevice();
	gcroot<Controller^> uiController = gcnew Controller(pttDevice, form);
}
