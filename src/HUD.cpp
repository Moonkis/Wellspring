#include "HUD.hpp"
#include "Player.hpp"

#include <iostream>

HUD::HUD(vh::Context& context)
{
	m_health.setTexture( *context.graphics->getTexture("heartcontainers.png") );
	m_soulpower.setTexture( *context.graphics->getTexture("soulcontainers.png") );
	m_portrait.setTexture( *context.graphics->getTexture("playerportrait.png") );
	m_xpbar.setTexture( *context.graphics->getTexture("xpbar.png") );
	m_xpcontainer.setTexture( *context.graphics->getTexture("xpcontainer.png") );
}

void HUD::update(float dt, float time, float x, float y)
{
	m_portrait.setPosition(x+16,y+16);
	m_xpcontainer.setPosition(x+50, y+32);
	m_xpbar.setPosition(x+50, y+32);
	m_health.setPosition(x+14,y+48);
	m_soulpower.setPosition(x+14,y+48+14);
}

void HUD::render(sf::RenderWindow& window, Player& player)
{
	float percent =  player.getXP() / player.getNextLevel();
	sf::IntRect xprect(0,0, m_xpbar.getTexture()->getSize().x * percent, 32);
	m_xpbar.setTextureRect(xprect);
	
	
	int wholehearts =  player.getHearts();
	int wholesouls = player.getSouls();
	
	float halfheart = player.getHearts() - wholehearts;
	float halfsoul = player.getSouls() - wholesouls;
	
	float hx = m_health.getPosition().x;
	float hy = m_health.getPosition().y;
	float sx = m_soulpower.getPosition().x;
	float sy = m_soulpower.getPosition().y;
	
	for( int i = 0; i < player.getMaxHearts(); i++ )
	{
		if(i < wholehearts )
		{
			sf::IntRect subrect(0,0,16,16);
			m_health.setTextureRect(subrect);
		}
		
		else if( i >= wholehearts && halfheart >= 0.5f )
		{
			sf::IntRect subrect(16,0,16,16);
			m_health.setTextureRect(subrect);
			halfheart = 0;
		}
		else
		{
			sf::IntRect subrect(32,0,16,16);
			m_health.setTextureRect(subrect);
		}
		
		m_health.setPosition(hx + i * 16, hy);
		window.draw(m_health);
	}
	
	for( int i = 0; i < player.getMaxSouls(); i++ )
	{
		if(i < wholesouls )
		{
			sf::IntRect subrect(0,0,16,16);
			m_soulpower.setTextureRect(subrect);
		}
		else if( i >= wholesouls && halfsoul >= 0.5f )
		{
			sf::IntRect subrect(16,0,16,16);
			m_soulpower.setTextureRect(subrect);
			halfsoul = 0;
		}
		else
		{
			sf::IntRect subrect(32,0,16,16);
			m_soulpower.setTextureRect(subrect);
		}
		
		m_soulpower.setPosition(sx + i * 16, sy);
		window.draw(m_soulpower);
	}
	
	window.draw(m_portrait);
	window.draw(m_xpcontainer);
	window.draw(m_xpbar);
}