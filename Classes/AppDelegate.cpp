#include "AppDelegate.h"

#include <vector>
#include <string>

#include "HelloWorldScene.h"
#include "AppMacros.h"

//#include "ChartboostX.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	CCConfiguration::sharedConfiguration()->loadConfigFile("values/strings.plist");
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	CCSize frameSize = pEGLView->getFrameSize();
    CCLOG("framesize : %f, %f", frameSize.width, frameSize.height); 

    pDirector->setOpenGLView(pEGLView);

    CCSize designSize = CCSize(480, 720);
    // Set the design resolution
    pEGLView->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);

//	CCSize frameSize = pEGLView->getFrameSize();
//
//    vector<string> searchPath;
//
//    // In this demo, we select resource according to the frame's height.
//    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
//    // We use the ratio of resource's height to the height of design resolution,
//    // this can make sure that the resource's height could fit for the height of design resolution.
//
//    // if the frame's height is larger than the height of medium resource size, select large resource.
//	if (frameSize.width > mediumResource.size.height)
//	{
//        searchPath.push_back(largeResource.directory);
//
//        pDirector->setContentScaleFactor(MIN(frameSize.width/designSize.width, frameSize.height/designSize.height));
//	}
//    // if the frame's height is larger than the height of small resource size, select medium resource.
//    else if (frameSize.width > smallResource.size.height)
//    {
//        searchPath.push_back(mediumResource.directory);
//
//        pDirector->setContentScaleFactor(MIN(frameSize.width/designSize.width, frameSize.height/designSize.height));
//    }
//    // if the frame's height is smaller than the height of medium resource size, select small resource.
//	else
//    {
//        searchPath.push_back(smallResource.directory);
//
//        pDirector->setContentScaleFactor(MIN(frameSize.width/designSize.width, frameSize.height/designSize.height));
//    }
//
//    // set searching path
//    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //ChartboostX::sharedChartboostX()->startSession();
    //ChartboostX::sharedChartboostX()->setAppId("531578d9f8975c0832e94caa");
    //ChartboostX::sharedChartboostX()->setAppSignature("3d81a0e58606912fd7817f07f835160c9aec847c");

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
