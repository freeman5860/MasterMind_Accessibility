package cn.robust.mastermind;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Rect;
import android.os.Bundle;
import android.support.v4.view.accessibility.AccessibilityNodeInfoCompat;
import android.support.v4.widget.ExploreByTouchHelper;
import android.view.View;
import android.view.accessibility.AccessibilityEvent;

public class MainSceneHelper extends ExploreByTouchHelper {
	private static final int NODE_SIZE = 2;
	
	private Context mContext;
	
	private ArrayList<Rect> mNodeRects;

	public MainSceneHelper(View forView) {
		super(forView);
		
		mContext = forView.getContext();
		
		initRects();
	}

	@Override
	protected int getVirtualViewAt(float x, float y) {
		for(int i = 0; i < NODE_SIZE; i++){
			Rect rect = mNodeRects.get(i);
			if(rect.contains((int)x, (int)y)){
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
	protected boolean onPerformActionForVirtualView(int virtualViewId, int action,
			Bundle bundle) {
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
	
	private String getContentDesc(int virtualViewId){
		switch(virtualViewId){
		case 0:
			return mContext.getString(R.string.cd_play_button);
		case 1:
			return mContext.getString(R.string.cd_howtoplay_button);
		}
		
		return "";
	}
	
	private void setParentRectFor(int virtualViewId, AccessibilityNodeInfoCompat node){
		Rect rect = mNodeRects.get(virtualViewId);
		if(rect != null){
			node.setBoundsInParent(rect);
		}
	}
	
	private void initRects(){
		mNodeRects = new ArrayList<Rect>(NODE_SIZE);
		int w = AccessibilityHelper.getWidth();
		int h = AccessibilityHelper.getHeight();
		Rect rect = null;
		for(int i = 0; i < NODE_SIZE; i++){
			switch(i){
			case 0:
				rect = new Rect(w / 2 - 20 , h - 400, w / 2 + 20, h - 300);
				break;
			case 1:
				rect = new Rect(w / 2 - 20 , h - 200, w / 2 + 20, h - 100);
				break;
			}
			mNodeRects.add(rect);
		}
	}

}
