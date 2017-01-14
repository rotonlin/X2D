//
//  Ref.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Ref_h
#define Ref_h

#include "core/Macros.h"

X2D_START

template<class T>
class RefPtr
{
public:
    RefPtr(T *ptr)
        : _ptr(ptr)
        , _iRefCount(1)
    {}

    ~RefPtr()
    {
        delete _ptr;
    }

    int _iRefCount;
    T *_ptr;
};

template<class T>
class Ref
{
public:
    Ref(T *ptr)
        : _pRefPt(new RefPtr<T>(ptr))
    {

    }

    Ref(Ref &sp)
        : _pRefPt(sp._pRefPt)
    {
        ++(_pRefPt->_iRefCount);
    }

    ~Ref()
    {
        if(--_pRefPt->_iRefCount == 0)
        {
            delete _pRefPt;
        }
    }

    Ref<T>& operator=(const Ref<T>& rhs)
    {
        ++(rhs._pRefPt->_iRefCount);
        if(--(_pRefPt->_iRefCount) == 0)
        {
            delete _pRefPt;
        }
        _pRefPt = rhs._pRefPt;

        return *this;
    }

    T* operator->()
    {
        return _pRefPt->_ptr;
    }

    int RefCount() const
    {
        return _pRefPt->_iRefCount;
    }

private:
    RefPtr<T> *_pRefPt;
};

X2D_END

#endif /* Ref_h */
