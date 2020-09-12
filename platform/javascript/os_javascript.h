
/*  os_javascript.h                                                      */

#ifndef OS_JAVASCRIPT_H
#define OS_JAVASCRIPT_H

#include "audio_driver_javascript.h"
#include "core/input/input.h"
#include "drivers/unix/os_unix.h"
#include "servers/audio_server.h"

#include <emscripten/html5.h>

class OS_JavaScript : public OS_Unix {
	MainLoop *main_loop = nullptr;
	AudioDriverJavaScript *audio_driver_javascript = nullptr;

	bool finalizing = false;
	bool idb_available = false;
	int64_t sync_wait_time = -1;
	int64_t last_sync_check_time = -1;

	static void main_loop_callback();

	static void file_access_close_callback(const String &p_file, int p_flags);

protected:
	virtual void initialize();

	virtual void set_main_loop(MainLoop *p_main_loop);
	virtual void delete_main_loop();

	virtual void finalize();

	virtual bool _check_internal_feature_support(const String &p_feature);

public:
	// Override return type to make writing static callbacks less tedious.
	static OS_JavaScript *get_singleton();

	virtual void initialize_joypads();

	virtual bool has_touchscreen_ui_hint() const;

	virtual int get_audio_driver_count() const;
	virtual const char *get_audio_driver_name(int p_driver) const;

	virtual MainLoop *get_main_loop() const;
	void finalize_async();
	bool main_loop_iterate();

	virtual Error execute(const String &p_path, const List<String> &p_arguments, bool p_blocking = true, ProcessID *r_child_id = nullptr, String *r_pipe = nullptr, int *r_exitcode = nullptr, bool read_stderr = false, Mutex *p_pipe_mutex = nullptr);
	virtual Error kill(const ProcessID &p_pid);
	virtual int get_process_id() const;

	String get_executable_path() const;
	virtual Error shell_open(String p_uri);
	virtual String get_name() const;
	// Override default OS implementation which would block the main thread with delay_usec.
	// Implemented in javascript_main.cpp loop callback instead.
	virtual void add_frame_delay(bool p_can_draw) {}
	virtual bool can_draw() const;

	virtual String get_cache_path() const;
	virtual String get_config_path() const;
	virtual String get_data_path() const;
	virtual String get_user_data_dir() const;

	void set_idb_available(bool p_idb_available);
	virtual bool is_userfs_persistent() const;

	void resume_audio();
	bool is_finalizing() { return finalizing; }

	OS_JavaScript();
};

#endif
