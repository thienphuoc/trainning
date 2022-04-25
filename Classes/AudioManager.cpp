#include "AudioManager.h"
#include "AudioEngine.h"
#include "Definitation.h"

int AudioManager::backgroundMusic = -1;
int AudioManager::selectSound = -1;
int AudioManager::selectIncorrectPokemonSound = -1;
int AudioManager::removePokemonSound = -1;

float AudioManager::backgroundVolume = 1.0f;

float AudioManager::effectVolume = 1.0f;
void AudioManager::playBackgroundMusic()
{
	backgroundMusic = cocos2d::experimental::AudioEngine::play2d(URL_BACKGROUND_MUSIC_MP3, true, backgroundVolume);
}

void AudioManager::stopBackgroundMusic()
{
	cocos2d::experimental::AudioEngine::stop(backgroundMusic);
}

void AudioManager::setBackgroundVolume(float volume)
{
	backgroundVolume = volume;
	cocos2d::experimental::AudioEngine::setVolume(backgroundMusic, volume);
}

void AudioManager::playSelectSoundEffect()
{
	selectSound = cocos2d::experimental::AudioEngine::play2d(URL_CLICK_MP3, false, effectVolume);
}

void AudioManager::playSelectIncorrectPokemonSoundEffect()
{
	selectIncorrectPokemonSound = cocos2d::experimental::AudioEngine::play2d(URL_INCORRECT_MP3, false, effectVolume);
}

void AudioManager::playRemovePokemonSoundEffect()
{
	removePokemonSound = cocos2d::experimental::AudioEngine::play2d(URL_CORRECT_MP3, false, effectVolume);
}


void AudioManager::setEffectVolume(float volume)
{
	effectVolume = volume;
}

void AudioManager::playAllMusic()
{
	AudioManager::playBackgroundMusic();
	AudioManager::playSelectSoundEffect();
	AudioManager::playSelectIncorrectPokemonSoundEffect();
	AudioManager::playRemovePokemonSoundEffect();
}

void AudioManager::stopAllMusic()
{
	cocos2d::experimental::AudioEngine::stop(backgroundMusic);
	cocos2d::experimental::AudioEngine::stop(selectSound);
	cocos2d::experimental::AudioEngine::stop(selectIncorrectPokemonSound);
	cocos2d::experimental::AudioEngine::stop(removePokemonSound);
}
