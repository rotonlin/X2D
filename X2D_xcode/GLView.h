//
//  GLView.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GLView : UIView
{
    CAEAGLLayer* _pLayer;
}

@property (nonatomic, retain) EAGLContext* _pContext;
@property (nonatomic, assign) GLuint _iColorRenderBuffer;
@property (nonatomic, assign) GLuint _iDepthRenderBuffer;
@property (nonatomic, assign) GLuint _iFrameBuffer;

@property (nonatomic, assign) int _iViewWidth;
@property (nonatomic, assign) int _iViewHeight;

@property (nonatomic, assign) int _iRedSize;
@property (nonatomic, assign) int _iGreenSize;
@property (nonatomic, assign) int _iBlueSize;
@property (nonatomic, assign) int _iAlphaSize;

@property (nonatomic, assign) int _iDepthSize;
@property (nonatomic, assign) int _iStencilSize;

@property (nonatomic, assign) int _iSamplesSize;

-(BOOL)Initialize:(int)redsize GreenSize:(int)greensize BlueSize:(int)bluesize AlphaSize:(int)alphasize DepthSize:(int)depthsize StencilSize:(int)stencilsize SamplesSize:(int)samplessize;

@end
