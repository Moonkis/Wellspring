#ifndef _WELLSPRING_HUD_HPP
#define _WELLSPRING_HUD_HPP

#include <SFML\Graphics.hpp>
#include <Vildhjarta\Context.hpp>

class Player;

class HUD
{
public:
	HUD(vh::Context& context);
	void update( float dt, float time, float x, float y);
	void render(sf::RenderWindow& window, Player& player);
private:
	sf::Sprite m_health;
	sf::Sprite m_soulpower;
	sf::Sprite m_portrait;
	sf::Sprite m_xpbar;
	sf::Sprite m_xpcontainer;
};

#endif