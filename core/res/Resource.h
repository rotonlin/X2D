//
//  Resource.h
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Resource_h
#define Resource_h

#include "core/Macros.h"
#include "core/Ref.h"

class Resource : public Reference
{
public:
    static uint64_t _gResourceId;

	Resource();
    virtual ~Resource();

    _FORCE_INLINE_ uint64_t RID() const { return _iResId; }
    _FORCE_INLINE_ const std::string& Path() const {return _path;}
    void SetPath(const std::string& rPath);
private:
    uint64_t _iResId;
    std::string _path;
};

#endif /* Resource_h */
