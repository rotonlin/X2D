//
//  AudioEngine.cpp
//  X2D
//
//  Created by roton on 17/1/30.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "AudioEngine.h"

#define CHECK_RESULT(result) assert(result == FMOD_OK)

static FMOD::Studio::System *gSystem = 0;
static FMOD::Studio::EventInstance *gMusicEvent = 0;

AudioEngine* AudioEngine::_gInstance = memnew(AudioEngine);

AudioEngine::AudioEngine()
{

}

AudioEngine::~AudioEngine()
{

}

AudioEngine& AudioEngine::GetSingleton()
{
    return *_gInstance;
}

void AudioEngine::Init()
{
    if (gSystem == 0)
    {
        FMOD_RESULT result = FMOD::Studio::System::create(&gSystem);
        CHECK_RESULT(result);

        FMOD::System *lowLevelSystem ;
        result = gSystem->getLowLevelSystem(&lowLevelSystem);
        CHECK_RESULT(result);

        result = lowLevelSystem->setDSPBufferSize(512, 4);
        CHECK_RESULT(result);

        result = gSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
        CHECK_RESULT(result);
    }
}

void AudioEngine::DeInit()
{
    if (gSystem)
    {
        FMOD_RESULT result = gSystem->release();
        CHECK_RESULT(result);

        gSystem = 0;
    }
}

void AudioEngine::LoadBank(const std::string &bankPath)
{
    FMOD::Studio::Bank *stringsBank;
    FMOD_RESULT result = gSystem->loadBankFile(bankPath.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
    CHECK_RESULT(result);
}

FMOD::Studio::System * AudioEngine::GetStudioSystem()
{
    return gSystem;
}


void AudioEngine::PlayBackgroundMusic(const char *musicPath)
{
    if (gMusicEvent)
    {
        FMOD_RESULT result = gMusicEvent->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
        CHECK_RESULT(result);

        result = gMusicEvent->release();
        CHECK_RESULT(result);

        gMusicEvent = 0;
    }

    gMusicEvent = GetEvent(musicPath);

    FMOD_RESULT result = gMusicEvent->start();
    CHECK_RESULT(result);
}


void AudioEngine::SetBackgroundMusicParam(const char *param, float value)
{
    if (gMusicEvent)
    {
        FMOD::Studio::ParameterInstance *paramInst;
        FMOD_RESULT result = gMusicEvent->getParameter(param, &paramInst);
        CHECK_RESULT(result);

        result = paramInst->setValue(value);
        CHECK_RESULT(result);
    }
}


FMOD::Studio::EventInstance * AudioEngine::GetEvent(const char *eventPath)
{
    FMOD::Studio::System *system = GetStudioSystem();

    FMOD::Studio::EventDescription *desc;
    FMOD_RESULT result = system->getEvent(eventPath, &desc);
    CHECK_RESULT(result);

    FMOD::Studio::EventInstance *inst;
    result = desc->createInstance(&inst);
    CHECK_RESULT(result);

    return inst;
}


void AudioEngine::PlayEvent(const char *eventPath)
{
    FMOD::Studio::EventInstance *inst = GetEvent(eventPath);

    FMOD_RESULT result = inst->start();
    CHECK_RESULT(result);

    result = inst->release(); // Fire and forget
    CHECK_RESULT(result);
}


void AudioEngine::PlayEventWithParam(const char *eventPath, const char *param, float value)
{
    FMOD::Studio::EventInstance *eventInst = GetEvent(eventPath);
    
    FMOD::Studio::ParameterInstance *paramInst;
    FMOD_RESULT result = eventInst->getParameter(param, &paramInst);
    CHECK_RESULT(result);
    
    result = paramInst->setValue(value);
    CHECK_RESULT(result);
    
    result = eventInst->start();
    CHECK_RESULT(result);
    
    result = eventInst->release(); // Fire and forget
    CHECK_RESULT(result);
}


void AudioEngine::Update()
{
    FMOD::Studio::System *system = GetStudioSystem();
    
    FMOD_RESULT result = system->update();
    CHECK_RESULT(result);
}
