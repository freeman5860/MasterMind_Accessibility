package cn.robust.mastermind;

import java.util.ArrayList;
import java.util.List;

import android.graphics.Rect;
import android.os.Bundle;
import android.support.v4.view.accessibility.AccessibilityNodeInfoCompat;
import android.support.v4.widget.ExploreByTouchHelper;
import android.view.View;
import android.view.accessibility.AccessibilityEvent;

public class BaseSceneHelper extends ExploreByTouchHelper {

	protected ArrayList<AccessibilityItem> mNodeItems;

	public BaseSceneHelper(View forView) {
		super(forView);

		mNodeItems = new ArrayList<AccessibilityItem>();
	}

	@Override
	protected int getVirtualViewAt(float x, float y) {
		for (int i = 0; i < mNodeItems.size(); i++) {
			Rect rect = mNodeItems.get(i).mRect;
			if (rect.contains((int) x, (int) y)) {
				return i;
			}
		}
		return -1;
	}

	@Override
	protected void getVisibleVirtualViews(List<Integer> virtualViewIds) {
		for (int i = 0; i < mNodeItems.size(); i++) {
			virtualViewIds.add(mNodeItems.get(i).id);
		}
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
		if(mNodeItems.size() > virtualViewId){
			node.setContentDescription(getContentDesc(virtualViewId));
			setParentRectFor(virtualViewId, node);
		}else{
			node.setContentDescription("");
			node.setBoundsInParent(new Rect(0, 0, 1, 1));
		}
	}

	private String getContentDesc(int virtualViewId) {
		if (mNodeItems.size() > virtualViewId) {
			return mNodeItems.get(virtualViewId).mDesc;
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
	
	public void updateAccessibilityItem(int i, String desc){
		if(mNodeItems.size() > i){
			AccessibilityItem item = mNodeItems.get(i);
			item.mDesc = desc;
		}
	}

	public void addAccessibilityItem(AccessibilityItem item) {
		mNodeItems.add(item);
	}

	public void destroyScene() {
		mNodeItems.clear();
	}
}
