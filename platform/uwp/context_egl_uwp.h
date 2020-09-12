
/*  context_egl_uwp.h                                                    */

#ifndef CONTEXT_EGL_UWP_H
#define CONTEXT_EGL_UWP_H

#include <wrl.h>

#include <EGL/egl.h>

#include "core/error_list.h"
#include "core/os/os.h"

using namespace Windows::UI::Core;

class ContextEGL_UWP {
public:
	enum Driver {
		GLES_2_0,
		VULKAN, // FIXME: Add Vulkan support.
	};

private:
	CoreWindow ^ window;

	EGLDisplay mEglDisplay;
	EGLContext mEglContext;
	EGLSurface mEglSurface;

	EGLint width;
	EGLint height;

	bool vsync;

	Driver driver;

public:
	void release_current();

	void make_current();

	int get_window_width();
	int get_window_height();
	void swap_buffers();

	void set_use_vsync(bool use) { vsync = use; }
	bool is_using_vsync() const { return vsync; }

	Error initialize();
	void reset();

	void cleanup();

	ContextEGL_UWP(CoreWindow ^ p_window, Driver p_driver);
	~ContextEGL_UWP();
};

#endif // CONTEXT_EGL_UWP_H
