#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCallback(CCObject * pSender);

	virtual void keyBackClicked();
    
    //给文字添加描边
    CCLabelTTF* textAddOutline(const char* string, const char* fontName, float fontSize,const ccColor3B &color3,float lineWidth);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private :
    CCMenu* m_pItemMenu;
};

static const int menuCount = 2;
static const std::string menuNames[]={"开始游戏", "怎么玩","MORE GAME"};
static const std::string menuKey[]={"play_btn", "htp_btn"};
#endif // __HELLOWORLD_SCENE_H__
