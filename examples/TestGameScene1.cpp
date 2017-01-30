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
#include "node/Sprite.h"
#include "Application.h"

#include "Timer.h"

TestGameScene1::TestGameScene1()
{

}

TestGameScene1::~TestGameScene1()
{

}

void TestGameScene1::Update(float fDelta)
{
    printf("%f\n", fDelta);
}

void TestGameScene1::Init()
{
    SetSize(Application::GetSingleton().GetWinSize());
    SetPosition(mathfu::vec2(0, 0));

    _pTex = Load_Res("/Users/roton/Desktop/AllM3Code/X2D/examples/images/heros.altlas");

    Ref<Sprite> pSprite = memnew(Sprite);
    pSprite->SetPosition(mathfu::vec2(250, 150));
    pSprite->SetSize(Sizef(300.0f, 300.0f));
    //pSprite->SetColor(mathfu::vec4(0.5, 0.5, 0.2, 1));
    //pSprite->SetRotation(-M_PI / 3);
    pSprite->SetTexture("heros/zhaoyun.png");
    AddChild(pSprite);

    Ref<Sprite> pSprite1 = memnew(Sprite);
    pSprite1->SetPosition(pSprite->Center());
    pSprite1->SetSize(Sizef(100.0f, 100.0f));
    pSprite1->SetTexture("heros/test/anqila.png");
    //pSprite1->SetColor(mathfu::vec4(0.7, 0.3, 0.2, 1));
    //pSprite1->SetRotation(-M_PI / 4);
    //pSprite1->SetScale(1.2);
    pSprite->AddChild(pSprite1);

    //Ref<Sprite> pSprite2 = memnew(Sprite);
    //pSprite2->SetPosition(pSprite1->Center());
    //pSprite2->SetSize(Sizef(50.0f, 50.0f));
    //pSprite2->SetImage("/Users/roton/Desktop/AllM3Code/X2D/examples/images/image.png");
    //pSprite2->SetColor(mathfu::vec4(0.2, 0.3, 0.2, 1));
    //pSprite2->SetRotation(M_PI / 4);
    //pSprite2->Hide();
    //pSprite1->AddChild(pSprite2);


    TIMER_UPDATA(TestGameScene1, this);
}

void TestGameScene1::DeInit()
{
    TIMER_DELETE(this);
}

void TestGameScene1::TimerCallBack()
{
    printf("TimerCallBack\n");
}


