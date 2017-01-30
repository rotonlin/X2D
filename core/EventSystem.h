//
//  EventSystem.h
//  X2D
//
//  Created by roton on 17/1/29.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef EventSystem_h
#define EventSystem_h

#include "Object.h"
#include "simplesignal.h"


class EventSystem : public Object
{
public:
    EventSystem() {}
    ~EventSystem(){}

    static EventSystem& GetSingleton();

private:

    //std::unordered_map<std::string, Simple::Signal> _signalMap;
};

#endif /* EventSystem_h */
