#ifndef _WELLSPRING_SPLASHSTATE_HPP
#define _WELLSPRING_SPLASHSTATE_HPP

#include <Vildhjarta\State.hpp>

class SplashState : public vh::State
{
public:
	SplashState(float fadetime, float timeBeforeFade, std::string background, vh::Context& context);
	~SplashState();
	void handleEvent(sf::Event& event, sf::RenderWindow& window);
	void update(float dt, float time, vh::Context& context);
	void render(sf::RenderWindow& window);
private:
	sf::Sprite m_background;
	sf::Color m_color;
	
	float m_fadetime;
	float m_timeBeforeFade;
	
	vh::Context* m_context;
	std::string m_gfx;
};


#endif