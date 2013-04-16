#ifndef _WELLSPRING_ENEMY_HPP
#define _WELLSPRING_ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <Vildhjarta/Context.hpp>

class Enemy
{
public:
	virtual void render(sf::RenderWindow& window)=0;
	virtual void update(float dt, float time, vh::Context& context)=0;
	
	float getX();
	float getY();
	
protected:
	float m_x, m_y;
};


#endif