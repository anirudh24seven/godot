
/*  GodotVulkanRenderView.java                                           */



package org.godotengine.godot;

import org.godotengine.godot.input.GodotGestureHandler;
import org.godotengine.godot.input.GodotInputHandler;
import org.godotengine.godot.vulkan.VkRenderer;
import org.godotengine.godot.vulkan.VkSurfaceView;

import android.annotation.SuppressLint;
import android.content.Context;
import android.view.GestureDetector;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceView;

public class GodotVulkanRenderView extends VkSurfaceView implements GodotRenderView {
	private final Godot godot;
	private final GodotInputHandler mInputHandler;
	private final GestureDetector mGestureDetector;
	private final VkRenderer mRenderer;

	public GodotVulkanRenderView(Context context, Godot godot) {
		super(context);

		this.godot = godot;
		mInputHandler = new GodotInputHandler(this);
		mGestureDetector = new GestureDetector(context, new GodotGestureHandler(this));
		mRenderer = new VkRenderer();

		setFocusableInTouchMode(true);
		startRenderer(mRenderer);
	}

	@Override
	public SurfaceView getView() {
		return this;
	}

	@Override
	public void initInputDevices() {
		mInputHandler.initInputDevices();
	}

	@Override
	public void queueOnRenderThread(Runnable event) {
		queueOnVkThread(event);
	}

	@Override
	public void onActivityPaused() {
		onPause();
	}

	@Override
	public void onActivityResumed() {
		onResume();
	}

	@Override
	public void onBackPressed() {
		godot.onBackPressed();
	}

	@Override
	public GodotInputHandler getInputHandler() {
		return mInputHandler;
	}

	@SuppressLint("ClickableViewAccessibility")
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		super.onTouchEvent(event);
		mGestureDetector.onTouchEvent(event);
		return godot.gotTouchEvent(event);
	}

	@Override
	public boolean onKeyUp(final int keyCode, KeyEvent event) {
		return mInputHandler.onKeyUp(keyCode, event) || super.onKeyUp(keyCode, event);
	}

	@Override
	public boolean onKeyDown(final int keyCode, KeyEvent event) {
		return mInputHandler.onKeyDown(keyCode, event) || super.onKeyDown(keyCode, event);
	}

	@Override
	public boolean onGenericMotionEvent(MotionEvent event) {
		return mInputHandler.onGenericMotionEvent(event) || super.onGenericMotionEvent(event);
	}

	@Override
	public void onResume() {
		super.onResume();

		queueOnVkThread(new Runnable() {
			@Override
			public void run() {
				// Resume the renderer
				mRenderer.onVkResume();
				GodotLib.focusin();
			}
		});
	}

	@Override
	public void onPause() {
		super.onPause();

		queueOnVkThread(new Runnable() {
			@Override
			public void run() {
				GodotLib.focusout();
				// Pause the renderer
				mRenderer.onVkPause();
			}
		});
	}
}
