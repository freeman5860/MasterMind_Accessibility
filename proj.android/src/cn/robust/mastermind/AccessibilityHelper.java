package cn.robust.mastermind;

import java.lang.ref.WeakReference;

import android.annotation.TargetApi;
import android.graphics.Rect;
import android.os.Build;
import android.support.v4.view.ViewCompat;
import android.util.Log;
import android.view.accessibility.AccessibilityEvent;

public class AccessibilityHelper {
	
	private static int sGameWith = 480;
	private static int sGameHeight = 720;
	
	private static int sWidth;
	private static int sHeight;
	
	private static BaseSceneHelper mMenuRef;
	private static BaseSceneHelper mPlayRef;
	private static BaseSceneHelper mOverRef;
	private static BaseSceneHelper mHelpRef;
	private static BaseSceneHelper mCurRef;
	
	private static WeakReference<AccessibilityGameView> mGameViewRef;
	
	public static void setGameView(AccessibilityGameView view){
		mGameViewRef = new WeakReference<AccessibilityGameView>(view);
		
		mMenuRef = new BaseSceneHelper(view);
		mPlayRef = new BaseSceneHelper(view);
		mOverRef = new BaseSceneHelper(view);
		mHelpRef = new BaseSceneHelper(view);
	}
	
	public static void setScreen(int w, int h){
		sWidth = w;
		sHeight = h;
		
		Log.e("hjy", "setScreen w:" + w + " h:" + h);
	}
	
	public static int getWidth(){
		return sWidth;
	}
	
	public static int getHeight(){
		return sHeight;
	}
	
	private static int getScreenX(int x){
		int ret = x * sWidth / sGameWith;
		return ret;
	}
	
	private static int getScreenY(int y){
		// 针对不同的拉伸方式要有不同的转换，这里是kResolutionShowAll
		int realHeight = sGameHeight * sWidth / sGameWith;
		int blackHeight = (sHeight - realHeight) / 2;
		int y1 = sGameHeight - y;
		int ret = y1 * realHeight / sGameHeight + blackHeight;
		return ret;
	}
	
	public static Rect getScreenRect(Rect r){
		int left = getScreenX(r.left);
		int right = getScreenX(r.right);
		int top = getScreenY(r.top);
		int bottom = getScreenY(r.bottom);
		
		return new Rect(left, top, right, bottom);
	}
	
	public static void onMenuSceneLoad(int scene){
		Log.e("hjy", "onMenuSceneLoad " + scene);
		
		if(mGameViewRef.get() != null && mMenuRef != null && 
				mPlayRef != null && mOverRef != null){
			switch (scene) {
			case 0:
				ViewCompat.setAccessibilityDelegate(mGameViewRef.get(), mMenuRef);
				handleNewScene(mMenuRef);
				break;
			case 1:
				ViewCompat.setAccessibilityDelegate(mGameViewRef.get(), mPlayRef);
				handleNewScene(mPlayRef);
				break;
			case 2:
				ViewCompat.setAccessibilityDelegate(mGameViewRef.get(), mOverRef);
				handleNewScene(mOverRef);
				break;
			case 3:
				ViewCompat.setAccessibilityDelegate(mGameViewRef.get(), mHelpRef);
				handleNewScene(mHelpRef);
			}
		}
	}
	
	private static void handleNewScene(BaseSceneHelper newScene){
		if(mCurRef != null ){
			mCurRef.destroyScene();
		}
		mCurRef = newScene;
		mGameViewRef.get().setCurSceneHelper(newScene);
		
		if(android.os.Build.VERSION.SDK_INT >= 16){
			mGameViewRef.get().postDelayed(new Runnable() {
				
				@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
				@Override
				public void run() {
					mGameViewRef.get().sendAccessibilityEvent(AccessibilityEvent.TYPE_VIEW_ACCESSIBILITY_FOCUS_CLEARED);
				}
			}, 100);
		}
	}
	
	public static void addMenuSceneRect(int i, String d, int l, int r, int t, int b){
		int sl = getScreenX(l);
		int sr = getScreenX(r);
		int st = getScreenY(b);
		int sb = getScreenY(t);
		AccessibilityItem item = new AccessibilityItem(i, d, sl, sr, st, sb);
		Log.e("hjy", "addMenuSceneRect " + item.toString());
		if(mMenuRef != null){
			mMenuRef.addAccessibilityItem(item);
		}
	}
	
	public static void addPlaySceneRect(int i, String d, int l, int r, int t, int b){
		Log.e("hjy", "addPlaySceneRect rect:" + l + "," + r + "," + t + "," + b);
		int sl = getScreenX(l);
		int sr = getScreenX(r);
		int st = getScreenY(b);
		int sb = getScreenY(t);
		AccessibilityItem item = new AccessibilityItem(i, d, sl, sr, st, sb);
		//Log.e("hjy", "addPlaySceneRect " + item.toString());
		if(mPlayRef != null){
			mPlayRef.addAccessibilityItem(item);
		}
	}
	
	public static void addSceneRect(int i, String d, int l, int r, int t, int b){
		int sl = getScreenX(l);
		int sr = getScreenX(r);
		int st = getScreenY(b);
		int sb = getScreenY(t);
		AccessibilityItem item = new AccessibilityItem(i, d, sl, sr, st, sb);
		Log.e("hjy", "addSceneRect " + item.toString());
		if(mCurRef != null){
			mCurRef.addAccessibilityItem(item);
		}
	}
	
	@TargetApi(Build.VERSION_CODES.JELLY_BEAN) 
	public static void annouceStepResult(String result){
		if(mGameViewRef.get() != null){
			if(android.os.Build.VERSION.SDK_INT >= 16){
			    AccessibilityEvent event = AccessibilityEvent.obtain(AccessibilityEvent.TYPE_ANNOUNCEMENT);
			    event.setPackageName(mGameViewRef.get().getContext().getPackageName());
			    event.setClassName(mGameViewRef.get().getClass().getName());
			    event.setSource(mGameViewRef.get());
			    event.getText().add(result);
			    mGameViewRef.get().getParent().requestSendAccessibilityEvent(mGameViewRef.get(), event);
			}
		}
	}
	
	public static void updateAccessibilityItem(int i, String desc){
		if(mCurRef != null){
			mCurRef.updateAccessibilityItem(i, desc);
	}
	}
}
