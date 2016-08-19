#include "AccesibilityWrapper/AccesibilityWrapper.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

using namespace cocos2d;

static AccesibilityWrapper * s_Instance = NULL;

AccesibilityWrapper * AccesibilityWrapper::getInstance(){
	if(s_Instance == NULL){
		s_Instance = new AccesibilityWrapper();
	}

	return s_Instance;
}

void AccesibilityWrapper::initMenuSceneRect(){
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			"com/freeman/cocos2dx/AdmobPlugin","showBanner","()V");
	if(!isHave){
			//CCLog("jni:openURL 函数不存在");
	}else{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID);
	}
}
