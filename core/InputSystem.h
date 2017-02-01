//
//  InputSystem.h
//  X2D
//
//  Created by roton on 17/2/1.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef InputSystem_h
#define InputSystem_h

#include "Object.h"
#include "simplesignal.h"
#include "SDL.h"

#define INPUT_MAP(obj, func) \
InputSystem::GetSingleton().Map(obj, InputSystem::KeyBoradEvent.connect(Simple::slot(*obj, func)));\

#define INPUT_UNMAP(obj)\
InputSystem::GetSingleton().UnMap(obj)

class InputSystem : public Object
{
public:
    InputSystem();
    ~InputSystem();

    static InputSystem& GetSingleton();

    void Update();

    void Map(void* ptr, size_t connectId);
    void UnMap(void* ptr);
public:
    //events
    static Simple::Signal<void (SDL_Event*)> KeyBoradEvent;

private:
    std::map<void*, std::vector<size_t>> _connectMap;

    static InputSystem* _gInstance;
};


#endif /* InputSystem_h */
