#include "Main.h"

IMPLEMENT_APP_CONSOLE(Main)

bool Main::OnInit()
{
	win = new MainWindow();
	win->Show();

	return true;
}
