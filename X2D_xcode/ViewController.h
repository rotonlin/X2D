//
//  ViewController.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#import <GLKit/GLKit.h>

@interface ViewController : GLKViewController
{
    GLuint vertexBufferID;
}

@property (retain, nonatomic) GLKBaseEffect *baseEffect;

@end

