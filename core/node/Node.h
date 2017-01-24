//
//  Node.h
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Core_Node_h
#define Core_Node_h

#include "Ref.h"
#include "core/Math.h"

//---------------------------------------
class Node : public Reference
{
public:
	Node();
    virtual ~Node();

	friend class Render_GLES;

	void AddChild(Ref<Node> node);
	void RemoveChild(Ref<Node> node);
	void RemoveFromParent(Ref<Node> self);

	void ConvertToGLSpace(mathfu::vec2& rVec2);
	void GetGloblePosition(mathfu::vec2& rVec2);

	//setters and getters
	_FORCE_INLINE_ void SetZOrder(int iZOrder) { _iZOrder = iZOrder; _bSortDirty = true; };
	_FORCE_INLINE_ int ZOrder() const { return _iZOrder; }

	_FORCE_INLINE_ void SetPosition(const mathfu::vec2& rPos) { _position = rPos; _bTransformDirty = true;
	}
	_FORCE_INLINE_ const mathfu::vec2& Position() const { return _position; }

	_FORCE_INLINE_ void SetSize(const Sizef& rSize) { _size = rSize; _bTransformDirty = true;}
	_FORCE_INLINE_ const Sizef& Size() const { return _size; }
	_FORCE_INLINE_ const Sizef ScaledSize() const { return Sizef(_size._width * _fScale, _size._height * _fScale); }

	_FORCE_INLINE_ const std::list<Ref<Node>>& GetChilds() const { return _childs; }

	//radians 
	_FORCE_INLINE_ void SetRotation(float fRotation) { _fRotation = fRotation; _bTransformDirty = true;}
	_FORCE_INLINE_ float Rotation() const { return _fRotation; }

	//color for all vertex in sprite
	_FORCE_INLINE_ void SetColor(const mathfu::vec4& rColor) { _color = rColor; };
	_FORCE_INLINE_ const mathfu::vec4& Color() const { return _color; }

	_FORCE_INLINE_ Node* GetParent() const { return _parent; }

	_FORCE_INLINE_ void SetScale(float fScale) { _fScale = fScale; _bTransformDirty = true; }
	_FORCE_INLINE_ float Scale() const { return _fScale; }

	const mathfu::mat3& TransformLocal();
	_FORCE_INLINE_ void SetTransform(const mathfu::mat3& rTransform) { _transform = rTransform; }
	_FORCE_INLINE_ const mathfu::mat3& GetTransform() const { return _transform; }
	_FORCE_INLINE_ const mathfu::mat3& GetLocalTransform() const { return _localTransform; }

	//get current center
	_FORCE_INLINE_ mathfu::vec2 Center() const 
	{
		return mathfu::vec2(_size._width * _fScale / 2.0f, _size._height * _fScale / 2.0f);
	}

	_FORCE_INLINE_ void SetVisible(bool bVisible) { _bVisible = bVisible; }
	_FORCE_INLINE_ bool Visible() const { return _bVisible; }
	_FORCE_INLINE_ void Hide() { _bVisible = false; }
	_FORCE_INLINE_ void Show() { _bVisible = true; }

	_FORCE_INLINE_ void SetClipByParent(bool bClip) { _bClipByParent = bClip; }
	_FORCE_INLINE_ bool ClipByParent() const { return _bClipByParent; }
protected:
	virtual void Draw();
	virtual void Update(float fDelta);

	void SortChilds();

protected:
	int _iZOrder;
	int _iSubZOrder;//child added order
	mathfu::vec2 _position;
	mathfu::vec2 _globlePositon;
	mathfu::vec4 _color;
	Sizef _size;
	float _fRotation;
	float _fScale;
	bool _bVisible;
	bool _bClipByParent;

	//tranform
	mathfu::mat3 _transform;
	mathfu::mat3 _localTransform;
private:
	bool _bSortDirty;
	bool _bTransformDirty;

	Node* _parent;//weak ref
	std::list<Ref<Node>> _childs;
};

#endif /* Node_h */
