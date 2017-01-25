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

class Application : public Reference
{
public:
	Application();
    virtual ~Application();

	int Run(int argc, char *argv[]);
};

#endif /* Application_h */
