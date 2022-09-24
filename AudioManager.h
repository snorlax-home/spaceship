#pragma once
#include <vector>

#include "fmod.hpp"

class AudioManager
{
private:
	// Declare variables
	FMOD::System *audioSystem;
	/*
	 * Channels created for sound effect and music
	 * Did not use the same channel
	 * as playSound will make the channel pointer point to a new channel object
	 * Music is played when the level is initialized, so the channel pointer will point to the channel object with the music
	 * If there is a sound effect played, the channel pointer will then point to the channel object with the sound effect
	 * Therefore, no longer having access to the channel object with the music
	 * making it impossible to alter properties of music which is still playing
	 * Therefore, if you want to change the properties of music while also play other sound effects
	 * a channel pointer that points to the channel object playing the music must be specifically created
	 */
	FMOD::Channel *soundEffectChannel = 0;
	FMOD::Channel *musicChannel = 0;
	FMOD_RESULT result;
	void *extraDriverData = 0;

public:
	// Constructor and Destructor
	AudioManager();
	~AudioManager();
	// 	Initialize the audio system
	void InitializeAudio();
	// Getters
	//std::vector<FMOD::Sound*> GetSounds();
	FMOD::System *GetAudioSystem();
	FMOD::Channel *GetSoundEffectChannel();
	FMOD::Channel *GetMusicChannel();
	FMOD_RESULT GetResult();
	// Other Methods
	FMOD::Sound* CreateSounds(const char* soundFilePath, bool loop);
	FMOD::Sound* CreateStreams(const char* soundFilePath, bool loop);
	void UpdateSound();
	void ResultCheck(FMOD_RESULT result, const char *message);
	void PlaySoundEffect(FMOD::Sound* sound, float volume, float pitch, float pan);
	void PlayMusic(FMOD::Sound* sound, float volume, float pitch, float pan);
	// Altering channel properties only limited to music Channel
	// TODO: continue write comment here
	void AlterMusicChannelVolume(float volume);
	void AlterMusicChannelPitch(float pitch);
	void AlterMusicChannelPan(float pan);
	//void AlterChannel(float volume, float pitch, float pan);
};