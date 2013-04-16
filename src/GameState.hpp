#ifndef _WELLSPRING_GAMESTATE_HPP
#define _WELLSPRING_GAMESTATE_HPP

#include <SFML\Graphics.hpp>
#include <Vildhjarta\State.hpp>
#include "Level.hpp"
#include "HUD.hpp"
#include "Player.hpp"

class GameState : public vh::State
{
public:
	GameState(vh::Context& context, sf::RenderWindow* window);
	~GameState();
	void handleEvent(sf::Event& event, sf::RenderWindow& window);
	void update(float dt, float time, vh::Context& context);
	void render(sf::RenderWindow& window);
	void notifyLevelChange();
private:
	Level m_level;
	HUD m_hud;
	Player* m_player;
	sf::RenderWindow* m_window;
	bool m_levelChange;
};



#endif