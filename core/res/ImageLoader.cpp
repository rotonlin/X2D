//
//  TextureLoader.cpp
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "res/ImageLoader.h"
#include "io/FileAccess.h"
#include "res/Image.h"
#include "res/Texture.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "res/ResourceCache.h"

static void _png_error_function(png_structp, png_const_charp text)
{
    printf("%s\n", text);
}

static void _png_warn_function(png_structp, png_const_charp text)
{
    printf("%s\n", text);
}

//----------------------------------------------------------------------------------------------------

ImageLoader::ImageLoader()
{

}

ImageLoader::~ImageLoader()
{

}

void ImageLoader::ReadPngData(png_structp png_ptr,png_bytep data, png_size_t p_length)
{
    FileAccess *f = (FileAccess*)png_get_io_ptr(png_ptr);
    f->Read((char*)data, p_length);
}

bool ImageLoader::Detect(const std::string& fileName)
{
    if (fileName.rfind(".png") != std::string::npos
        || fileName.rfind(".altlas") != std::string::npos)
    {
        return true;
    }

	return false;
}


Ref<Resource> ImageLoader::Load(const std::string &fileName)
{
    if (fileName.rfind(".altlas") != std::string::npos)
    {
        return LoadAltlasTexture(fileName);
    }

    Ref<ImageTexture> pTex = ResourceCache::GetSingleton().GetResource(fileName);
    if (pTex.ptr())
    {
        return pTex;
    }

    Ref<Image> pImage = LoadImage(fileName);
    pTex = pImage->CreateTexture();
    pTex->SetPath(fileName);
    return pTex;
}

//load altlas
Ref<Resource> ImageLoader::LoadAltlasTexture(const std::string &fileName)
{
    //check cache
    size_t index = fileName.rfind(".");

    std::string imagePath = fileName.substr(0, index) + ".png";

    Ref<AltlasTesture> pTex = ResourceCache::GetSingleton().GetResource(imagePath);
    if (pTex.ptr())
    {
        return pTex;
    }

    //if texture not in cache,  load texture
    Ref<Image> pImage = LoadImage(imagePath);
    pTex = pImage->CreateAltlaTexture();
    pTex->SetPath(imagePath);

    Ref<FileAccess> fileReader = memnew(FileAccess(fileName.c_str(), "rb"));

    std::string jsonFile;

    size_t fileSize =fileReader->GetFileSize();
    char * jsonBuffer = memnew_arr(char, fileSize + 1);
    fileReader->Read(jsonBuffer, fileSize);
    jsonBuffer[fileSize] = 0;

    rapidjson::Document document;
    if(document.Parse(jsonBuffer).HasParseError())
    {
        memdelete_arr(jsonBuffer);
        return nullptr;
    }

    if (document.HasMember("meta"))
    {
        rapidjson::Value& meta = document["meta"];
        if (meta.HasMember("image"))
        {
            //create altlas by texture
            if (document.HasMember("frames"))
            {
                const rapidjson::Value& frames = document["frames"];
                for (int i = 0, l = frames.Size(); i < l; ++i)
                {
                    const rapidjson::Value& frm = frames[i]["frame"];
                    Rectf subRec(frm["x"].GetFloat(), frm["y"].GetFloat(), frm["w"].GetFloat(), frm["h"].GetFloat());
                    Ref<Altlas> pAltla = memnew(Altlas);
                    pAltla->Init(pTex->GetRect(), subRec);
                    pAltla->SetTID(pTex->TID());

                    std::string imagesetName = meta["image"].GetString();
                    imagesetName = imagesetName.substr(0, imagesetName.length() - 4);

                    std::string altlasName = imagesetName + "/" + frames[i]["filename"].GetString();
                    pAltla->SetPath(altlasName);
                    pTex->AddAltla(altlasName, pAltla);
                }
            }
            memdelete_arr(jsonBuffer);

            return pTex;
        }
    }

    memdelete_arr(jsonBuffer);
    return nullptr;
}

