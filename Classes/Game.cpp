/*
 * Game.cpp
 *
 *  Created on: 2013-12-21
 *      Author: robust
 */

#include "Game.h"
#include <string>
#include <sstream>
#include "HelloWorldScene.h"
#include "ChartboostX.h"

using namespace std;

static ccColor3B colors[6] = { ccc3(255, 0, 0), ccc3(0, 255, 0), ccc3(0, 0,
		255), ccc3(255, 255, 0), ccc3(255, 255, 255), ccc3(44, 44, 44) };
//static int wormTag = 1;

Game::Game() :
		mTime(0), curCount(0), clock(NULL) {
	for (int i = 0; i < 4; i++) {
		answer[i] = rand() % 6;
	}
	initCurRow();
}

CCScene* Game::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	Game *layer = Game::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Game::init() {
	if (!CCLayerColor::initWithColor(ccc4(154, 232, 86, 255))) {
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", this,
			menu_selector(Game::menuCallback));

	pCloseItem->setPosition(
			ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
					origin.y + visibleSize.height - pCloseItem->getContentSize().height/2));
    pCloseItem->setScale(0.7);

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create();
	pMenu->addChild(pCloseItem, 10000);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	int space_x = origin.x + 33;
	int space_y = origin.y + 108;
	int sw = 80;
	int sh = 64;
	for (int i = 35; i >= 0; i--) {
		int x = i % 4;
		int y = (int) (i / 4);
		CCSprite* h = CCSprite::create("hole_back.png");
//		h->setScaleY(sh / h->getContentSize().height);
//		h->setTextureRect(CCRectMake(0, 0, 106, 30));
		h->setPosition(ccp(space_x + (x+0.5) * sw, space_y + (y-0.5) * sh));
		//按照顺序设置tag
		addChild(h, 0, i);

		CCSprite* hf = CCSprite::create("hole.png");
		hf->setPosition(
		ccp(hf->getContentSize().width / 2, hf->getContentSize().height / 2));
		//设置zorder，遮挡虫子
		h->addChild(hf, 1);

		if (x == 0) {
			//添加左边数字
			stringstream ss;
			ss << y + 1;
			string str;
			ss >> str;
			CCLabelTTF* label = CCLabelTTF::create(str.c_str(),
					"fonts/akaDylan Plain.ttf", 20);
			label->setPosition(ccp(space_x + x * sw - 23, space_y + y * sh + 10));
			addChild(label);
		} else if (x == 3) {
			//添加鸟巢
			CCSprite* nest = CCSprite::create("nest.png");
			nest->setPosition(
					ccp(space_x + x * sw + 109 + nest->getContentSize().width*0.5, space_y + y * sh - 20 + nest->getContentSize().height * 0.5));
			//设置tag，从42开始
			addChild(nest, 0, 42 + y);
		}
	}

	//添加底部虫子
	int adjust = origin.x - 5;
	int space = 81;
	int pos_y = origin.y;
	float height;
	for (int i = 0; i < 6; i++) {
		CCSprite* h = CCSprite::create("hole_back.png");
		height = h->getContentSize().height;
//		h->setScaleY(sh / height);
		h->setPosition(ccp(adjust + (i+0.5) * space, pos_y));
		//设置tag，从36开始
		addChild(h, 0, 36 + i);
		CCSprite* worm = createWorm(i);
		worm->setPosition(
		ccp(worm->getContentSize().width / 2, height - 15));
		h->addChild(worm);
		CCSprite* hf = CCSprite::create("hole.png");
		hf->setPosition(
		ccp(hf->getContentSize().width / 2, hf->getContentSize().height / 2));
		h->addChild(hf);
	}

	clock = CCLabelTTF::create("", "fonts/akaDylan Plain.ttf", 20);
	clock->setPosition(ccp(space_x + 40, 700));
	clock->setColor(ccc3(255, 0, 0));
	addChild(clock);
	schedule(schedule_selector(Game::step));

	this->setTouchEnabled(true);

	return true;
}

void Game::initCurRow() {
	for (int i = 0; i < 4; i++) {
		curRow[i] = -1;
	}
}

void Game::step(float dt) {
	mTime += dt;
	char str[12] = { 0 };
	sprintf(str, "%d:%d", (int) mTime / 60, (int) mTime % 60);
	clock->setString(str);
}

