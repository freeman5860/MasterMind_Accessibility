/*
 * HowToPlayScene.cpp
 *
 *  Created on: 2013-12-19
 *      Author: robust
 */

#include "HowToPlay.h"
#include "HelloWorldScene.h"
#include "ChartboostX.h"

CCScene* HowToPlay::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HowToPlay *layer = HowToPlay::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool HowToPlay::init() {
	if (!CCLayer::init()) {
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("back2.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(
	ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	this->setTouchEnabled(true);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    ChartboostX::sharedChartboostX()->hasCachedInterstitial();
    ChartboostX::sharedChartboostX()->showInterstitial();
#endif

	return true;
}

void HowToPlay::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event){
	CCScene* pScene = new CCScene();
			CCLayer* pLayer = HelloWorld::create();
			pScene->addChild(pLayer, 0);
			CCDirector::sharedDirector()->replaceScene(pScene);
			pScene->release();
}

void HowToPlay::registerWithTouchDispatcher()
{
	// CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}