Ref<Resource> ImageLoader::LoadImage(const std::string& fileName)
{
    Ref<FileAccess> fileReader = memnew(FileAccess(fileName.c_str(), "rb"));

    png_structp png;
    png_infop info;

    //create png ptr
    png = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                   (png_voidp)NULL,
                                   _png_error_function,
                                   _png_warn_function);
    if (png == nullptr)
    {
        printf("Out of Memory");
        return nullptr;
    }

    info = png_create_info_struct(png);
    if (!info)
    {
        png_destroy_read_struct(&png,NULL,NULL);
        printf("Out of Memory\n");
        return nullptr;
    }

    if (setjmp(png_jmpbuf(png)))
    {
        png_destroy_read_struct(&png,NULL,NULL);
        printf("PNG Corrupted\n");
        return nullptr;
    }

    png_set_read_fn(png,(void*)fileReader.ptr(),(png_rw_ptr)ReadPngData);

    png_uint_32 width, height;
    int depth, color;

    png_read_info(png, info);
    png_get_IHDR(png, info, &width, &height, &depth, &color, NULL, NULL, NULL);

    //printf("Image width:%i\n", width);
    //printf("Image Height:%i\n", height);
    //printf("Bit depth:%i\n", depth);
    //printf("Color type:%i\n", color);

    if (depth<8)
    { //only bit dept 8 per channel is handled
        png_set_packing(png);
    };

    if (depth > 8) {
        png_set_strip_16(png);
        png_read_update_info(png, info);
    }

    if (png_get_valid(png,info,PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(png);
        png_read_update_info(png, info);
        png_get_IHDR(png, info, &width, &height, &depth, &color, NULL, NULL, NULL);
    }

    int palette_colors = 0;
    int palette_components = 0;
    int components = 0;

    Image::Format fmt;
    switch(color)
    {
        case PNG_COLOR_TYPE_GRAY:
        {
            fmt=Image::FORMAT_GRAYSCALE;
            components=1;
        } break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
        {
            fmt=Image::FORMAT_GRAYSCALE_ALPHA;
            components=2;
        } break;
        case PNG_COLOR_TYPE_RGB:
        {
            fmt=Image::FORMAT_RGB;
            components=3;
        } break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
        {
            fmt=Image::FORMAT_RGBA;
            components=4;
        } break;
        case PNG_COLOR_TYPE_PALETTE:
        {
            int ntrans = 0;
            png_get_tRNS(png, info, NULL, &ntrans, NULL);
            //printf("transparent colors %i\n", ntrans);

            fmt = ntrans > 0 ? Image::FORMAT_INDEXED_ALPHA : Image::FORMAT_INDEXED;
            palette_components = ntrans > 0 ? 4 : 3;
            components = 1;
            
            png_colorp colors;
            png_get_PLTE(png, info, &colors, &palette_colors);
            
        } break;
        default:
        {
            printf("INVALID PNG TYPE\n");
            png_destroy_read_struct(&png, &info, NULL);
            return nullptr;
        } break;
    }

    int rowsize = components * width;

    Ref<Image> pImage = memnew(Image);
    pImage->Set(width, height, fmt, components);
    std::vector<uint8_t>& dstbuff = pImage->WritableBuffer();

    dstbuff.resize(rowsize * height + palette_components * 256);

    uint8_t* data = &dstbuff[0];

    uint8_t **row_p = new uint8_t* [height];

    for (unsigned int i = 0; i < height; i++)
    {
        row_p[i] = &data[components * width * i];
    }

    png_read_image(png, (png_bytep*)row_p);

    if (palette_colors)
    {
        uint8_t *r_pal = &data[components * width * height]; // end of the array
        png_colorp colors;
        int num;
        png_get_PLTE(png, info, &colors, &num);

        int ofs = 0;
        for (int i=0; i < palette_colors; i++)
        {
            r_pal[ofs + 0] = colors[i].red;
            r_pal[ofs + 1] = colors[i].green;
            r_pal[ofs + 2] = colors[i].blue;
            if (palette_components == 4)
            {
                r_pal[ofs + 3] = 255;
            };
            ofs += palette_components;
        };

        if (fmt == Image::FORMAT_INDEXED_ALPHA)
        {
            png_color_16p alphas;
            png_bytep alpha_idx;
            int count;
            png_get_tRNS(png, info, &alpha_idx, &count, &alphas);
            for (int i=0; i<count; i++)
            {
                r_pal[i*4+3] = alpha_idx[i];
            };
        };
    };

    delete[] row_p;

    png_destroy_read_struct(&png, &info, NULL );

	return pImage;
}
