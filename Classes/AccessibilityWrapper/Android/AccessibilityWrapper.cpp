#include "AccessibilityWrapper/AccessibilityWrapper.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

using namespace cocos2d;

static AccessibilityWrapper * s_Instance = NULL;

AccessibilityWrapper * AccessibilityWrapper::getInstance(){
	if(s_Instance == NULL){
		s_Instance = new AccessibilityWrapper();
	}

	return s_Instance;
}

void AccessibilityWrapper::addMenuSceneRect(int i, const char * s, float l, float r, float t, float b){
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			"cn/robust/mastermind/AccessibilityHelper","addMenuSceneRect","(ILjava/lang/String;IIII)V");
	if(!isHave){
			//CCLog("jni:openURL 函数不存在");
	}else{
		int left = (int)l;
		int right = (int)r;
		int top = (int)t;
		int bottom = (int) b;
		jstring jstr = minfo.env->NewStringUTF(s);
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID, i, jstr, left, right, top, bottom);
	}
}

void AccessibilityWrapper::addPlaySceneRect(int i, const char * s, float l, float r, float t, float b){
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			"cn/robust/mastermind/AccessibilityHelper","addPlaySceneRect","(ILjava/lang/String;IIII)V");
	if(!isHave){
			//CCLog("jni:openURL 函数不存在");
	}else{
		int left = (int)l;
		int right = (int)r;
		int top = (int)t;
		int bottom = (int) b;
		jstring jstr = minfo.env->NewStringUTF(s);
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID, i, jstr, left, right, top, bottom);
	}
}

void AccessibilityWrapper::onSceneStart(int scene){
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			"cn/robust/mastermind/AccessibilityHelper","onMenuSceneLoad","(I)V");
	if(!isHave){
			//CCLog("jni:openURL 函数不存在");
	}else{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID, scene);
	}
}
