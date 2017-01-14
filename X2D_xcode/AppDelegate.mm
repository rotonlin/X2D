//
//  AppDelegate.m
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#import "AppDelegate.h"
#import "GLView.h"
#import "ViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

@synthesize _pWindow;
@synthesize _pGlView;
@synthesize _pViewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Hide the topest status bar
    [[UIApplication sharedApplication] setStatusBarHidden:YES];

    self._pWindow = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.

    CGRect size = [[UIScreen mainScreen] bounds];
    _pGlView = [[GLView alloc] initWithFrame:size];
    [_pGlView Initialize:8 GreenSize:8 BlueSize:8 AlphaSize:8 DepthSize:16 StencilSize:0 SamplesSize:0];
    [self._pWindow addSubview:_pGlView];

    self._pWindow.backgroundColor = [UIColor clearColor];

    _pViewController = [[ViewController alloc] init];
    self._pWindow.rootViewController = _pViewController;

    [self._pWindow makeKeyAndVisible];

    

    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {

}

- (void)applicationDidEnterBackground:(UIApplication *)application {

}

- (void)applicationWillEnterForeground:(UIApplication *)application {

}

- (void)applicationDidBecomeActive:(UIApplication *)application {

}

- (void)applicationWillTerminate:(UIApplication *)application {

}

@end
