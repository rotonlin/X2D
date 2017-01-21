//
//  Macros.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Macros_h
#define Macros_h

#include <string>
#include <queue>
#include <map>
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>

#include <cstdlib>
#include <cstdio>

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
#define _FORCE_INLINE_ _ALWAYS_INLINE_
#endif
#endif

#define memnew(class_type) (new (std::nothrow) class_type)

#endif /* Macros_h */
