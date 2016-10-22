//
//  AccessibilityHelper.h
//  Mole Guess
//
//  Created by Freeman on 2016/10/22.
//
//

#import <Foundation/Foundation.h>
#import "BaseSceneHelper.h"
#import "AccessibilityView.h"

#define GAME_WIDTH 480
#define GAME_HEIGHT 720

@interface AccessibilityHelper : NSObject{
    BaseSceneHelper * mMenuRef;
    BaseSceneHelper * mPlayRef;
    BaseSceneHelper * mOverRef;
    BaseSceneHelper * mHelpRef;
    BaseSceneHelper * mCurRef;
    
    AccessibilityView * mGameView;
    
    int sWidth;
    int sHeight;
}

+ (AccessibilityHelper*) getInstance;
- (void) onInited;
- (void) onMenuSceneLoad: (int)scene;
- (void) handleNewScene: (BaseSceneHelper*) newScene;
- (void) addMenuSceneRect: (NSString*)d left:(int)l right:(int)r top:(int)t bottom:(int)b;
- (void) addPlaySceneRect: (NSString*)d left:(int)l right:(int)r top:(int)t bottom:(int)b;
- (void) addSceneRect: (NSString*)d left:(int)l right:(int)r top:(int)t bottom:(int)b;
- (void) annouceStepResult: (NSString*)d;
- (void) annouceDelayImpl: (NSString*)d;
- (void) setGameView: (AccessibilityView *)view;
- (int) getScreenX: (int)x;
- (int) getScreenY: (int)y;
- (CGRect) getScreenRect: (int)l right: (int)r top: (int)t bottom: (int)b;

@end
