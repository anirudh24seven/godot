
/*  os_server.h                                                          */



#ifndef OS_SERVER_H
#define OS_SERVER_H

#include "core/input/input.h"
#include "drivers/dummy/texture_loader_dummy.h"
#include "drivers/unix/os_unix.h"
#ifdef __APPLE__
#include "platform/osx/crash_handler_osx.h"
#include "platform/osx/semaphore_osx.h"
#else
#include "platform/x11/crash_handler_linuxbsd.h"
#endif
#include "servers/audio_server.h"
#include "servers/rendering/rasterizer.h"
#include "servers/rendering_server.h"

#undef CursorShape

class OS_Server : public OS_Unix {
	RenderingServer *rendering_server;
	VideoMode current_videomode;
	List<String> args;
	MainLoop *main_loop;

	bool grab;

	virtual void delete_main_loop();

	bool force_quit;

	InputDefault *input;

	CrashHandler crash_handler;

	int video_driver_index;

	Ref<ResourceFormatDummyTexture> resource_loader_dummy;

protected:
	virtual int get_video_driver_count() const;
	virtual const char *get_video_driver_name(int p_driver) const;
	virtual int get_current_video_driver() const;
	virtual int get_audio_driver_count() const;
	virtual const char *get_audio_driver_name(int p_driver) const;

	virtual void initialize_core();
	virtual Error initialize(const VideoMode &p_desired, int p_video_driver, int p_audio_driver);
	virtual void finalize();

	virtual void set_main_loop(MainLoop *p_main_loop);

public:
	virtual String get_name() const;

	virtual void set_mouse_show(bool p_show);
	virtual void set_mouse_grab(bool p_grab);
	virtual bool is_mouse_grab_enabled() const;
	virtual Point2 get_mouse_position() const;
	virtual int get_mouse_button_state() const;
	virtual void set_window_title(const String &p_title);

	virtual MainLoop *get_main_loop() const;

	virtual bool can_draw() const;

	virtual void set_video_mode(const VideoMode &p_video_mode, int p_screen = 0);
	virtual VideoMode get_video_mode(int p_screen = 0) const;
	virtual void get_fullscreen_mode_list(List<VideoMode> *p_list, int p_screen = 0) const;

	virtual Size2 get_window_size() const;

	virtual void move_window_to_foreground();

	void run();

	virtual bool _check_internal_feature_support(const String &p_feature);

	virtual String get_config_path() const;
	virtual String get_data_path() const;
	virtual String get_cache_path() const;

	virtual String get_system_dir(SystemDir p_dir) const;

	void disable_crash_handler();
	bool is_disable_crash_handler() const;

	OS_Server();
};

#endif
