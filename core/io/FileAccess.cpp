//
//  Program.cpp
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "FileAccess.h"
#include <sys/stat.h>

FileAccess::FileAccess(const std::string& filePath, const char* pAccessType)
{
    f = fopen(filePath.c_str(), pAccessType);
    _path = filePath;
    if (!f)
    {
        assert("file open error!" && 0);
    }
}

FileAccess::~FileAccess()
{
    if (f)
    {
        fclose(f);
    }
}

size_t FileAccess::Read(char *buffer, size_t size)
{
    assert("buffer invalid" && buffer);
    return fread(buffer, size, 1, f);
}

int FileAccess::Seek(size_t size, int seekType)
{
    return fseek(f, size, seekType);
}

size_t FileAccess::write(const char *buffer, size_t size)
{
    assert("buffer invalid" && buffer);
    return fwrite(buffer, size, 1, f);
}

size_t FileAccess::GetFileSize()
{
    if (f)
    {
        struct stat _st;
        int res = stat(_path.c_str(), &_st);
        if (res != -1)
        {
            return _st.st_size;
        }
    }
    return 0;
}
