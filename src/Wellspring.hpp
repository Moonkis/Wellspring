#ifndef _WELLSPRING_WELLSPRING_HPP
#define _WELLSPRING_WELLSPRING_HPP
#include <Vildhjarta\Game.hpp>
#include <Vildhjarta\ResourceCache.hpp>
#include <Vildhjarta\State.hpp>
#include <stack>
#include <SFML\Audio.hpp>

class Wellspring : public vh::GameWindow
{
public:
	~Wellspring();
private:
	// @Overriden
	bool initialize();
	void handleEvent(sf::Event& event, sf::RenderWindow& window);
	void update(float dt, float time, vh::Context& context);
	void render(sf::RenderWindow& window);
	
	vh::ResourceCache<sf::Texture> m_textures;
	vh::ResourceCache<sf::SoundBuffer> m_soundbuffers;

	std::stack<vh::State*> m_states;
};

#endif