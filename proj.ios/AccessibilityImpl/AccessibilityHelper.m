//
//  AccessibilityHelper.m
//  Mole Guess
//
//  Created by Freeman on 2016/10/22.
//
//

#import "AccessibilityHelper.h"

@implementation AccessibilityHelper

static AccessibilityHelper * instance = nil;

+(AccessibilityHelper*) getInstance{
    @synchronized(self) {
        if (instance == nil) {
            instance = [[self alloc] init];
            [instance onInited];
        }
    }
    return instance;
}

-(void) onInited{
    CGRect rect = [[UIScreen mainScreen] bounds];
    sWidth = rect.size.width;
    sHeight = rect.size.height;
    
    mMenuRef = [[BaseSceneHelper alloc] init];
    mPlayRef = [[BaseSceneHelper alloc] init];
    mOverRef = [[BaseSceneHelper alloc] init];
    mHelpRef = [[BaseSceneHelper alloc] init];
}

-(void) onMenuSceneLoad:(int)scene{
    switch (scene) {
        case 0:
            [self handleNewScene:mMenuRef];
            break;
        case 1:
            [self handleNewScene:mPlayRef];
            break;
        case 2:
            [self handleNewScene:mOverRef];
            break;
        case 3:
            [self handleNewScene:mHelpRef];
            break;
        default:
            NSLog(@"onMenuSceneLoad %d error", scene);
            break;
    }

}

-(void) handleNewScene:(BaseSceneHelper *)newScene{
    if(mCurRef != NULL){
        [mCurRef destroyScene];
    }
    if(mGameView){
        [mGameView onSceneDestroy];
    }
    
    mCurRef = newScene;
    
    if(mGameView){
        [mGameView onSceneChange:newScene];
    }
}

-(void) addMenuSceneRect:(NSString *)d left:(int)l right:(int)r top:(int)t bottom:(int)b{
    int sl = [self getScreenX:l];
    int sr = [self getScreenX:r];
    int st = [self getScreenY:b];
    int sb = [self getScreenY:t];
    AccessibilityItem * item = [[AccessibilityItem alloc] init];
    CGRect rect = [self getScreenRect:sl right:sr top:st bottom:sb];
    [item initWithDesc:d withRect:rect];
    if(mMenuRef != NULL){
        [mMenuRef addAccessibilityItem:item];
    }
}

-(void) addPlaySceneRect:(NSString *)d left:(int)l right:(int)r top:(int)t bottom:(int)b{
    int sl = [self getScreenX:l];
    int sr = [self getScreenX:r];
    int st = [self getScreenY:b];
    int sb = [self getScreenY:t];
    AccessibilityItem * item = [[AccessibilityItem alloc] init];
    CGRect rect = [self getScreenRect:sl right:sr top:st bottom:sb];
    [item initWithDesc:d withRect:rect];
    if(mPlayRef != NULL){
        [mPlayRef addAccessibilityItem:item];
    }
}

-(void) addSceneRect:(NSString *)d left:(int)l right:(int)r top:(int)t bottom:(int)b{
    int sl = [self getScreenX:l];
    int sr = [self getScreenX:r];
    int st = [self getScreenY:b];
    int sb = [self getScreenY:t];
    AccessibilityItem * item = [[AccessibilityItem alloc] init];
    CGRect rect = [self getScreenRect:sl right:sr top:st bottom:sb];
    [item initWithDesc:d withRect:rect];
    if(mCurRef != NULL){
        [mCurRef addAccessibilityItem:item];
    }
}

-(void) annouceStepResult:(NSString *)d{
    [self performSelector:@selector(annouceDelayImpl:) withObject:[NSString stringWithString:d] afterDelay:1.0f];
}

-(void) annouceDelayImpl:(NSString *)d{
    // 主动发声
    UIAccessibilityPostNotification(UIAccessibilityAnnouncementNotification, d);
}

-(void) setGameView:(AccessibilityView *)view{
    mGameView = view;
}

-(int) getScreenY:(int)y{
    int rH = GAME_HEIGHT * sWidth / GAME_WIDTH;
    int bH = (sHeight - rH) / 2;
    int y1 = GAME_HEIGHT - y;
    return (y1 * rH / GAME_HEIGHT + bH);
}

-(int) getScreenX:(int)x{
    return x * sWidth / GAME_WIDTH;
}

-(CGRect) getScreenRect:(int)l right:(int)r top:(int)t bottom:(int)b{
   // NSLog(@"%d,%d,%d,%d",l, r, t, b);
    return CGRectMake(l, t, r - l, b - t);
}

@end
