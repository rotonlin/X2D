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

	//setters and getters
	_FORCE_INLINE_ void SetZOrder(int iZOrder) { _iZOrder = iZOrder; _bSortDirty = true; };
	_FORCE_INLINE_ int ZOrder() const { return _iZOrder; }

	_FORCE_INLINE_ void SetPosition(const mathfu::vec2& rPos) { _position = rPos; }
	_FORCE_INLINE_ const mathfu::vec2& Position() const { return _position; }

	_FORCE_INLINE_ void SetSize(const Sizef& rSize) { _size = rSize; }
	_FORCE_INLINE_ const Sizef& Size() const { return _size; }

	_FORCE_INLINE_ const std::list<Ref<Node>>& GetChilds() const { return _childs; }

	_FORCE_INLINE_ void SetRotation(float fRotation) { _fRotation = fRotation; }
	_FORCE_INLINE_ float Rotation() const { return _fRotation; }
protected:
	virtual void Draw();
	void SortChilds();

	int _iZOrder;
	int _iSubZOrder;//child added order
	mathfu::vec2 _position;
	Sizef _size;
	float _fRotation;
private:
	bool _bSortDirty;

	std::list<Ref<Node>> _childs;
};

#endif /* Node_h */
