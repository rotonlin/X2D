//
//  Timer.h
//  X2D
//
//  Created by roton on 17/1/28.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Timer_h
#define Timer_h

#include <queue>

#include "Ref.h"

#define TIMER(time, event, if_repeat) \
Timer timer;\
timer.repeat = if_repeat;\
timer._iIntvel = uint64_t(time * 1000);\
timer._event = event;\
timer._iGloble = timer._iIntvel + TimerEngine::GetSingleton().GlobleTime();\
TimerEngine::GetSingleton().AddTimer(timer);\

struct Timer
{
    uint64_t _iIntvel;
    uint64_t _iGloble;
    std::string _event;
    bool repeat;

    bool operator < (const Timer& t) const
    {
        return _iGloble > t._iGloble;
    }
};

class TimerEngine : public Reference
{
public:
    TimerEngine() : _iGlobleTime(0) {}
    ~TimerEngine(){}

    static TimerEngine& GetSingleton();

    void AddTimer(Timer& rTimer);

    void Update(uint64_t addedTime);

    uint64_t GlobleTime() const {return _iGlobleTime;}
private:
    std::priority_queue<Timer> _timers;
    uint64_t _iGlobleTime;

    static TimerEngine* _gInstance;
};


#endif /* Timer_h */
