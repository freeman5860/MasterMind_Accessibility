package cn.robust.mastermind;

import android.graphics.Rect;

public class AccessibilityItem {

	public Rect mRect;
	public String mDesc;
	public int id;
	
	public AccessibilityItem(int id){
		this.id = id;
		this.mRect = new Rect(0, 0, 1, 1);
	}
	
	public AccessibilityItem(int id, String desc, int l, int r, int t, int b){
		this.id = id;
		this.mDesc = desc;
		this.mRect = new Rect(l, t, r, b);
	}
	
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("id:").append(id);
		sb.append(" mDesc:").append(mDesc);
		sb.append(" mRect:").append(mRect.toString());
		return sb.toString();
	}
}
