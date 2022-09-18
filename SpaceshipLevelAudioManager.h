#pragma once
#include "AudioManager.h"
class SpaceshipLevelAudioManager : public AudioManager
{
private:
	FMOD::Sound *backgroundMusic;

public:
	SpaceshipLevelAudioManager();
	~SpaceshipLevelAudioManager();
	void InitializeAudio();
	void LoadSounds();
	void PlayBackgroundMusic();
	void UpdateSound(int point);
};
