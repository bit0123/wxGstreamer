#pragma once

#include <wx\frame.h>
#include <wx\sizer.h>
#include <wx\panel.h>

#include "GstMPlayer.h"

class MainWindow : public wxFrame
{
public:
	MainWindow();
	~MainWindow();

private:
	wxBoxSizer * sizer;
	wxPanel *vidContainer;
	GstMPlayer *mPlayer;
};

