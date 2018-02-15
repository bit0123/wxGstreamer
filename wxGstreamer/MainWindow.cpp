#include "MainWindow.h"

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "wxGstreamer")
{
	vidContainer = new wxPanel(this, wxID_ANY);
	sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(vidContainer, 1, wxEXPAND);
	SetSizer(sizer);
	
	mPlayer = new GstMPlayer(vidContainer->GetHandle());
	mPlayer->LoadLocalFile("C:/gstreamer/1.0/x86_64/bin/3D_fishes.mp4");
	mPlayer->Play();

}

MainWindow::~MainWindow()
{

}
