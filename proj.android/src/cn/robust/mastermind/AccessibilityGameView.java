package cn.robust.mastermind;

import android.annotation.SuppressLint;
import android.content.Context;
import android.view.MotionEvent;
import android.view.View;

public class AccessibilityGameView extends View {
	
	private BaseSceneHelper mTouchHelper;

	public AccessibilityGameView(Context context) {
		super(context);
		
		setContentDescription(getResources().getString(R.string.app_name));
	}
	
	public void setCurSceneHelper(BaseSceneHelper helper){
		mTouchHelper = helper;
	}
	
	@SuppressLint("NewApi")
	@Override
	protected boolean dispatchHoverEvent(MotionEvent event) {
		if(mTouchHelper != null && mTouchHelper.dispatchHoverEvent(event)){
			return true;
		}
		
		return super.dispatchHoverEvent(event);
	}

}
