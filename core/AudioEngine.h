//
//  AudioEngine.h
//  X2D
//
//  Created by roton on 17/1/30.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef AudioEngine_h
#define AudioEngine_h

#include "Object.h"
#include "fmod_studio.hpp"

class AudioEngine : public Object
{
public:
    AudioEngine();
    ~AudioEngine();

    static AudioEngine& GetSingleton();

    void Init();
    void DeInit();

    void Update();
    void PlayBackgroundMusic(const char *musicPath);
    void SetBackgroundMusicParam(const char *param, float value);
    void PlayEvent(const char *eventPath);
    void PlayEventWithParam(const char *eventPath, const char *param, float value);
    void LoadBank(const std::string& bankPath);

    FMOD::Studio::EventInstance *GetEvent(const char *eventPath);
    FMOD::Studio::System * GetStudioSystem();

private:

    static AudioEngine* _gInstance;
};


#endif /* AudioEngine_h */
