//
//  FileReader.h
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef FileAccess_h
#define FileAccess_h

#include "core/Macros.h"
#include "core/Ref.h"

class FileAccess : public Reference
{
public:
    enum SEEKTYPE
    {
        F_SEEK_SET = SEEK_SET,
        F_SEEK_CUR = SEEK_CUR,
        F_SEEK_END = SEEK_END
    };

    //ex. FileReader("aaa.txt", "rb+")..
    FileAccess(const std::string& filePath, const char* pAccessType);
    ~FileAccess();

    size_t Read(char* buffer, size_t size);

    //SEEK_SET, SEEK_CUR, SEEK_END
    int Seek(size_t size, int seekType);

    size_t write(const char* buffer, size_t size);

    size_t GetFileSize();

    _FORCE_INLINE_ const std::string& GetPath() const { return _path; };
private:
    FILE* f;
    std::string _path;
};

#endif /*FileAccess_h */
