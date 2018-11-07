#include <vcclr.h>
#include <sstream>
#include "MyForm.h"
#include "PttDevice.h"
#include "UiController.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;
using namespace System::Diagnostics;

[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	HidPttEmulator::MyForm^ form = gcnew HidPttEmulator::MyForm();
	gcroot<PttDevice^> button = gcnew PttDevice();
	gcroot<UiController^> uiController = gcnew UiController(button, form);
}
