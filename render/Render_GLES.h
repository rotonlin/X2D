//
//  Render_GLES.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Render_GLES_h
#define Render_GLES_h

class Render_GLES
{
public:
    Render_GLES& getSingleton();

    bool Init();
    bool DeInit();
private:
    Render_GLES();
    ~Render_GLES();

    static Render_GLES* _sInstance;
};

#endif /* Render_GLES_h */
