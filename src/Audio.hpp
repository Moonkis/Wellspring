#ifndef _WELLSPRING_AUDIO_HPP
#define _WELLSPRING_AUDIO_HPP

#include <VILDHJARTA\ResourceCache.hpp>
#include <SFML\Audio.hpp>

#include <string>
#include <vector>
class Audio
{
public:
	Audio();
	~Audio();
	
	void playSFX(std::string sfx);
	void stopSFXS();
	
	void playBGM(std::string bgm);
	void stopBGM();
	
	float getBGMVolume();
	float getSFXVolume();
	
	void update();
private:
	vh::ResourceCache<sf::SoundBuffer> m_cache;
	std::vector<sf::Sound*> m_sfxs;
	sf::Music m_bgm;
	
	float m_bgmVolume;
	float m_sfxVolume;
};

#endif