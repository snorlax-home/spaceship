#include "AudioManager.h"
#include <iostream>

using namespace std;

// Constructor and Destructor
AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::InitializeAudio()
{
	// Create the audio system
	ResultCheck(FMOD::System_Create(&audioSystem), "FMOD::System_Create Failed");
	// Initialize the audio system
	ResultCheck(audioSystem->init(32, FMOD_INIT_NORMAL, extraDriverData), "audioSystem->init Failed");
}

// Method to get FMOD results and error message for display
void AudioManager::ResultCheck(FMOD_RESULT result, const char *message)
{
	// Check if the result is an error
	if (result != FMOD_OK)
	{
		cout << message << endl;
	}
}



//
// // Abstract method to load sounds
// void AudioManager::LoadSounds()
// {
// }

// Getter
FMOD::System *AudioManager::GetAudioSystem()
{
	return audioSystem;
}

FMOD::Channel *AudioManager::GetChannel()
{
	return channel;
}

// FMOD::Channel **AudioManager::GetChannelAddress()
// {
// 	return &channel;
// }

FMOD_RESULT AudioManager::GetResult()
{
	return result;
}

FMOD::Sound* AudioManager::CreateSounds(const char* soundFilePath, bool loop)
{
	FMOD::Sound* newSound;
	ResultCheck(audioSystem->createSound(soundFilePath, FMOD_DEFAULT, 0, &newSound), "audioSystem->createSound Failed");
	if (loop)
	{
		ResultCheck(newSound->setMode(FMOD_LOOP_NORMAL), "sound->setMode Failed");
	}
	else if (!loop)
	{
		ResultCheck(newSound->setMode(FMOD_LOOP_OFF), "sound->setMode Failed");
	}
	return newSound;
}

FMOD::Sound* AudioManager::CreateStreams(const char* soundFilePath, bool loop)
{
	FMOD::Sound* newSound;
	ResultCheck(audioSystem->createStream(soundFilePath, FMOD_DEFAULT, 0, &newSound), "audioSystem->createSound Failed");
	if (loop)
	{
		ResultCheck(newSound->setMode(FMOD_LOOP_NORMAL), "sound->setMode Failed");
	}
	else if (!loop)
	{
		ResultCheck(newSound->setMode(FMOD_LOOP_OFF), "sound->setMode Failed");
	}
	return newSound;
}

// Method to update the audio system
void AudioManager::UpdateSound()
{
	ResultCheck(audioSystem->update(), "Error updating sounds");
}

void AudioManager::PlaySounds(FMOD::Sound* sound, float volume, float pitch, float pan)
{
	ResultCheck(audioSystem->playSound(sound, 0, false, &channel), "audioSystem->playSound Failed");
	ResultCheck(channel->setVolume(volume), "channel->setVolume Failed");
	ResultCheck(channel->setPitch(pitch), "channel->setPitch Failed");
	ResultCheck(channel->setPan(pan), "channel->setPan Failed");
}