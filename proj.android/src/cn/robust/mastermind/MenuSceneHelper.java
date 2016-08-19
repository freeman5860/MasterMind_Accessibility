package cn.robust.mastermind;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Rect;
import android.os.Bundle;
import android.support.v4.view.accessibility.AccessibilityNodeInfoCompat;
import android.support.v4.widget.ExploreByTouchHelper;
import android.util.Log;
import android.view.View;
import android.view.accessibility.AccessibilityEvent;

public class MenuSceneHelper extends ExploreByTouchHelper {
	private static final int NODE_SIZE = 2;

	private Context mContext;

	private ArrayList<AccessibilityItem> mNodeItems;

	public MenuSceneHelper(View forView) {
		super(forView);

		mContext = forView.getContext();

		mNodeItems = new ArrayList<AccessibilityItem>(NODE_SIZE);
		for(int i = 0; i < NODE_SIZE; i++){
			mNodeItems.add(new AccessibilityItem(i));
		}
		
		AccessibilityHelper.setMenuSceneRef(this);
	}

	@Override
	protected int getVirtualViewAt(float x, float y) {
		for (int i = 0; i < NODE_SIZE; i++) {
			Rect rect = mNodeItems.get(i).mRect;
			if (rect.contains((int) x, (int) y)) {
				Log.e("hjy", "getvirtualviewat " + i);
				return i;
			}
		}
		return -1;
	}

	@Override
	protected void getVisibleVirtualViews(List<Integer> virtualViewIds) {
		virtualViewIds.add(0);
		virtualViewIds.add(1);
	}

	@Override
	protected boolean onPerformActionForVirtualView(int virtualViewId,
			int action, Bundle bundle) {
		return false;
	}

	@Override
	protected void onPopulateEventForVirtualView(int virtualViewId,
			AccessibilityEvent event) {
		event.setContentDescription(getContentDesc(virtualViewId));
	}

	@Override
	protected void onPopulateNodeForVirtualView(int virtualViewId,
			AccessibilityNodeInfoCompat node) {
		node.setContentDescription(getContentDesc(virtualViewId));

		setParentRectFor(virtualViewId, node);
	}

	private String getContentDesc(int virtualViewId) {
		switch (virtualViewId) {
		case 0:
			return mContext.getString(R.string.cd_play_button);
		case 1:
			return mContext.getString(R.string.cd_howtoplay_button);
		}

		return "";
	}

	private void setParentRectFor(int virtualViewId,
			AccessibilityNodeInfoCompat node) {
		if (mNodeItems.size() > virtualViewId) {
			Rect rect = mNodeItems.get(virtualViewId).mRect;
			if (rect != null) {
				node.setBoundsInParent(rect);
			}
		}
	}
	
	public void setAccessibilityItem(int i, AccessibilityItem item){
		mNodeItems.set(i, item);
	}
}
