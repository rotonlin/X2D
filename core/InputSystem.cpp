//
//  InputSystem.cpp
//  X2D
//
//  Created by roton on 17/2/1.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "InputSystem.h"

static SDL_Event event;

InputSystem* InputSystem::_gInstance = memnew(InputSystem);

Simple::Signal<void (SDL_Event*)> InputSystem::KeyBoradEvent;

InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{

}

InputSystem& InputSystem::GetSingleton()
{
    return *_gInstance;
}

void InputSystem::Update()
{
    /* Check for events */
    while (SDL_PollEvent(&event))
    {
        KeyBoradEvent.emit(&event);
    }
}

void InputSystem::Map(void *ptr, size_t connectId)
{
    std::vector<size_t>& connections = _connectMap[ptr];
    connections.push_back(connectId);
}

void InputSystem::UnMap(void *ptr)
{
    if (_connectMap.find(ptr) != _connectMap.end())
    {
        std::vector<size_t>& connections = _connectMap[ptr];
        for (size_t i = 0, l = connections.size(); i < l; ++i)
        {
            KeyBoradEvent.disconnect(connections[i]);
        }
    }
}
