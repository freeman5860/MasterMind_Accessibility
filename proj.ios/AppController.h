#import <UIKit/UIKit.h>

#import "GADInterstitial.h"
#import "GADInterstitialDelegate.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,GADInterstitialDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADInterstitial *interstitial_;
}

@end

