//
//  Timer.cpp
//  X2D
//
//  Created by roton on 17/1/28.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Timer.h"

//events
Simple::Signal<void ()> TimerEngine::TimerEvent;


TimerEngine* TimerEngine::_gInstance = memnew(TimerEngine);

TimerEngine& TimerEngine::GetSingleton()
{
    return *_gInstance;
}

void TimerEngine::Update(uint64_t addedTime)
{
    _iGlobleTime += addedTime;

    //update nodes
    for (std::list<Node*>::iterator iter = _updateList.begin(); iter != _updateList.end(); ++iter)
    {
        if ((*iter)->ShouldUpdate())
        {
            (*iter)->Update(addedTime * 1.0 / 1000);
        }
    }

    while (!_timers.empty())
    {
        const Timer& t = _timers.top();
        if (_iGlobleTime >= t._iGloble)
        {
            if (t.shouldStop)
            {
                _timers.pop();
                continue;
            }
            //printf("timer finished event : %s\n", t._event.c_str());
            //emit events
            TimerEvent.emit();

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

void TimerEngine::Map(void *ptr, size_t connectId)
{
    std::vector<size_t>& connections = _connectMap[ptr];
    connections.push_back(connectId);
}

void TimerEngine::UnMap(void *ptr)
{
    if (_connectMap.find(ptr) != _connectMap.end())
    {
        std::vector<size_t>& connections = _connectMap[ptr];
        for (size_t i = 0, l = connections.size(); i < l; ++i)
        {
            TimerEvent.disconnect(connections[i]);
        }
    }
}

void TimerEngine::AddTimer(Timer &rTimer)
{
    _timers.push(rTimer);
}

void TimerEngine::AddToUpdateList(Node *pNode)
{
    _updateList.push_back(pNode);
}

void TimerEngine::RemoveFromUpdateList(Node *pNode)
{
    _updateList.remove(pNode);
}



