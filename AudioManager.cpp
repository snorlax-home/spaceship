#include "AudioManager.h"
#include <iostream>

using namespace std;

// Constructor and Destructor
AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
	delete this;
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

// Getter
FMOD::System *AudioManager::GetAudioSystem()
{
	return audioSystem;
}

FMOD::Channel *AudioManager::GetSoundEffectChannel()
{
	return soundEffectChannel;
}

FMOD::Channel* AudioManager::GetMusicChannel()
{
	return musicChannel;
}

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

void AudioManager::PlaySoundEffect(FMOD::Sound* sound, float volume, float pitch, float pan)
{
	ResultCheck(audioSystem->playSound(sound, 0, false, &soundEffectChannel), "audioSystem->playSound Failed");
	ResultCheck(soundEffectChannel->setVolume(volume), "soundEffectChannel->setVolume Failed");
	ResultCheck(soundEffectChannel->setPitch(pitch), "soundEffectChannel->setPitch Failed");
	ResultCheck(soundEffectChannel->setPan(pan), "soundEffectChannel->setPan Failed");

}

void AudioManager::PlayMusic(FMOD::Sound* sound, float volume, float pitch, float pan)
{
	ResultCheck(audioSystem->playSound(sound, 0, false, &musicChannel), "audioSystem->playSound Failed");
	ResultCheck(musicChannel->setVolume(volume), "musicChannel->setVolume Failed");
	ResultCheck(musicChannel->setPitch(pitch), "musicChannel->setPitch Failed");
	ResultCheck(musicChannel->setPan(pan), "musicChannel->setPan Failed");
}

void AudioManager::AlterMusicChannelVolume(float volume)
{
	ResultCheck(musicChannel->setVolume(volume), "musicChannel->setVolume Failed");
}

void AudioManager::AlterMusicChannelPitch(float pitch)
{
	ResultCheck(musicChannel->setPitch(pitch), "musicChannel->setPitch Failed");
}

void AudioManager::AlterMusicChannelPan(float pan)
{
	ResultCheck(musicChannel->setPan(pan), "musicChannel->setPan Failed");
}

void AudioManager::PauseMusicChannel()
{
	ResultCheck(musicChannel->setPaused(true), "musicChannel->setPaused Failed");
}

void AudioManager::ResumeMusicChannel()
{
	ResultCheck(musicChannel->setPaused(false),"musicChannel->setPaused Failed");
}




