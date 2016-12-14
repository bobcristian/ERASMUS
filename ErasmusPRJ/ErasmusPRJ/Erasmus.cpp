#include "Erasmus.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ErasmusPRJ::Erasmus form;
	Application::Run(%form);
}
