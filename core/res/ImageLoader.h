//
//  TextureLoader.h
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef ImageLoader_h
#define ImageLoader_h

#include "core/Macros.h"
#include "res/ResourceManager.h"
#include "res/Resource.h"
#include <png.h>

class ImageLoader : public ResourceLoader
{
public:
	ImageLoader();
    ~ImageLoader();

	virtual bool Detect(const std::string& fileName);
	virtual Ref<Resource> Load(const std::string& fileName);

private:
    static void ReadPngData(png_structp png_ptr,png_bytep data,png_size_t p_length);
};

#endif /* ImageLoader_h */
