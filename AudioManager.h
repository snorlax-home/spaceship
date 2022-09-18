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
	virtual void InitializeAudio();
	virtual void ResultCheck(FMOD_RESULT result, const char *message);
	virtual void LoadSounds();
	virtual FMOD::System *GetAudioSystem();
	virtual FMOD::Channel *GetChannel();
	virtual FMOD::Channel **GetChannelAddress();
	virtual FMOD_RESULT GetResult();
	virtual void UpdateSound();
	AudioManager();
	~AudioManager();
};