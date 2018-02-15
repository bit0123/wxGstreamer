#include "GstMPlayer.h"
#include <Windows.h>

GstMPlayer::GstMPlayer(HWND wnd) : vidOutputContainer(wnd), pipeline(NULL), playbin(NULL)
{
	gst_init(0, NULL);

	CreatePipeline();
}

bool GstMPlayer::CreatePipeline()
{
	pipeline = gst_pipeline_new(NULL);
	playbin = gst_element_factory_make("playbin", NULL);
	gst_bin_add(GST_BIN(pipeline), playbin);

	// 1st way to directly set the render surface (window)
	if(vidOutputContainer != nullptr)
		gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(playbin), (guintptr)vidOutputContainer);

	// 2nd way to set handler video overlay
	/*GstBus *bus = gst_element_get_bus(pipeline);
	gst_bus_enable_sync_message_emission(bus);
	gst_bus_set_sync_handler(bus, (GstBusSyncHandler) bus_sync_handler, this, NULL);*/
	
	return true;
}

GstBusSyncReply GstMPlayer::bus_sync_handler(GstBus *bus, GstMessage *message, GstMPlayer *player)
{
	// ignore anything but 'prepare-window-handle' element messages
	if (!gst_is_video_overlay_prepare_window_handle_message(message))
		return GST_BUS_PASS;

	if (player->vidOutputContainer != NULL)
	{
		GstVideoOverlay *overlay;
		overlay = GST_VIDEO_OVERLAY(GST_MESSAGE_SRC(message));
		gst_video_overlay_set_window_handle(overlay, (guintptr)player->vidOutputContainer);
	}
	
	gst_message_unref(message);

	return GST_BUS_DROP;
}

bool GstMPlayer::LoadLocalFile(std::string path)
{
	GError *err;
	gchar *uri = gst_filename_to_uri(path.c_str(), &err);
	if (err != NULL)
	{
		return false;
	}
	g_object_set(G_OBJECT(playbin), "uri", uri, NULL);

	if (vidOutputContainer != nullptr)
		gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(playbin), (guintptr)vidOutputContainer);

	return true;
}

bool GstMPlayer::Play()
{
	return ChangePlaybinState(GST_STATE_PLAYING);
}

bool GstMPlayer::Pause()
{
	return ChangePlaybinState(GST_STATE_PAUSED);
}

bool GstMPlayer::Stop()
{
	return ChangePlaybinState(GST_STATE_READY);
}

bool GstMPlayer::ChangePlaybinState(GstState state)
{
	GstStateChangeReturn m_Ret = gst_element_set_state(pipeline, state);

	switch (m_Ret) {
	case GST_STATE_CHANGE_FAILURE:
		g_print("State Change Failure\n");
		return false;
		break;
	}
	return true;
}

GstMPlayer::~GstMPlayer()
{
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(GST_OBJECT(pipeline));
}
