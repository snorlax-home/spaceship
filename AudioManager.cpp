#include "AudioManager.h"
#include <iostream>

using namespace std;

void AudioManager::InitializeAudio()
{
	ResultCheck(FMOD::System_Create(&audioSystem), "FMOD::System_Create Failed");
	ResultCheck(audioSystem->init(32, FMOD_INIT_NORMAL, extraDriverData), "audioSystem->init Failed");
}

void AudioManager::ResultCheck(FMOD_RESULT result, const char *message)
{
	if (result != FMOD_OK)
	{
		cout << message << endl;
	}
}

void AudioManager::LoadSounds()
{
}

FMOD::System *AudioManager::GetAudioSystem()
{
	return audioSystem;
}

FMOD::Channel *AudioManager::GetChannel()
{
	return channel;
}

FMOD::Channel **AudioManager::GetChannelAddress()
{
	return &channel;
}

FMOD_RESULT AudioManager::GetResult()
{
	return result;
}

void AudioManager::UpdateSound()
{
	ResultCheck(GetAudioSystem()->update(), "Error updating sounds");
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}