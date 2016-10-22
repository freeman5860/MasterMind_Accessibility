#include "AccessibilityWrapper/AccessibilityWrapper.h"
#import "AccessibilityHelper.h"

static AccessibilityWrapper * s_Instance = NULL;

AccessibilityWrapper * AccessibilityWrapper::getInstance(){
	if(s_Instance == NULL){
		s_Instance = new AccessibilityWrapper();
	}

	return s_Instance;
}

void AccessibilityWrapper::onSceneStart(int scene){
    [[AccessibilityHelper getInstance]onMenuSceneLoad:scene];
}

void AccessibilityWrapper::addMenuSceneRect(int i, const char *s, float l, float r, float t, float b){
    NSString * desc = [[NSString alloc]initWithUTF8String:s];
    [[AccessibilityHelper getInstance]addMenuSceneRect:desc left:l right:r top:t bottom:b];
}

void AccessibilityWrapper::addPlaySceneRect(int i, const char *s, float l, float r, float t, float b){
    NSString * desc = [[NSString alloc]initWithUTF8String:s];
    [[AccessibilityHelper getInstance]addPlaySceneRect:desc left:l right:r top:t bottom:b];
}

void AccessibilityWrapper::addSceneRect(int i, const char *s, float l, float r, float t, float b){
    NSString * desc = [[NSString alloc]initWithUTF8String:s];
    [[AccessibilityHelper getInstance]addSceneRect:desc left:l right:r top:t bottom:b];
}

void AccessibilityWrapper::annouceResult(const char *s){
    NSString * desc = [[NSString alloc]initWithUTF8String:s];
    [[AccessibilityHelper getInstance]annouceStepResult:desc];
}

void AccessibilityWrapper::updateNodeDesc(int i, const char *s){
    NSLog(@"updateNodeDesc");
}
