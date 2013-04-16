#ifndef _WELLSPRING_STAIRWAY_HPP
#define _WELLSPRING_STAIRWAY_HPP


#include <SFML\Graphics.hpp>
#include <Vildhjarta/Context.hpp>
#include "Entity.hpp"

class Player;
class GameState;

class Stairway : public Entity
{
public:
	Stairway(vh::Context& context);
	
	void render(sf::RenderWindow& window);
	void update(float dt, float time, Tilemap& tilemap) {};
	
	void handleCollision(Player& player);
	void setGameState(GameState* owner);
	
	static Entity* createStairway(vh::Context& context) { return new Stairway(context); }
private:
	GameState* m_owner;
};

#endif