
/*  context_gl_osx.h                                                     */

#ifndef CONTEXT_GL_OSX_H
#define CONTEXT_GL_OSX_H

#if defined(OPENGL_ENABLED) || defined(GLES_ENABLED)

#include "core/error_list.h"
#include "core/os/os.h"

#include <AppKit/AppKit.h>
#include <ApplicationServices/ApplicationServices.h>
#include <CoreVideo/CoreVideo.h>

class ContextGL_OSX {
	bool opengl_3_context;
	bool use_vsync;

	void *framework;
	id window_view;
	NSOpenGLPixelFormat *pixelFormat;
	NSOpenGLContext *context;

public:
	void release_current();

	void make_current();
	void update();

	void set_opacity(GLint p_opacity);

	int get_window_width();
	int get_window_height();
	void swap_buffers();

	Error initialize();

	void set_use_vsync(bool p_use);
	bool is_using_vsync() const;

	ContextGL_OSX(id p_view, bool p_opengl_3_context);
	~ContextGL_OSX();
};

#endif
#endif
