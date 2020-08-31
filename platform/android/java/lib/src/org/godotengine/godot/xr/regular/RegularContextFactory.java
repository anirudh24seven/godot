
/*  RegularContextFactory.java                                           */



package org.godotengine.godot.xr.regular;

import org.godotengine.godot.GodotLib;
import org.godotengine.godot.utils.GLUtils;

import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

/**
 * Factory used to setup the opengl context for pancake games.
 */
public class RegularContextFactory implements GLSurfaceView.EGLContextFactory {
	private static final String TAG = RegularContextFactory.class.getSimpleName();

	private static final int _EGL_CONTEXT_FLAGS_KHR = 0x30FC;
	private static final int _EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR = 0x00000001;

	private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

	public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
		// FIXME: Add support for Vulkan.
		Log.w(TAG, "creating OpenGL ES 2.0 context :");

		GLUtils.checkEglError(TAG, "Before eglCreateContext", egl);
		EGLContext context;
		if (GLUtils.use_debug_opengl) {
			int[] attrib_list2 = { EGL_CONTEXT_CLIENT_VERSION, 2, _EGL_CONTEXT_FLAGS_KHR, _EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR, EGL10.EGL_NONE };
			context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list2);
		} else {
			int[] attrib_list2 = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
			context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list2);
		}
		GLUtils.checkEglError(TAG, "After eglCreateContext", egl);
		return context;
	}

	public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
		egl.eglDestroyContext(display, context);
	}
}
