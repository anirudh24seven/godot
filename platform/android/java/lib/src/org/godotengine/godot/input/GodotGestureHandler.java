
/*  GodotGestureHandler.java                                             */



package org.godotengine.godot.input;

import org.godotengine.godot.GodotLib;
import org.godotengine.godot.GodotRenderView;

import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;

/**
 * Handles gesture input related events for the {@link GodotRenderView} view.
 * https://developer.android.com/reference/android/view/GestureDetector.SimpleOnGestureListener
 */
public class GodotGestureHandler extends GestureDetector.SimpleOnGestureListener {
	private final GodotRenderView mRenderView;

	public GodotGestureHandler(GodotRenderView godotView) {
		mRenderView = godotView;
	}

	private void queueEvent(Runnable task) {
		mRenderView.queueOnRenderThread(task);
	}

	@Override
	public boolean onDown(MotionEvent event) {
		super.onDown(event);
		//Log.i("GodotGesture", "onDown");
		return true;
	}

	@Override
	public boolean onSingleTapConfirmed(MotionEvent event) {
		super.onSingleTapConfirmed(event);
		return true;
	}

	@Override
	public void onLongPress(MotionEvent event) {
		//Log.i("GodotGesture", "onLongPress");
	}

	@Override
	public boolean onDoubleTap(MotionEvent event) {
		//Log.i("GodotGesture", "onDoubleTap");
		final int x = Math.round(event.getX());
		final int y = Math.round(event.getY());
		queueEvent(new Runnable() {
			@Override
			public void run() {
				GodotLib.doubletap(x, y);
			}
		});
		return true;
	}

	@Override
	public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
		//Log.i("GodotGesture", "onScroll");
		final int x = Math.round(distanceX);
		final int y = Math.round(distanceY);
		queueEvent(new Runnable() {
			@Override
			public void run() {
				GodotLib.scroll(x, y);
			}
		});
		return true;
	}

	@Override
	public boolean onFling(MotionEvent event1, MotionEvent event2, float velocityX, float velocityY) {
		//Log.i("GodotGesture", "onFling");
		return true;
	}
}
