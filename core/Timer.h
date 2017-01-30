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

#include "Object.h"
#include "simplesignal.h"

#define ADD_TIMER(time, if_repeat) \
Timer timer;\
timer.repeat = if_repeat;\
timer.shouldStop = false;\
timer._iIntvel = uint64_t(time * 1000);\
timer._iGloble = timer._iIntvel + TimerEngine::GetSingleton().GlobleTime();\
TimerEngine::GetSingleton().AddTimer(timer);

#define TIMER(time, if_repeat, obj, func) \
ADD_TIMER(time, if_repeat)\
TimerEngine::GetSingleton().Map(obj, TimerEngine::TimerEvent.connect(Simple::slot(*obj, func)));\

#define TIMER_UPDATA(class, obj)\
ADD_TIMER(0.016f, true)\
TimerEngine::GetSingleton().Map(obj, TimerEngine::TimerEvent.connect(Simple::slot(*obj, &class::Update)));\

#define TIMER_DELETE(obj)\
TimerEngine::GetSingleton().UnMap(obj)


struct Timer
{
    uint64_t _iIntvel;
    uint64_t _iGloble;
    bool repeat;
    bool shouldStop;

    bool operator < (const Timer& t) const
    {
        return _iGloble > t._iGloble;
    }
};

class TimerEngine : public Object
{
public:
    TimerEngine() : _iGlobleTime(0) {}
    ~TimerEngine(){}

    static TimerEngine& GetSingleton();

    void AddTimer(Timer& rTimer);

    void Update(uint64_t addedTime);

    uint64_t GlobleTime() const {return _iGlobleTime;}

    void Map(void* ptr, size_t connectId);
    void UnMap(void* ptr);
public:
    //events
    static Simple::Signal<void (float)> TimerEvent;
private:
    std::priority_queue<Timer> _timers;
    uint64_t _iGlobleTime;

    std::map<void*, std::vector<size_t>> _connectMap;

    static TimerEngine* _gInstance;
};


#endif /* Timer_h */
