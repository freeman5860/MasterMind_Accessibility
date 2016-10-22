//
//  BaseSceneHelper.m
//  Mole Guess
//
//  Created by Freeman on 2016/10/22.
//
//

#import "BaseSceneHelper.h"

@implementation BaseSceneHelper

-(instancetype)init{
    mAccessibilityItems = [[NSMutableArray alloc] init];
    
    return self;
}

-(NSArray*) getAccessibilityItems
{
    return mAccessibilityItems;
}

-(void) addAccessibilityItem : (AccessibilityItem *) item{
    [mAccessibilityItems addObject:item];
}

-(void) destroyScene{
    [mAccessibilityItems removeAllObjects];
}

@end
