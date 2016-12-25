//
//  AccessibilityItem.h
//  Mole Guess
//
//  Created by Freeman on 2016/10/22.
//
//

#import <Foundation/Foundation.h>

@interface AccessibilityItem : NSObject

-(void) initWithDesc: (nullable NSString *)d withRect: (CGRect)r;

@property (nonatomic) CGRect mRect;

@property (nullable, nonatomic, copy) NSString * mDesc;

@end
