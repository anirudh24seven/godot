
/*  Joystick.java                                                        */



package org.godotengine.godot.input;

import android.view.InputDevice.MotionRange;

import java.util.ArrayList;

/**
 * POJO class to represent a Joystick input device.
 */
class Joystick {
	int device_id;
	String name;
	ArrayList<MotionRange> axes;
	ArrayList<MotionRange> hats;
}
