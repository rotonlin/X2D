//
//  Macros.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#include <string>
#include <queue>
#include <map>
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include <list>

#include <cstdlib>
#include <cstdio>
#include <cstddef>

#include "mathfu/glsl_mappings.h"

#ifndef _ALWAYS_INLINE_
#if defined(__GNUC__) && (__GNUC__ >= 4 )
#    define _ALWAYS_INLINE_ __attribute__((always_inline)) inline
#elif defined(__llvm__)
#    define _ALWAYS_INLINE_ __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#       define _ALWAYS_INLINE_ __forceinline
#else
#    define _ALWAYS_INLINE_ inline
#endif
#endif

#ifndef _FORCE_INLINE_
#ifdef _DEBUG
#define _FORCE_INLINE_ inline
#else
#define _FORCE_INLINE_ inline
#endif
#endif

#define memnew(class_type) (new (std::nothrow) class_type)

#define memdelete(class_type) delete class_type; class_type = nullptr

#define memnew_arr(class_type, size) (new (std::nothrow) class_type[size])

#define memdelete_arr(class_type) delete[] class_type
