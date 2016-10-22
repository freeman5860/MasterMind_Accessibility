//
//  AccessibilityView.h
//  Mole Guess
//
//  Created by Freeman on 2016/10/22.
//
//

#import <UIKit/UIKit.h>
#import "AccessibilityItem.h"
#import "BaseSceneHelper.h"

@interface AccessibilityView : UIView{
    NSMutableArray * _AccessElements;
    
    BaseSceneHelper * mCurSceneHelper;
}

-(void) onSceneDestroy;
-(void) onSceneChange: (BaseSceneHelper *) scene;

@end
