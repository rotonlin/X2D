#ifndef Math_MATRIX_STACK
#define Math_MATRIX_STACK

#include <stack>
#include "core/MathUtility.h"

template<class MAT, class VEC>
class MatrixStack
{
public:
	MatrixStack()
	{
		_stack.push(MAT::Identity());
	}
	~MatrixStack(){}

	_FORCE_INLINE_ void LoadIdentity()
	{
		_stack.push(MAT::Identity());
	}

	_FORCE_INLINE_ void LoadMatrix(const MAT& rMatrix)
	{
		_stack.top() = rMatrix;
	}

	_FORCE_INLINE_ void MultMatrix(const MAT& rMatrix)
	{
		_stack.top() *= rMatrix;
	}

	_FORCE_INLINE_ void PushMatrix()
	{
		const MAT& rMat = _stack.top();
		_stack.push(rMat);
	}

	_FORCE_INLINE_ void PopMatrix() 
	{
		if (!_stack.empty())
		{
			_stack.pop();
		}
	}

	_FORCE_INLINE_ void PushMatrix(const MAT& rMatrix)
	{
		_stack.push(rMatrix);
	}

	// Two different ways to get the matrix
	_FORCE_INLINE_  const MAT& GetMatrix() const
	{ 
		return _stack.top(); 
	}

	_FORCE_INLINE_ void GetMatrix(MAT& rMatrix)
	{ 
		if (!_stack.empty())
		{
			rMatrix = _stack.top();
		}
	}

private:
	std::stack<MAT> _stack;
};

#endif
