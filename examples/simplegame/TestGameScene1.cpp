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

TestGameScene1::TestGameScene1()
{

}

TestGameScene1::~TestGameScene1()
{

}

void TestGameScene1::Update(float fDelta)
{
    
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

    AudioEngine::GetSingleton().LoadBank("/Users/roton/Desktop/AllM3Code/X2D/examples/simplegame/Master Bank.bank");
    AudioEngine::GetSingleton().LoadBank("/Users/roton/Desktop/AllM3Code/X2D/examples/simplegame/Master Bank.strings.bank");

    AudioEngine::GetSingleton().PlayBackgroundMusic("event:/simplegame/background");

    TIMER(1.5, true, this, &TestGameScene1::AddMonster);
}

void TestGameScene1::DeInit()
{
    TIMER_DELETE(this);
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

    // 3
    //auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, randomY));
    //auto actionRemove = RemoveSelf::create();
    //pMonster->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}


