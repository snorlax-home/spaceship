#pragma once
#include "fmod.hpp"
#include "AudioManager.h"
class SpaceshipAudioManager : public AudioManager
{
private:
	FMOD::Sound *pointSound, *bounceSound;

public:
	SpaceshipAudioManager();
	~SpaceshipAudioManager();
	void InitializeAudio();
	void LoadSounds();
	void playPointSound();
	void playBounceSound();
	void UpdateSound();
};
