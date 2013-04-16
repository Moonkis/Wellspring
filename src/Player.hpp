#ifndef _WELLSPRING_PLAYER_HPP
#define _WELLSPRING_PLAYER_HPP

#include <SFML\Graphics.hpp>
#include <Vildhjarta\Context.hpp>
#include <vector>
#include "Entity.hpp"

class Player : public Entity
{
public:
	Player(vh::Context& context);
	~Player();
	void render(sf::RenderWindow& window);
	void update(float dt, float time , Tilemap& tilemap);
	
	float getHearts() { return m_hearts; }
	float getMaxHearts() { return m_maxhearts; }
	
	float getSouls() { return m_souls; }
	float getMaxSouls() { return m_maxsouls; }
	
	float getXP() { return m_xp; }
	float getNextLevel() { return m_nextlevel; }
	
	static Entity* createPlayer(vh::Context& context) { return new Player(context); }
private:
	float m_hearts, m_maxhearts;
	float m_souls, m_maxsouls;
	float m_xp, m_nextlevel;
	
	unsigned int m_level;
	unsigned int m_speed;
	unsigned int m_power;
};

#endif
