#include "AudioManager.h"

void AudioManager::InitializeAudio()
{
	result = FMOD::System_Create(&audioSystem);
	result = audioSystem->init(32, FMOD_INIT_NORMAL, extraDriverData);
}

FMOD_RESULT AudioManager::CreateSounds(const char filePath, FMOD::Sound* sound) {
	return audioSystem->createSound(&filePath, FMOD_DEFAULT, 0, &sound);
};

FMOD_RESULT AudioManager::UpdateSounds() {
	return audioSystem->update();
}
FMOD_RESULT AudioManager::PlaySound(FMOD::Sound* soundSource)
{
	return audioSystem->playSound(soundSource, 0, false, &channel);
}
;

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

