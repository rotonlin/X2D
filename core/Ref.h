//
//  Ref.h
//  X2D
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Ref_h
#define Ref_h

#include "core/Macros.h"
#include "core/Object.h"

class Reference : public Object
{
public:
	Reference()
		: _iRefCount(1)
	{

	}

	~Reference() {}

	_FORCE_INLINE_ void reference()
	{
		_iRefCount++;
	}

	_FORCE_INLINE_ bool unreference()
	{
		if (_iRefCount > 0)
		{
			_iRefCount--;
		}
        else
        {
            return false;
        }

		return _iRefCount <= 0;//die
	}

	_FORCE_INLINE_ int ReferenceCount() const
	{
		return _iRefCount;
	}

	_FORCE_INLINE_ void InitRef()
	{
		_iRefCount = 1;
	}
private:
	int _iRefCount;
};


template<class T>
class Ref
{
public:
	Ref()
	{
		_pReference = nullptr;
	}

	~Ref() 
	{
		unref();
	}

	//copy constructors
	template<class T_Other>
	Ref(const Ref<T_Other>& p_from)
	{
		_pReference = nullptr;
		Reference *refb = const_cast<Reference*>(static_cast<const Reference*>(p_from.ptr()));
		if (!refb) 
		{
			unref();
			return;
		}

		Ref r;
		r._pReference = refb->cast_to<T>();
		ref(r);
		r._pReference = nullptr;
	}

	Ref(const Ref& p_from) 
	{
		_pReference = nullptr;
		ref(p_from);
	}

	Ref(T* p_reference)
	{
		if (p_reference)
		{
			ref_pointer(p_reference);
		}
		else
		{
			_pReference = nullptr;
		}
	}

	void operator = (const Ref& p_from) 
	{
		ref(p_from);
	}

	template<class T_Other>
	void operator = (const Ref<T_Other>& p_from) 
	{
		Reference *refb = const_cast<Reference*>(static_cast<const Reference*>(p_from.ptr()));

		if (!refb)
		{
			unref();
			return;
		}

		Ref r;
		r._pReference = refb->cast_to<T>();
		ref(r);
		r._pReference = NULL;
	}

	_FORCE_INLINE_ bool operator < (const Ref<T>& p_r) const 
	{
		return _pReference < p_r._pReference;
	}

	_FORCE_INLINE_ bool operator==(const Ref<T>& p_r) const
	{
		return _pReference == p_r._pReference;
	}

	_FORCE_INLINE_ bool operator!=(const Ref<T>& p_r) const 
	{
		return _pReference != p_r._pReference;
	}

	_FORCE_INLINE_ T* operator->()
	{
		return _pReference;
	}

	_FORCE_INLINE_ T* operator*() {

		return _pReference;
	}

	_FORCE_INLINE_ const T* operator->() const
	{
		return _pReference;
	}

	_FORCE_INLINE_ const T* ptr() const 
	{
		return _pReference;
	}

	_FORCE_INLINE_ T* ptr() 
	{
		return _pReference;
	}

	_FORCE_INLINE_ const T* operator*() const 
	{
		return _pReference;
	}

	int RefCount() const
	{
		return _pReference->ReferenceCount();
	}

	bool IsNull() const
	{
		return _pReference == nullptr;
	}

	void Unref()
	{
		_pReference->unreference();
	}

private:
	void ref(const Ref& p_from)
	{
		if (p_from._pReference == _pReference)
		{
			return;
		}

		//delete self ref
		unref();

		_pReference = p_from._pReference;
		if (_pReference)
		{
			_pReference->reference();
		}
	}

	void unref()
	{
		if (_pReference && _pReference->unreference())
		{
			delete _pReference;
		}
		_pReference = nullptr;
	}

	void ref_pointer(T* p_ref) 
	{
		if (p_ref)
		{
			p_ref->InitRef();
		}
		_pReference = p_ref;
	}

	T *_pReference;
};

#endif /* Ref_h */
