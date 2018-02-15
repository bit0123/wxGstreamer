#pragma once

#include <Windows.h>
#include <gst\gst.h>
#include <gst\video\video.h>
#include <string>

class GstMPlayer {

public:
	GstMPlayer(HWND wnd);
	~GstMPlayer();

	bool LoadLocalFile(std::string path);
	bool Play();
	bool Pause();
	bool Stop();

private:
	bool CreatePipeline();
	bool ChangePlaybinState(GstState state);
	static GstBusSyncReply bus_sync_handler(GstBus *bus, GstMessage *message, GstMPlayer *player);

	HWND vidOutputContainer;
	GstElement *pipeline;
	GstElement *playbin;
};
