/*
 * Game.h
 *
 *  Created on: 2013-12-21
 *      Author: robust
 */

#ifndef GAME_H_
#define GAME_H_

#include "cocos2d.h"

USING_NS_CC;

class Game: public cocos2d::CCLayerColor {
public:
	Game();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void step(float dt);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();
	void menuCallback(CCObject* pSender);
	void registerWithTouchDispatcher();
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	CREATE_FUNC(Game);

private:
	float mTime;
	int curCount;
	CCLabelTTF* clock;
	int answer[4];
	int curRow[4];
	CCSprite* createWorm(int index);
	CCSprite* createBird(int index);
	bool checkRow();
	void initCurRow();
	void gameOver(bool win);
	void onAnimFinish();
};

#endif /* GAME_H_ */
