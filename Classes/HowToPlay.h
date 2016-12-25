/*
 * HowToPlayScene.h
 *
 *  Created on: 2013-12-19
 *      Author: robust
 */

#ifndef HOWTOPLAYSCENE_H_
#define HOWTOPLAYSCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class HowToPlay : public cocos2d::CCLayer {
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    void registerWithTouchDispatcher();
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	virtual void keyBackClicked();

    CREATE_FUNC(HowToPlay);
};

#endif /* HOWTOPLAYSCENE_H_ */
