//
//  Application.h
//  X2D
//
//  Created by roton on 17/1/25.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Application_h
#define Application_h

#include "core/Macros.h"
#include "core/Ref.h"
#include "node/Scene.h"

class Application : public Reference
{
public:
	Application();
    virtual ~Application();

    static Application& GetSingleton();

    void RunScene(Ref<Scene> pScene);
    void Init();
    const Sizef& GetWinSize() const;

	int Run(int argc, char *argv[]);

private:
    Ref<Scene> _pCurScene;

    static Application* _gInstance;
};

#endif /* Application_h */
