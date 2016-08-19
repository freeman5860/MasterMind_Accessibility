package cn.robust.mastermind;

import java.lang.ref.WeakReference;

import android.graphics.Rect;
import android.support.v4.view.AccessibilityDelegateCompat;
import android.support.v4.view.ViewCompat;
import android.util.Log;

public class AccessibilityHelper {
	
	private static int sGameWith = 480;
	private static int sGameHeight = 720;
	
	private static int sWidth;
	private static int sHeight;
	
	private static WeakReference<MenuSceneHelper> mMenuRef;
	private static WeakReference<GameSceneHelper> mPlayRef;
	
	private static WeakReference<AccessibilityGameView> mGameViewRef;
	
	public static void setGameView(AccessibilityGameView view){
		mGameViewRef = new WeakReference<AccessibilityGameView>(view);
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
	
	public static void setMenuSceneRef(MenuSceneHelper helper){
		mMenuRef = new WeakReference<MenuSceneHelper>(helper);
	}
	
	public static void setGameSceneRef(GameSceneHelper helper){
		mPlayRef = new WeakReference<GameSceneHelper>(helper);
	}
	
	private static int getScreenX(int x){
		int ret = x * sWidth / sGameWith;
		return ret;
	}
	
	private static int getScreenY(int y){
//		int ret = y * sHeight / sGameHeight;
//		ret = sHeight - ret; // ×ø±ê×ª»»
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
		if(mGameViewRef.get() != null && mMenuRef.get() != null && mPlayRef.get() != null){
			switch (scene) {
			case 0:
				ViewCompat.setAccessibilityDelegate(mGameViewRef.get(), mMenuRef.get());
				//mMenuRef.get().onMenSceneLoad();
				break;
			case 1:
				ViewCompat.setAccessibilityDelegate(mGameViewRef.get(), mPlayRef.get());
				//mGameViewRef.get().invalidate();
				//mPlayRef.get().onMenSceneLoad();
				break;
			}
		}
	}
	
	public static void addMenuSceneRect(int i, String d, int l, int r, int t, int b){
		int sl = getScreenX(l);
		int sr = getScreenX(r);
		int st = getScreenY(b);
		int sb = getScreenY(t);
		AccessibilityItem item = new AccessibilityItem(i, d, sl, sr, st, sb);
		Log.e("hjy", "addMenuSceneRect " + item.toString());
		if(mMenuRef.get() != null){
			mMenuRef.get().setAccessibilityItem(i, item);
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
		if(mPlayRef.get() != null){
			mPlayRef.get().setAccessibilityItem(i, item);
		}
	}
}
