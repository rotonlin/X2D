//
//  AppDelegate.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#import <UIKit/UIKit.h>

@class GLView;
@class ViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *_pWindow;
@property (nonatomic, retain) GLView *_pGlView;
@property (nonatomic, retain) ViewController *_pViewController;

@end

