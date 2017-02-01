//
//  TestGameScene1.cpp
//  X2D
//
//  Created by roton on 17/1/28.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "TestGameScene1.h"

//test
#include "res/ResourceManager.h"
#include "Application.h"
#include "AudioEngine.h"
#include "Timer.h"
#include "InputSystem.h"
#include "animation/claw/tween/single_tweener.hpp"
#include "animation/claw/tween/tweener_group.hpp"
#include "animation/claw/tween/easing/easing_linear.hpp"

TestGameScene1::TestGameScene1()
{

}

TestGameScene1::~TestGameScene1()
{

}

void TestGameScene1::Update(float fDelta)
{
    Scene::Update(fDelta);

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    //continuous-response keys
    if(keystate[SDL_SCANCODE_W])
    {
        _pPlayer->SetPositionY(_pPlayer->Position().y() - 3);
    }

    if(keystate[SDL_SCANCODE_S])
    {
        _pPlayer->SetPositionY(_pPlayer->Position().y() + 3);
    }

    if(keystate[SDL_SCANCODE_A])
    {
        _pPlayer->SetPositionX(_pPlayer->Position().x() - 3);
    }

    if(keystate[SDL_SCANCODE_D])
    {
        _pPlayer->SetPositionX(_pPlayer->Position().x() + 3);
    }
}

void TestGameScene1::Init()
{
    SetSize(Application::GetSingleton().GetWinSize());
    SetPosition(mathfu::vec2(0, 0));

    _pTex = Load_Res("/Users/roton/Desktop/AllM3Code/X2D/examples/simplegame/player.png");

    const Sizef& winSize = Application::GetSingleton().GetWinSize();

    _pPlayer = memnew(Sprite);
    _pPlayer->SetPosition(mathfu::vec2(winSize._width * 0.05f, winSize._height * 0.5));
    _pPlayer->SetSize(Sizef(54.0f, 80.0f));
    _pPlayer->SetTexture(_pTex);
    AddChild(_pPlayer);
    _pPlayer->SetZOrder(100000);

    Load_Res("/Users/roton/Desktop/AllM3Code/X2D/examples/simplegame/Master Bank.bank");
    Load_Res("/Users/roton/Desktop/AllM3Code/X2D/examples/simplegame/Master Bank.strings.bank");

    AudioEngine::GetSingleton().PlayBackgroundMusic("event:/simplegame/background");

    TIMER(1.5, true, this, &TestGameScene1::AddMonster);
    INPUT_MAP(this, &TestGameScene1::OnInput);
}

void TestGameScene1::DeInit()
{
    TIMER_DELETE(this);
    INPUT_UNMAP(this);
}

void TestGameScene1::OnInput(const SDL_Event *pEvent)
{
    if (pEvent->type == SDL_KEYUP)
    {
        if (pEvent->key.keysym.sym == SDLK_SPACE)
        {
            Shoot();
        }
    }
}

void TestGameScene1::Shoot()
{
    AudioEngine::GetSingleton().PlayEvent("event:/simplegame/shoot");
    Ref<Sprite> pBullet = memnew(Sprite);
    Ref<Resource> pTexProj = Load_Res("/Users/roton/Desktop/AllM3Code/X2D/examples/simplegame/projectile.png");
    pBullet->SetTexture(pTexProj);
    pBullet->SetSize(Sizef(40.0f, 40.0f));

    const mathfu::vec2& playerPos = _pPlayer->Position();
    const Sizef& playerSize = _pPlayer->Size();
    pBullet->SetPosition(mathfu::vec2(playerPos.x() + playerSize._width / 2, playerPos.y()));

    //animation
    const Sizef& winSize = Application::GetSingleton().GetWinSize();
    Sprite* pMons = pBullet.ptr();
    claw::tween::single_tweener moveToX = claw::tween::single_tweener(
                                                               pBullet->Position().x() ,
                                                               winSize._width, 1.5,
                                                               [pMons](double update)
                                                               {
                                                                   pMons->SetPositionX(update);
                                                               }, claw::tween::easing_linear::ease_in);

    claw::tween::single_tweener rotationSelf = claw::tween::single_tweener(
                                                                      0.0f,
                                                                      M_PI * 2.0f,
                                                                      0.5f,
                                                                      [pMons](double update)
                                                                      {
                                                                          pMons->SetRotation(update);
                                                                      }, claw::tween::easing_linear::ease_in);
    rotationSelf.set_repeat(true);

    claw::tween::tweener_group *pMoveAndRotate = memnew(claw::tween::tweener_group);
    pMoveAndRotate->insert(moveToX);
    pMoveAndRotate->insert(rotationSelf);

    pMoveAndRotate->on_finished([pMons]
    {
        pMons->RemoveFromParent();
    });
    
    pBullet->AddTweener(pMoveAndRotate);
    AddChild(pBullet);
}

void TestGameScene1::AddMonster()
{
    Ref<Sprite> pMonster = memnew(Sprite);
    Ref<Resource> pTexMonster = Load_Res("/Users/roton/Desktop/AllM3Code/X2D/examples/simplegame/monster.png");
    pMonster->SetTexture(pTexMonster);
    pMonster->SetSize(Sizef(54.0f, 80.0f));

    const Sizef& monsterContentSize = pMonster->Size();
    auto selfContentSize = Size();
    int minY = monsterContentSize._height;
    int maxY = selfContentSize._height - monsterContentSize._height;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;

    pMonster->SetPosition(mathfu::vec2(selfContentSize._width + monsterContentSize._width / 2, randomY));
    AddChild(pMonster);

    // 2
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;

    //animation
    Sprite* pMons = pMonster.ptr();
    claw::tween::single_tweener* pMoveToX = memnew(claw::tween::single_tweener(
                                               pMonster->Position().x() ,
                                                -monsterContentSize._width / 2, randomDuration,
                                               [pMons](double update)
                                                {
                                                    pMons->SetPositionX(update);
                                                }, claw::tween::easing_linear::ease_in));
    pMoveToX->on_finished([pMons]
    {
        pMons->RemoveFromParent();
    });

    pMonster->AddTweener(pMoveToX);
}


