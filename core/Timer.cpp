//
//  Timer.cpp
//  X2D
//
//  Created by roton on 17/1/28.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Timer.h"

TimerEngine* TimerEngine::_gInstance = memnew(TimerEngine);

TimerEngine& TimerEngine::GetSingleton()
{
    return *_gInstance;
}

void TimerEngine::Update(uint64_t addedTime)
{
    _iGlobleTime += addedTime;

    while (!_timers.empty())
    {
        const Timer& t = _timers.top();
        if (_iGlobleTime >= t._iGloble)
        {
            //printf("timer finished event : %s\n", t._event.c_str());
            //emit events

            if (t.repeat)
            {
                Timer newTimer = t;
                newTimer._iGloble += newTimer._iIntvel;

                _timers.pop();
                _timers.push(newTimer);
            }
            else
            {
                _timers.pop();
            }
        }
        else
        {
            break;
        }
    }
}

void TimerEngine::AddTimer(Timer &rTimer)
{
    _timers.push(rTimer);
}
