#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "VisibleRect.h"
#include "HowToPlay.h"
#include "Game.h"
#include "GameConstants.h"
#include "SimpleAudioEngine.h"
//#include "ChartboostX.h"
#include "AccessibilityWrapper/AccessibilityWrapper.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "GameHelper.h"
#endif

#define LINE_SPACE          50
static CCPoint s_tCurPos = CCPointZero;
using namespace std;
USING_NS_CC;

using namespace CocosDenshion;

CCScene* HelloWorld::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	AccessibilityWrapper::getInstance()->onSceneStart(0);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("back.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(
	ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	/////////////////////////////
	// 3. add your codes below...
	m_pItemMenu = CCMenu::create();
	for (int i = 0; i < menuCount; ++i) {
		// #if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
		//         CCLabelBMFont* label = CCLabelBMFont::create(g_aTestNames[i].c_str(),  "fonts/arial16.fnt");
		// #else
        CCLabelTTF* label;
        
        label = textAddOutline(menuNames[i].c_str(),
                                       "fonts/akaDylan Plain.ttf", 30, ccWHITE, 1);
		
		// #endif
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this,
		menu_selector(HelloWorld::menuCallback));

		m_pItemMenu->addChild(pMenuItem, i + 10000);
		pMenuItem->setPosition(
				ccp( VisibleRect::center().x, (VisibleRect::bottom().y + (menuCount - i) * LINE_SPACE) ));

		CCRect rect = pMenuItem->rect();
		const char * str = GameConstants::getMenuNodeDesc(i);
		AccessibilityWrapper::getInstance()->addMenuSceneRect(i, str, rect.getMinX(),rect.getMaxX(),rect.getMinY(),rect.getMaxY());
	}

	m_pItemMenu->setContentSize(
			CCSizeMake(VisibleRect::getVisibleRect().size.width, (menuCount + 1) * (LINE_SPACE)));
	m_pItemMenu->setPosition(s_tCurPos);
	addChild(m_pItemMenu);
	setTouchEnabled(true);
	this->setKeypadEnabled(true);

	//add title
	CCSprite* title = CCSprite::create("title.png");
	title->setPosition(
			ccp(VisibleRect::center().x, VisibleRect::top().y - 96 - LINE_SPACE));
	//set title's scale action
	CCActionInterval* action = CCScaleBy::create(0.8, 0.96);
	CCActionInterval* action_back = action->reverse();
	CCActionInterval* seq = CCSequence::create(action, action_back, NULL);
	title->runAction(CCRepeatForever::create(seq));

	addChild(title);
    
    // 播放音乐
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background.mp3");
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);

	return true;
}

/*
 制作文字描边效果是很简单的，我们写好一段文字之后，也就是创建出一个CCLabelTTF，称之为正文CCLabelTTF。然后再创建出4个CCLabelTTF，颜色为黑色，大小同正文CCLabelTTF相同，
 称之为描边CCLabelTTF。说到这大家可能已经明白了，没错，就是把4个描边CCLabelTTF放于正文CCLabelTTF的下面，分别于左右上下与正文CCLabelTTF错开，这样描边效果就实现啦。。
 
 *string     文本
 *fontName   文本字体类型
 *fontSize   文本大小
 *color3     文本颜色
 *lineWidth  所描边的宽度
 */
CCLabelTTF* HelloWorld::textAddOutline(const char* string, const char* fontName, float fontSize,const ccColor3B &color3,float lineWidth)
{
    //描边CCLabelTTF 左
    CCLabelTTF* left = CCLabelTTF::create(string, fontName, fontSize);
    left->setColor(ccBLACK);
    
    //描边CCLabelTTF 右
    CCLabelTTF* right = CCLabelTTF::create(string, fontName, fontSize);
    right->setColor(ccBLACK);
    right->setPosition(ccp(left->getContentSize().width*0.5+lineWidth*2,left->getContentSize().height*0.5));
    left->addChild(right);
    
    //描边CCLabelTTF 上
    CCLabelTTF* up = CCLabelTTF::create(string, fontName, fontSize);
    up->setColor(ccBLACK);
    up->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5+lineWidth));
    left->addChild(up);
    
    //描边CCLabelTTF 下
    CCLabelTTF* down = CCLabelTTF::create(string, fontName, fontSize);
    down->setColor(ccBLACK);
    down->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5-lineWidth));
    left->addChild(down);
    
    //正文CCLabelTTF
    CCLabelTTF* center = CCLabelTTF::create(string, fontName, fontSize);
    center->setColor(color3);
    center->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5));
    left->addChild(center);
    
    return left;
}

void HelloWorld::menuCallback(CCObject* pSender) {
	// get the userdata, it's the index of the menu item clicked
	CCMenuItem* pMenuItem = (CCMenuItem *) (pSender);
	int nIdx = pMenuItem->getZOrder() - 10000;
	if (nIdx == 0) {
		CCScene* pScene = new CCScene();
		CCLayer* pLayer = Game::create();
		pScene->addChild(pLayer, 0);
		CCDirector::sharedDirector()->replaceScene(pScene);
		pScene->release();
	}else if (nIdx == 1){
        CCScene* pScene = new CCScene();
		CCLayer* pLayer = HowToPlay::create();
		pScene->addChild(pLayer, 0);
		CCDirector::sharedDirector()->replaceScene(pScene);
		pScene->release();
    }else if (nIdx == 2){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        //GameHelper::moreGame();
       // ChartboostX::sharedChartboostX()->showMoreApps();
#endif
    }
}

void HelloWorld::keyBackClicked(){
    CCDirector::sharedDirector()->end();
}
