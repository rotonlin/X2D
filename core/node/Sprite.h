//
//  Sprite.h
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Core_Sprite_h
#define Core_Sprite_h

#include "node/Node.h"
#include "res/Texture.h"
#include "res/Image.h"
//---------------------------------------

class Sprite : public Node
{
public:
	Sprite();
    virtual ~Sprite();

    _FORCE_INLINE_ void SetTexture(Ref<Texture> pTex) { _pTexture = pTex; }
    _FORCE_INLINE_ Ref<Texture> GetTexture() { return _pTexture; }

    void SetImage(Ref<Image> pImage);
    void SetImage(const std::string& rFilePath);

protected:
	virtual void Draw();

private:
    Ref<Texture> _pTexture;
};

#endif /* Sprite_h */
