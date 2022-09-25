#include "AudioManager.h"
#include <iostream>

using namespace std;

// Constructor and Destructor
AudioManager::AudioManager()
{
	audioSystem = nullptr;
	soundEffectChannel = nullptr;
	musicChannel = nullptr;
	extraDriverData = nullptr;
}

AudioManager::~AudioManager()
{
	delete this;
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

void AudioManager::InitializeAudio()
{
	// Create the audio system
	ResultCheck(FMOD::System_Create(&audioSystem), "FMOD::System_Create Failed");
	// Initialize the audio system
	ResultCheck(audioSystem->init(32, FMOD_INIT_NORMAL, extraDriverData), "audioSystem->init Failed");
}


// Getter
// Get the audio system
FMOD::System *AudioManager::GetAudioSystem()
{
	return audioSystem;
}

// Get the sound effect channel
FMOD::Channel *AudioManager::GetSoundEffectChannel()
{
	return soundEffectChannel;
}

// Get the music channel
FMOD::Channel* AudioManager::GetMusicChannel()
{
	return musicChannel;
}

// Get FMOD result
FMOD_RESULT AudioManager::GetResult()
{
	return result;
}

// Method to create sound
FMOD::Sound* AudioManager::CreateSounds(const char* soundFilePath, bool loop)
{
	FMOD::Sound* newSound;
	// Create the sound and assign it to the newSound pointer
	ResultCheck(audioSystem->createSound(soundFilePath, FMOD_DEFAULT, 0, &newSound), "audioSystem->createSound Failed");

	// Check if the sound is to be looped
	// If it is, set the mode to loop
	// Else, set the mode to not loop
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

// Method to create stream
FMOD::Sound* AudioManager::CreateStreams(const char* soundFilePath, bool loop)
{
	FMOD::Sound* newSound;
	// Create the stream and assign it to the newSound pointer
	ResultCheck(audioSystem->createStream(soundFilePath, FMOD_DEFAULT, 0, &newSound), "audioSystem->createSound Failed");

	// Check if the stream is to be looped
	// If it is, set the mode to loop
	// Else, set the mode to not loop
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

// Method to specifically play sound effects
void AudioManager::PlaySoundEffect(FMOD::Sound* sound, float volume, float pitch, float pan)
{
	// Play the sound effect
	ResultCheck(audioSystem->playSound(sound, 0, false, &soundEffectChannel), "audioSystem->playSound Failed");
	// Set channel volume
	ResultCheck(soundEffectChannel->setVolume(volume), "soundEffectChannel->setVolume Failed");
	// Set channel pitch
	ResultCheck(soundEffectChannel->setPitch(pitch), "soundEffectChannel->setPitch Failed");
	// Set channel pan
	ResultCheck(soundEffectChannel->setPan(pan), "soundEffectChannel->setPan Failed");

}

// Method to specifically play music
void AudioManager::PlayMusic(FMOD::Sound* sound, float volume, float pitch, float pan)
{
	// Play the music
	ResultCheck(audioSystem->playSound(sound, 0, false, &musicChannel), "audioSystem->playSound Failed");
	// Set channel volume
	ResultCheck(musicChannel->setVolume(volume), "musicChannel->setVolume Failed");
	// Set channel pitch
	ResultCheck(musicChannel->setPitch(pitch), "musicChannel->setPitch Failed");
	// Set channel pan 
	ResultCheck(musicChannel->setPan(pan), "musicChannel->setPan Failed");
}

// Method to alter the volume of music channel
void AudioManager::AlterMusicChannelVolume(float volume)
{
	ResultCheck(musicChannel->setVolume(volume), "musicChannel->setVolume Failed");
}

// Method to alter the pitch of the music channel
void AudioManager::AlterMusicChannelPitch(float pitch)
{
	ResultCheck(musicChannel->setPitch(pitch), "musicChannel->setPitch Failed");
}

// Method to alter the pan of the music channel
void AudioManager::AlterMusicChannelPan(float pan)
{
	ResultCheck(musicChannel->setPan(pan), "musicChannel->setPan Failed");
}

// Method to pause the music channel
void AudioManager::PauseMusicChannel()
{
	ResultCheck(musicChannel->setPaused(true), "musicChannel->setPaused Failed");
}

// Method to resume the music channel
void AudioManager::ResumeMusicChannel()
{
	ResultCheck(musicChannel->setPaused(false),"musicChannel->setPaused Failed");
}

// Method to clean up the audio manager
void AudioManager::CleanUp()
{
	// Stop all channels from playing
	soundEffectChannel->stop();
	musicChannel->stop();

	// Close audio system connection to output
	audioSystem->close();

	// Release audio system to free memory
	audioSystem->release();

	// Set pointers to null
	soundEffectChannel = nullptr;
	musicChannel = nullptr;
	audioSystem = nullptr;
	extraDriverData = nullptr;
}




