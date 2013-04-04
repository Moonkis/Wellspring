#include "Audio.hpp"
Audio::Audio()
{
	m_bgmVolume = 50;
	m_sfxVolume = 50;
}

Audio::~Audio()
{
	for(unsigned int i = 0; i < m_sfxs.size(); i++ )
	{
		m_sfxs[i]->stop();
		delete m_sfxs[i];
		m_sfxs.erase(m_sfxs.begin()+i);
		i--;
	}	
}

void Audio::playSFX(std::string sfx)
{
	sf::SoundBuffer* buffer = m_cache.get(sfx);
	if( buffer == nullptr )
	{
		buffer = new sf::SoundBuffer();
		if( !buffer->loadFromFile(sfx) )
		{
			delete buffer;
			return;
		}
		m_cache.add(sfx, buffer);
	}
	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*buffer);
	sound->setVolume(m_sfxVolume);
	m_sfxs.push_back(sound);
	m_sfxs.back()->play();
}

void Audio::stopSFXS()
{
	for( unsigned int i = 0; i < m_sfxs.size(); i++ )
	{
		m_sfxs[i]->stop();
		delete m_sfxs[i];
		m_sfxs.erase(m_sfxs.begin()+i);
		i--;
	}
}
	
void Audio::playBGM(std::string bgm)
{
	m_bgm.openFromFile(bgm);
	m_bgm.setVolume(m_bgmVolume);
	m_bgm.setLoop(true);
	m_bgm.play();
}

void Audio::stopBGM()
{
	m_bgm.stop();
}
	
float Audio::getBGMVolume()
{
	return m_bgmVolume;
}

float Audio::getSFXVolume()
{
	return m_sfxVolume;
}
	
void Audio::update()
{
	for(unsigned int i = 0; i < m_sfxs.size(); i++ )
	{
		if ( m_sfxs[i]->getStatus() == sf::Sound::Stopped )
		{
			delete m_sfxs[i];
			m_sfxs.erase(m_sfxs.begin()+i);
			i--;
		}
	}
}