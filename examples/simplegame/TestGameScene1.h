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

union SDL_Event;

class TestGameScene1 : public Scene
{
public:
    TestGameScene1();
    ~TestGameScene1();

    virtual void Update(float fDelta);
    virtual void Init();
    virtual void DeInit();

    void AddMonster();
    void Shoot();

    void OnInput(const SDL_Event* pEvent);
private:
    Ref<Resource> _pTex;

    Ref<Sprite> _pPlayer;
};

#endif /* TestGameScene1_h */
