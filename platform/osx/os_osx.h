
/*  os_osx.h                                                             */

#ifndef OS_OSX_H
#define OS_OSX_H

#include "core/input/input.h"
#include "crash_handler_osx.h"
#include "drivers/coreaudio/audio_driver_coreaudio.h"
#include "drivers/coremidi/midi_driver_coremidi.h"
#include "drivers/unix/os_unix.h"
#include "joypad_osx.h"
#include "servers/audio_server.h"

class OS_OSX : public OS_Unix {
	virtual void delete_main_loop();

	bool force_quit;

	JoypadOSX *joypad_osx = nullptr;

#ifdef COREAUDIO_ENABLED
	AudioDriverCoreAudio audio_driver;
#endif
#ifdef COREMIDI_ENABLED
	MIDIDriverCoreMidi midi_driver;
#endif

	CrashHandler crash_handler;

	MainLoop *main_loop;

public:
	String open_with_filename;

protected:
	virtual void initialize_core();
	virtual void initialize();
	virtual void finalize();

	virtual void initialize_joypads();

	virtual void set_main_loop(MainLoop *p_main_loop);

public:
	virtual String get_name() const;

	virtual Error open_dynamic_library(const String p_path, void *&p_library_handle, bool p_also_set_library_path = false);

	virtual MainLoop *get_main_loop() const;

	virtual String get_config_path() const;
	virtual String get_data_path() const;
	virtual String get_cache_path() const;
	virtual String get_bundle_resource_dir() const;
	virtual String get_godot_dir_name() const;

	virtual String get_system_dir(SystemDir p_dir) const;

	Error shell_open(String p_uri);

	String get_locale() const;

	virtual String get_executable_path() const;

	virtual String get_unique_id() const; //++

	virtual bool _check_internal_feature_support(const String &p_feature);

	void run();

	void disable_crash_handler();
	bool is_disable_crash_handler() const;

	virtual Error move_to_trash(const String &p_path);

	OS_OSX();
};

#endif
