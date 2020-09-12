
/*  VkSurfaceView.kt                                                     */

@file:JvmName("VkSurfaceView")
package org.godotengine.godot.vulkan

import android.content.Context
import android.view.SurfaceHolder
import android.view.SurfaceView

/**
 * An implementation of SurfaceView that uses the dedicated surface for
 * displaying Vulkan rendering.
 * <p>
 * A [VkSurfaceView] provides the following features:
 * <p>
 * <ul>
 * <li>Manages a surface, which is a special piece of memory that can be
 * composited into the Android view system.
 * <li>Accepts a user-provided [VkRenderer] object that does the actual rendering.
 * <li>Renders on a dedicated [VkThread] thread to decouple rendering performance from the
 * UI thread.
 * </ul>
 */
open internal class VkSurfaceView(context: Context) : SurfaceView(context), SurfaceHolder.Callback {

	companion object {
		fun checkState(expression: Boolean, errorMessage: Any) {
			check(expression) { errorMessage.toString() }
		}
	}

	/**
	 * Thread used to drive the vulkan logic.
	 */
	private val vkThread: VkThread by lazy {
		VkThread(this, renderer)
	}

	/**
	 * Performs the actual rendering.
	 */
	private lateinit var renderer: VkRenderer

	init {
		isClickable = true
		holder.addCallback(this)
	}

	/**
	 * Set the [VkRenderer] associated with the view, and starts the thread that will drive the vulkan
	 * rendering.
	 *
	 * This method should be called once and only once in the life-cycle of [VkSurfaceView].
	 */
	fun startRenderer(renderer: VkRenderer) {
		checkState(!this::renderer.isInitialized, "startRenderer must only be invoked once")
		this.renderer = renderer
		vkThread.start()
	}

	/**
	 * Queues a runnable to be run on the Vulkan rendering thread.
	 *
	 * Must not be called before a [VkRenderer] has been set.
	 */
	fun queueOnVkThread(runnable: Runnable) {
		vkThread.queueEvent(runnable)
	}

	/**
	 * Resumes the rendering thread.
	 *
	 * Must not be called before a [VkRenderer] has been set.
	 */
	open fun onResume() {
		vkThread.onResume()
	}

	/**
	 * Pauses the rendering thread.
	 *
	 * Must not be called before a [VkRenderer] has been set.
	 */
	open fun onPause() {
		vkThread.onPause()
	}

	/**
	 * Tear down the rendering thread.
	 *
	 * Must not be called  before a [VkRenderer] has been set.
	 */
	fun onDestroy() {
		vkThread.blockingExit()
	}

	override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
		vkThread.onSurfaceChanged(width, height)
	}

	override fun surfaceDestroyed(holder: SurfaceHolder) {
		vkThread.onSurfaceDestroyed()
	}

	override fun surfaceCreated(holder: SurfaceHolder) {
		vkThread.onSurfaceCreated()
	}
}