void Game::menuCallback(CCObject* pSender) {
	CCMenuItem* pMenuItem = (CCMenuItem *) (pSender);
	int nIdx = pMenuItem->getZOrder() - 10000;
	switch (nIdx) {
        case 0:{
            CCScene* pHelloScene = new CCScene();
            CCLayer* pHelloLayer = HelloWorld::create();
            pHelloScene->addChild(pHelloLayer, 0);
            CCDirector::sharedDirector()->replaceScene(pHelloScene);
            pHelloScene->release();
            break;
        }
        case 1:{
            //play again
            CCScene* pScene = new CCScene();
            CCLayer* pLayer = Game::create();
            pScene->addChild(pLayer, 0);
            CCDirector::sharedDirector()->replaceScene(pScene);
            pScene->release();
            break;
        }
	}
}

/**
 * 为了方便实现缩小动画，已经设置其轴点为（0，0）
 */
CCSprite* Game::createWorm(int i) {
	char str[12] = { 0 };
	sprintf(str, "worm%d.png", i + 1);
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(str);
	CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture,
	CCRectMake(52*0, 52*0, 52, 52));
	CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture,
	CCRectMake(52*1, 52*0, 52, 52));
	CCSprite* worm = CCSprite::createWithSpriteFrame(frame0);
	worm->setAnchorPoint(CCPointZero);
	CCArray* animFrames = CCArray::createWithCapacity(2);
	animFrames->addObject(frame0);
	animFrames->addObject(frame1);
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames,
			1.5f);
	CCAnimate *animate = CCAnimate::create(animation);
	CCActionInterval* seq = CCSequence::create(animate, CCFlipX::create(true),
			animate->copy()->autorelease(), CCFlipX::create(false),
			NULL);
	worm->setColor(colors[i]);
	worm->runAction(CCRepeatForever::create(seq));
	return worm;
}

CCSprite* Game::createBird(int i) {
	char str[12] = { 0 };
	sprintf(str, "bird%d.png", i);
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(str);
	CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture,
	CCRectMake(36*0, 36*0, 36, 27));
	CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture,
	CCRectMake(36*1, 36*0, 36, 27));
	CCSprite* bird = CCSprite::createWithSpriteFrame(frame0);
	CCArray* animFrames = CCArray::createWithCapacity(2);
	animFrames->addObject(frame0);
	animFrames->addObject(frame1);
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames,
			1.5f);
	CCAnimate *animate = CCAnimate::create(animation);
	CCActionInterval* seq = CCSequence::create(animate, CCFlipX::create(true),
			animate->copy()->autorelease(), CCFlipX::create(false),
			NULL);
	bird->runAction(CCRepeatForever::create(seq));
	return bird;
}

bool Game::checkRow() {
	int result = 0;
	CCSprite* nest = (CCSprite*) getChildByTag(42 + (curCount - 1) / 4);
	CCSprite* bird;
//	float h, w;
	bool checked1[] = { false, false, false, false };
	for (int i = 0; i < 4; i++) {
		if (curRow[i] == answer[i]) {
			result++;
			checked1[i] = true;
			bird = createBird(2);
//			w = bird->getContentSize().width;
//			h = bird->getContentSize().height;
//			bird->setPosition(ccp(w / 2 + result % 2 * w, h / 2 + result  / 2 * h));
			//鸟的图片宽高分别为36*27，为了使图片能居中，设置位置时，分别添加了5,20
			//下同
			bird->setPosition(
			ccp(23 + (result-1) % 2 * 36, 33.5 + (result-1) / 2 * 27));
			nest->addChild(bird);
		}
	}
	if (result == 4) {
		gameOver(true);
		return true;
	}
	if (curCount > 35) {
		gameOver(false);
		return false;
	}
	bool checked2[4];
	for (int i = 0; i < 4; i++) {
		checked2[i] = checked1[i];
	}
	for (int i = 0; i < 4; i++) {
		if (checked1[i]) {
			continue;
		}
		int cur = curRow[i];
		for (int j = 0; j < 4; j++) {
			if (checked2[j] == true) {
				continue;
			}
			if (answer[j] == cur && !checked2[j]) {
				checked2[j] = true;
				result++;
				bird = createBird(1);
//				w = bird->getContentSize().width;
//				h = bird->getContentSize().height;
				bird->setPosition(
						ccp(23 + (result - 1) % 2 * 36, 33.5 + (result-1) / 2 * 27));
//				bird->setPosition(ccp(w / 2 + result % 2 * w, h / 2 + result  / 2 * h));
				nest->addChild(bird);
				break;
			}
		}
	}
	return false;
}

