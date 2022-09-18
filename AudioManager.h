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
	virtual void InitializeAudio();
	virtual void LoadSounds();
	// Getters
	virtual FMOD::System *GetAudioSystem();
	virtual FMOD::Channel *GetChannel();
	virtual FMOD::Channel **GetChannelAddress();
	virtual FMOD_RESULT GetResult();
	// Other Methods
	virtual void UpdateSound();
	virtual void ResultCheck(FMOD_RESULT result, const char *message);
};