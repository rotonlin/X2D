//
//  ViewController.m
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#import "ViewController.h"
#import "core/Ref.h"
#import "core/Object.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.

    x2d::Ref<Object> obj(new Object());
    NSLog(@"%d", obj.RefCount());

    x2d::Ref<Object> obj1(obj);
    NSLog(@"%d", obj.RefCount());

    {
        x2d::Ref<Object> obj2 = obj;
        NSLog(@"%d", obj.RefCount());
    }
    NSLog(@"%d", obj.RefCount());

    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
