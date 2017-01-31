//
//  TestGameScene1.h
//  X2D
//
//  Created by roton on 17/1/28.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef TestGameScene1_h
#define TestGameScene1_h

#include "node/Scene.h"
#include "res/Texture.h"
#include "node/Sprite.h"
#include "animation/claw/tween/tweener_group.hpp"
#include "animation/claw/tween/single_tweener.hpp"
#include "animation/claw/tween/easing/easing_linear.hpp"

class TestGameScene1 : public Scene
{
public:
    TestGameScene1();
    ~TestGameScene1();

    virtual void Update(float fDelta);
    virtual void Init();
    virtual void DeInit();

    void AddMonster();

private:
    Ref<Resource> _pTex;

    Ref<Sprite> _pPlayer;

    claw::tween::single_tweener* _single_tween;
    claw::tween::single_tweener* _single_tween_back;
    claw::tween::tweener_group* _group;
};

#endif /* TestGameScene1_h */
