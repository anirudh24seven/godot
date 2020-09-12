
/*  GodotRenderer.java                                                   */

package org.godotengine.godot;

import org.godotengine.godot.plugin.GodotPlugin;
import org.godotengine.godot.plugin.GodotPluginRegistry;
import org.godotengine.godot.utils.GLUtils;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Godot's renderer implementation.
 */
class GodotRenderer implements GLSurfaceView.Renderer {
	private final GodotPluginRegistry pluginRegistry;
	private boolean activityJustResumed = false;

	GodotRenderer() {
		this.pluginRegistry = GodotPluginRegistry.getPluginRegistry();
	}

	public void onDrawFrame(GL10 gl) {
		if (activityJustResumed) {
			GodotLib.onRendererResumed();
			activityJustResumed = false;
		}

		GodotLib.step();
		for (GodotPlugin plugin : pluginRegistry.getAllPlugins()) {
			plugin.onGLDrawFrame(gl);
		}
	}

	public void onSurfaceChanged(GL10 gl, int width, int height) {
		GodotLib.resize(null, width, height);
		for (GodotPlugin plugin : pluginRegistry.getAllPlugins()) {
			plugin.onGLSurfaceChanged(gl, width, height);
		}
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		GodotLib.newcontext(null, GLUtils.use_32);
		for (GodotPlugin plugin : pluginRegistry.getAllPlugins()) {
			plugin.onGLSurfaceCreated(gl, config);
		}
	}

	void onActivityResumed() {
		// We defer invoking GodotLib.onRendererResumed() until the first draw frame call.
		// This ensures we have a valid GL context and surface when we do so.
		activityJustResumed = true;
	}

	void onActivityPaused() {
		GodotLib.onRendererPaused();
	}
}
