#pragma once
#include "fmod.hpp"

class AudioManager
{
private:
	FMOD::System *audioSystem;
	FMOD::Channel *channel = 0;
	FMOD_RESULT result;
	void *extraDriverData = 0;

public:
	// Constructor and Destructor
	AudioManager();
	~AudioManager();
	// 	Init and Load
	void InitializeAudio();
	void LoadSounds();
	// Getters
	FMOD::System *GetAudioSystem();
	FMOD::Channel *GetChannel();
	FMOD::Channel **GetChannelAddress();
	FMOD_RESULT GetResult();
	// Other Methods
	void CreateSounds(FMOD::Sound* sound, const char* soundFilePath, bool loop);
	void UpdateSound();
	void ResultCheck(FMOD_RESULT result, const char *message);
	void PlaySounds(FMOD::Sound* sound, float volume, float pitch, float pan);
};