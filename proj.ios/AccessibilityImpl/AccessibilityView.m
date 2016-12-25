//
//  AccessibilityView.m
//  Mole Guess
//
//  Created by Freeman on 2016/10/22.
//
//

#import "AccessibilityView.h"


@implementation AccessibilityView

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (instancetype) init
{
    self = [super initWithFrame:CGRectMake(0, 0, 500, 500)];
    return self;
}

-(BOOL)isAccessibilityElement
{
    return NO;
}

-(NSArray*)getAccessElement
{
    
    if(!_AccessElements)
    {
        _AccessElements = [[NSMutableArray alloc] init];
    }
    
    if(mCurSceneHelper){
        NSArray * itemArray = [mCurSceneHelper getAccessibilityItems];
        NSInteger itemLen = [itemArray count];
        NSInteger elementLen = [_AccessElements count];
        // 如果比较不同，则更新
        if(itemLen != elementLen){
            [_AccessElements removeAllObjects];
            
            for(int i = 0; i < itemLen; i++){
                AccessibilityItem * item = (AccessibilityItem *)[itemArray objectAtIndex:i];
                UIAccessibilityElement *element = [[[UIAccessibilityElement alloc] initWithAccessibilityContainer:self] autorelease];
                element.isAccessibilityElement = YES;
                element.accessibilityTraits = UIAccessibilityTraitNone;
                element.accessibilityFrame = [self convertRect:item.mRect toView:nil];// 转换为屏幕坐标
                element.accessibilityLabel = item.mDesc;
                [_AccessElements addObject:element];
            }
            
            NSInteger newCount = [_AccessElements count];
            NSLog(@"replace all %ld", (long)newCount);
        }
    }
    
    return _AccessElements;
}

- (NSInteger)accessibilityElementCount
{
    return [self getAccessElement].count;
}

- (id)accessibilityElementAtIndex:(NSInteger)index
{
    return [[self getAccessElement] objectAtIndex:index];
}

- (NSInteger)indexOfAccessibilityElement:(id)element
{
    return [[self getAccessElement] indexOfObject:element];
}

-(void) onSceneDestroy{
    [_AccessElements removeAllObjects];
}

-(void) onSceneChange:(BaseSceneHelper *)scene{
    mCurSceneHelper = scene;
}

@end
