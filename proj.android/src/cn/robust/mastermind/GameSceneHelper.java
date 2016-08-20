package cn.robust.mastermind;

import android.view.View;

public class GameSceneHelper extends BaseSceneHelper {

	public GameSceneHelper(View forView) {
		super(forView);
		
		AccessibilityHelper.setGameSceneRef(this);
	}
}
