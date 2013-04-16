#ifndef _WELLSPRING_WELLSPRING_HPP
#define _WELLSPRING_WELLSPRING_HPP

#include <Vildhjarta\Game.hpp>
#include <Vildhjarta\State.hpp>
#include <Vildhjarta\Graphics.hpp>
#include <Vildhjarta\Audio.hpp>

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
	
	/* Audio, Graphics and Statemanagment is to be integrated into Vildhjarta. */
	vh::Audio m_audio;
	vh::Graphics m_graphics;
	std::stack<vh::State*> m_states;
};

#endif