void Game::gameOver(bool win) {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSprite* dialog = CCSprite::create("dialog.png");
	dialog->setPosition(
	ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	string result;
	if (win) {
		result = "You Win!";
	} else {
		result = "You Lose!";
	}
	CCLabelTTF* label = CCLabelTTF::create(result.c_str(),
			"fonts/akaDylan Plain.ttf", 40);
	float w = dialog->getContentSize().width;
	float h = dialog->getContentSize().height;
	label->setColor(colors[2]);
	label->setPosition(ccp(w / 2, h - label->getContentSize().height / 2 - 20));
	dialog->addChild(label);
	char str[12] = { 0 };
	sprintf(str, "%d:%d", (int) mTime / 60, (int) mTime % 60);
	label = CCLabelTTF::create(str, "fonts/akaDylan Plain.ttf", 20);
	label->setColor(colors[0]);
	label->setPosition(ccp(w / 2, h - label->getContentSize().height / 2 - 80));
	dialog->addChild(label);
	for (int i = 0; i < 4; i++) {
		CCSprite* ball = CCSprite::create("ball.png");
		ball->setColor(colors[answer[i]]);
		ball->setPosition(ccp(110 + i * 80, 90));
		dialog->addChild(ball);
	}
	label = CCLabelTTF::create("Play Again", "fonts/akaDylan Plain.ttf", 20);
	label->setColor(colors[2]);
	CCMenu* menu = CCMenu::create();
	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, dialog,
	menu_selector(Game::menuCallback));
	pMenuItem->setPosition(ccp(w / 2, 30));
//	menu->setContentSize(CCSizeMake(w, h));
	menu->setPosition(CCPointZero);
	menu->addChild(pMenuItem, 10001);
	dialog->addChild(menu);
	addChild(dialog);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    ChartboostX::sharedChartboostX()->hasCachedInterstitial();
    ChartboostX::sharedChartboostX()->showInterstitial();
#endif
}

void Game::onAnimFinish(){
	this->setTouchEnabled(true);
}

void Game::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
//	CCTouch *touch = (CCTouch *) touches->anyObject();
//	CCPoint beginLoc = touch->getLocationInView();
//	beginLoc = CCDirector::sharedDirector()->convertToGL(beginLoc);

	if (curCount > 35) {
		return;
	}
	for (int i = 36; i < 42; i++) {
		CCSprite* sprite = (CCSprite*) getChildByTag(i);
		if (sprite == NULL) {
			return;
		}
		CCPoint point = sprite->convertTouchToNodeSpace(
				(CCTouch *) touches->anyObject());
		CCSprite* click = (CCSprite*) sprite->getChildren()->objectAtIndex(0);
		if (click->boundingBox().containsPoint(point)) {
			setTouchEnabled(false);
			CCActionInterval* action = CCScaleBy::create(0.2, 1, 0.01);
			CCActionInterval* action_back = action->reverse();
			CCActionInterval* seq = CCSequence::create(action, action_back,
					NULL);
			CCFiniteTimeAction* actions = CCSequence::create(seq,
                    CCCallFunc::create(this,callfunc_selector(Game::onAnimFinish)),NULL);
			click->runAction(actions);
			sprite = (CCSprite*) getChildByTag(curCount);
			curRow[curCount % 4] = i - 36;
			CCSprite* worm = createWorm(i - 36);
			worm->setPosition(
					ccp(worm->getContentSize().width / 2, sprite->getContentSize().height - 15));
			worm->setScaleY(0.01);
			CCActionInterval* zoomIn = CCScaleBy::create(0.2, 1, 100);
			worm->runAction(zoomIn);
			sprite->addChild(worm);
			curCount++;
			if (curCount % 4 == 0) {
				checkRow();
			}
			return;
		}
//		CCRect rect = ((CCSprite*)getChildByTag(i)->getChildren()->objectAtIndex(1))->boundingBox();
//		if(rect.containsPoint(beginLoc)){
//			cout<< i - 36 <<" clicked"<<endl;
//			return;
//		}
	}
}

void Game::registerWithTouchDispatcher() {
// CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(
			this, 0);
}
