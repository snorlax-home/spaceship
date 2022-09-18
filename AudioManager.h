#pragma once
#include "fmod.hpp"

class AudioManager
{
private:
	FMOD::System* audioSystem;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extraDriverData = 0;

public:
	void InitializeAudio();
	FMOD_RESULT CreateSounds(const char, FMOD::Sound*);
	FMOD_RESULT UpdateSounds();
	FMOD_RESULT PlaySound(FMOD::Sound* soundSource);
	AudioManager();
	~AudioManager();

};