
/*  GodotRenderView.java                                                 */

package org.godotengine.godot;

import org.godotengine.godot.input.GodotInputHandler;

import android.view.SurfaceView;

public interface GodotRenderView {
	abstract public SurfaceView getView();

	abstract public void initInputDevices();

	abstract public void queueOnRenderThread(Runnable event);

	abstract public void onActivityPaused();
	abstract public void onActivityResumed();

	abstract public void onBackPressed();

	abstract public GodotInputHandler getInputHandler();
}
