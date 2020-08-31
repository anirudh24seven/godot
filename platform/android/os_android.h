
/*  os_android.h                                                         */



#ifndef OS_ANDROID_H
#define OS_ANDROID_H

#include "audio_driver_jandroid.h"
#include "audio_driver_opensl.h"
#include "core/os/main_loop.h"
#include "drivers/unix/os_unix.h"
#include "servers/audio_server.h"

class GodotJavaWrapper;
class GodotIOJavaWrapper;

struct ANativeWindow;

class OS_Android : public OS_Unix {
private:
	Size2i display_size;

	bool use_apk_expansion;

#if defined(OPENGL_ENABLED)
	bool use_16bits_fbo;
	const char *gl_extensions;
#endif

#if defined(VULKAN_ENABLED)
	ANativeWindow *native_window;
#endif

	mutable String data_dir_cache;

	//AudioDriverAndroid audio_driver_android;
	AudioDriverOpenSL audio_driver_android;

	MainLoop *main_loop;

	GodotJavaWrapper *godot_java;
	GodotIOJavaWrapper *godot_io_java;

public:
	virtual void initialize_core();
	virtual void initialize();

	virtual void initialize_joypads();

	virtual void set_main_loop(MainLoop *p_main_loop);
	virtual void delete_main_loop();

	virtual void finalize();

	typedef int64_t ProcessID;

	static OS_Android *get_singleton();
	GodotJavaWrapper *get_godot_java();
	GodotIOJavaWrapper *get_godot_io_java();

	virtual bool request_permission(const String &p_name);
	virtual bool request_permissions();
	virtual Vector<String> get_granted_permissions() const;

	virtual Error open_dynamic_library(const String p_path, void *&p_library_handle, bool p_also_set_library_path = false);

	virtual String get_name() const;
	virtual MainLoop *get_main_loop() const;

	void main_loop_begin();
	bool main_loop_iterate();
	void main_loop_request_go_back();
	void main_loop_end();
	void main_loop_focusout();
	void main_loop_focusin();

	void set_display_size(const Size2i &p_size);
	Size2i get_display_size() const;

	void set_context_is_16_bits(bool p_is_16);
	void set_opengl_extensions(const char *p_gl_extensions);

	void set_native_window(ANativeWindow *p_native_window);
	ANativeWindow *get_native_window() const;

	virtual Error shell_open(String p_uri);
	virtual String get_user_data_dir() const;
	virtual String get_resource_dir() const;
	virtual String get_locale() const;
	virtual String get_model_name() const;

	virtual String get_unique_id() const;

	virtual String get_system_dir(SystemDir p_dir) const;

	void vibrate_handheld(int p_duration_ms);

	virtual bool _check_internal_feature_support(const String &p_feature);
	OS_Android(GodotJavaWrapper *p_godot_java, GodotIOJavaWrapper *p_godot_io_java, bool p_use_apk_expansion);
	~OS_Android();
};

#endif
