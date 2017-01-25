//
//  Image.h
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Image_h
#define Image_h

#include "core/Macros.h"
#include "res/Resource.h"

class Image : public Resource
{
public:
	Image();
    ~Image();

    enum Format
    {
        FORMAT_GRAYSCALE,
        FORMAT_GRAYSCALE_ALPHA,
        FORMAT_RGB,
        FORMAT_RGBA,
        FORMAT_INDEXED_ALPHA,
        FORMAT_INDEXED,
    };

    _FORCE_INLINE_ void Set(int iWidth, int iHeight, Format eFormat) {_iHeight = iHeight, _iWidth = iWidth; _eFormat = eFormat;}
    _FORCE_INLINE_ std::vector<uint8_t>& WritableBuffer() {return _pBuffer;}
private:
    int _iHeight;
    int _iWidth;
    std::vector<uint8_t> _pBuffer;
    Format _eFormat;
};

#endif /* Image_h */
