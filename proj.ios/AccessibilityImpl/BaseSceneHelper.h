//
//  BaseSceneHelper.h
//  Mole Guess
//
//  Created by Freeman on 2016/10/22.
//
//

#import <Foundation/Foundation.h>
#import "AccessibilityItem.h"

@interface BaseSceneHelper : NSObject{
    NSMutableArray * mAccessibilityItems;
}

-(NSArray *) getAccessibilityItems;
-(void) addAccessibilityItem: (AccessibilityItem *) item;
-(void) destroyScene;

@end
