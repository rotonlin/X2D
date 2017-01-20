#ifndef Math_MATRIX_STACK
#define Math_MATRIX_STACK

#include <stack>
#include "core/Math.h"

class MatrixStack
{
public:
	MatrixStack()
	{
		_stack.push(mathfu::mat4::Identity());
	}
	~MatrixStack(){}

	inline void LoadIdentity()
	{
		_stack.push(mathfu::mat4::Identity());
	}

	inline void LoadMatrix(const mathfu::mat4& rMatrix)
	{
		_stack.top() = rMatrix;
	}

	inline void MultMatrix(const mathfu::mat4& rMatrix)
	{
		_stack.top() *= rMatrix;
	}

	inline void PushMatrix()
	{
		const mathfu::mat4& rMat = _stack.top();
		_stack.push(rMat);
	}

	inline void PopMatrix() 
	{
		if (!_stack.empty())
		{
			_stack.pop();
		}
	}

	inline void Scale(float x, float y, float z)
	{
		_stack.top() *= mathfu::mat4::FromScaleVector(mathfu::vec3(x, y, z));
	}


	inline void Translate(float x, float y, float z)
	{
		_stack.top() *= mathfu::mat4::FromTranslationVector(mathfu::vec3(x, y, z));
	}

	inline void Rotate(float angle, float x, float y, float z)
	{
		mathfu::Quaternion<float> quaternion = mathfu::Quaternion<float>::FromAngleAxis(angle, mathfu::vec3(x, y, z));
		_stack.top() *= quaternion.ToMatrix4();
	}

	inline void PushMatrix(const mathfu::mat4& rMatrix)
	{
		_stack.push(rMatrix);
	}

	// Two different ways to get the matrix
	inline const mathfu::mat4& GetMatrix()
	{ 
		return _stack.top(); 
	}

	inline void GetMatrix(mathfu::mat4& rMatrix)
	{ 
		if (!_stack.empty())
		{
			rMatrix = _stack.top();
		}
	}

private:
	std::stack<mathfu::mat4> _stack;
};

#endif