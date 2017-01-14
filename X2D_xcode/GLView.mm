//
//  GLView.m
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#import "GLView.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@implementation GLView

@synthesize _pContext;
@synthesize _iColorRenderBuffer;
@synthesize _iDepthRenderBuffer;
@synthesize _iFrameBuffer;
@synthesize _iViewWidth;
@synthesize _iViewHeight;
@synthesize _iRedSize;
@synthesize _iGreenSize;
@synthesize _iBlueSize;
@synthesize _iAlphaSize;
@synthesize _iDepthSize;
@synthesize _iStencilSize;
@synthesize _iSamplesSize;

+(Class)layerClass
{
    return [CAEAGLLayer class];
}

-(BOOL)Init
{
    return YES;
}

-(void)Finish
{
    [self DestroyBuffers];
}

-(BOOL)Initialize:(int)redsize GreenSize:(int)greensize BlueSize:(int)bluesize AlphaSize:(int)alphasize DepthSize:(int)depthsize StencilSize:(int)stencilsize SamplesSize:(int)samplessize
{
    _iRedSize = redsize;
    _iGreenSize = greensize;
    _iBlueSize = bluesize;
    _iAlphaSize = alphasize;
    _iDepthSize = depthsize;
    _iStencilSize = stencilsize;
    _iSamplesSize = samplessize;

    [self SetupLayer];
    [self SetupContext];
    [self SetupRenderBuffer];

    if (_iDepthSize > 0)
    {
        [self SetupDepthBuffer];
    }

    [self SetupFrameBuffer];

    if([self Init])
    {
        // Set up Display Link
        CADisplayLink* pDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(CADisplayLinkRender:)];
        [pDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

        return YES;
    }

    return NO;
}

-(void)SetupLayer
{
    _pLayer = (CAEAGLLayer*)self.layer;

    // layer set to no opaque
    _pLayer.opaque = NO;

    NSString* colorFormat = @"";

    if(_iRedSize == 5 && _iGreenSize == 6 && _iBlueSize == 5)
    {
        colorFormat = kEAGLColorFormatRGB565;
    }
    else if(_iRedSize == 8 && _iGreenSize == 8 && _iBlueSize == 8)
    {
        colorFormat = kEAGLColorFormatRGBA8;
    }
    else
    {
        NSLog(@"connot support this format, failed");
        exit(-1);
    }

    _pLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO],
                                kEAGLDrawablePropertyRetainedBacking,
                                kEAGLColorFormatRGBA8,
                                kEAGLDrawablePropertyColorFormat,
                                nil];
}

-(void)SetupContext
{
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _pContext = [[EAGLContext alloc] initWithAPI:api];

    if(!_pContext)
    {
        NSLog(@"Create EGL Context Failed");
        exit(-1);
    }

    if(![EAGLContext setCurrentContext:_pContext])
    {
        NSLog(@"Set Current Context Failed");
        exit(-1);
    }
}

-(void)SetupRenderBuffer
{
    glGenRenderbuffers(1, &_iColorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _iColorRenderBuffer);

    [_pContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:_pLayer];

    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_iViewWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_iViewHeight);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

-(void)SetupDepthBuffer
{
    glGenRenderbuffers(1, &_iDepthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _iDepthRenderBuffer);

    GLuint size = 0;

    if(_iDepthSize == 16)
    {
        size = GL_DEPTH_COMPONENT16;
    }
    else if(_iDepthSize == 24)
    {
        size = GL_DEPTH_COMPONENT24_OES;
    }
    else if(_iDepthSize == 32)
    {
        size = GL_DEPTH_COMPONENT32_OES;
    }
    else
    {
        NSLog(@"Invalide depth size");
    }

    if(size != 0)
    {
        glRenderbufferStorage(GL_RENDERBUFFER, size, _iViewWidth, _iViewHeight);
    }

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

-(void)SetupFrameBuffer
{
    glGenFramebuffers(1, &_iFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _iFrameBuffer);

    if(_iColorRenderBuffer)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _iColorRenderBuffer);
    }

    if(_iDepthRenderBuffer)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _iDepthRenderBuffer);
    }
}

-(void)DestroyBuffers
{
    if(_iColorRenderBuffer)
    {
        glDeleteRenderbuffers(1, &_iColorRenderBuffer);
        _iColorRenderBuffer = 0;
    }

    if(_iDepthRenderBuffer)
    {
        glDeleteRenderbuffers(1, &_iDepthRenderBuffer);
        _iDepthRenderBuffer = 0;
    }

    if(_iFrameBuffer)
    {
        glDeleteFramebuffers(1, &_iFrameBuffer);
        _iFrameBuffer = 0;
    }
}

-(void)SwapBuffers
{
    if(_pContext)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, _iColorRenderBuffer);

        [_pContext presentRenderbuffer:GL_RENDERBUFFER];

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
}

-(BOOL)Render
{
    static int frameCount = 0;

    static float red = 0.0f;
    static float green = 0.0f;
    static float blue = 0.0f;

    if(frameCount % 60 == 0)
    {
        red = rand() % 255 / 255.0f;
        green = rand() % 255 / 255.0f;
        blue = rand() % 255 / 255.0f;
    }

    glClearColor(red, green, blue, 1.0);
    glClearDepthf(-1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    [self SwapBuffers];

    frameCount++;

    return YES;
}

-(void)CADisplayLinkRender:(CADisplayLink *)displayLink
{
    [self Render];
}

@end
