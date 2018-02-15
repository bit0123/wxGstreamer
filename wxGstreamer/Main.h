#pragma once

#include <wx\wx.h>
#include "MainWindow.h"

class Main : public wxApp
{
	virtual bool OnInit();

private:
	MainWindow *win;
};
