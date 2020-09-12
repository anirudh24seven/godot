
/*  FullScreenGodotApp.java                                              */

package org.godotengine.godot;

import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;

import androidx.fragment.app.FragmentActivity;

/**
 * Base activity for Android apps intending to use Godot as the primary and only screen.
 *
 * It's also a reference implementation for how to setup and use the {@link Godot} fragment
 * within an Android app.
 */
public abstract class FullScreenGodotApp extends FragmentActivity {
	protected Godot godotFragment;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.godot_app_layout);
		godotFragment = new Godot();
		getSupportFragmentManager().beginTransaction().replace(R.id.godot_fragment_container, godotFragment).setPrimaryNavigationFragment(godotFragment).commitNowAllowingStateLoss();
	}

	@Override
	public void onNewIntent(Intent intent) {
		if (godotFragment != null) {
			godotFragment.onNewIntent(intent);
		}
	}

	@Override
	public void onBackPressed() {
		if (godotFragment != null) {
			godotFragment.onBackPressed();
		} else {
			super.onBackPressed();
		}
	}

	@Override
	public boolean onKeyMultiple(final int inKeyCode, int repeatCount, KeyEvent event) {
		if (godotFragment != null && godotFragment.onKeyMultiple(inKeyCode, repeatCount, event)) {
			return true;
		}
		return super.onKeyMultiple(inKeyCode, repeatCount, event);
	}
}
