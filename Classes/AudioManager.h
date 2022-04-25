#pragma once

class AudioManager
{
public:
	static int backgroundMusic, selectSound, selectIncorrectPokemonSound, removePokemonSound;

	static float backgroundVolume, effectVolume;

	static void playBackgroundMusic();

	static void stopBackgroundMusic();

	static void setBackgroundVolume(float volume);

	static void playSelectSoundEffect();

	static void playSelectIncorrectPokemonSoundEffect();

	static void playRemovePokemonSoundEffect();

	static void setEffectVolume(float volume);
	static void playAllMusic();
	static void stopAllMusic();


};