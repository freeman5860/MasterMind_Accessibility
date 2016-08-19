package cn.robust.mastermind;

import android.graphics.Rect;
import android.util.Log;

public class AccessibilityHelper {
	
	private static int sGameWith = 480;
	private static int sGameHeight = 720;
	
	private static int sWidth;
	private static int sHeight;
	
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
		int ret = y * sHeight / sGameHeight;
		return ret;
	}
	
	public static Rect getScreenRect(Rect r){
		int left = getScreenX(r.left);
		int right = getScreenX(r.right);
		int top = getScreenY(r.top);
		int bottom = getScreenY(r.bottom);
		
		return new Rect(left, top, right, bottom);
	}
}
