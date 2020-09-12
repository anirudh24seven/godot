
/*  context_gl_windows.h                                                 */

#if defined(OPENGL_ENABLED) || defined(GLES_ENABLED)

// Author: Juan Linietsky <reduzio@gmail.com>, (C) 2008

#ifndef CONTEXT_GL_WIN_H
#define CONTEXT_GL_WIN_H

#include "core/error_list.h"
#include "core/os/os.h"

#include <windows.h>

typedef bool(APIENTRY *PFNWGLSWAPINTERVALEXTPROC)(int interval);
typedef int(APIENTRY *PFNWGLGETSWAPINTERVALEXTPROC)(void);

class ContextGL_Windows {
	HDC hDC;
	HGLRC hRC;
	unsigned int pixel_format;
	HWND hWnd;
	bool opengl_3_context;
	bool use_vsync;
	bool vsync_via_compositor;

	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
	PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT;

	static bool should_vsync_via_compositor();

public:
	void release_current();

	void make_current();

	int get_window_width();
	int get_window_height();
	void swap_buffers();

	Error initialize();

	void set_use_vsync(bool p_use);
	bool is_using_vsync() const;

	ContextGL_Windows(HWND hwnd, bool p_opengl_3_context);
	~ContextGL_Windows();
};

#endif
#endif
