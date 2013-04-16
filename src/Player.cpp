#include "Player.hpp"
#include "ICollisionProfile.hpp"
#include "PlayerCollisionProfile.hpp"

Player::Player(vh::Context& context)
{
	m_maxhearts = 8;
	m_hearts = 2.5;
	m_maxsouls = 3;
	m_souls = 1.5;
	m_speed = 8;
	m_power = 1;
	m_xp = 50;
	m_nextlevel = 200;
	m_level = 1;
	m_x = m_y = 0;
	m_collisionProfile = new PlayerCollisionProfile(this);
	
	m_sprite.setTexture( *context.graphics->getTexture("player.png") );
}

Player::~Player()
{
	delete m_collisionProfile;
}

void Player::render(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_x, m_y);
	window.draw(m_sprite);
}

void Player::update(float dt, float time,Tilemap& tilemap)
{
	float x = m_x;
	float y = m_y;
	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
	{
		y -= m_speed;
	}
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
	{
		y += m_speed;
	} 
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
	{
		x -= m_speed;
	} 
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
	{
		x += m_speed;
	}
	m_x = x;
	m_y = y;
}

// TODO: Get intersection amount and move back by that.
/*
void Player::handleCollision(Tilemap& tiles, float x, float y)
{
	auto checkPosition = [&](int x, int y)
	{
		x += 8;
		y += 20;
		int xRight  = x + 16;
		int yBottom = y + 8;
		bool a = (tiles[x     /32][y/32] != 1);
		bool b = (tiles[xRight/32][y/32] != 1);
		bool c = (tiles[x     /32][yBottom/32] != 1);
		bool d = (tiles[xRight/32][yBottom/32] != 1);
		return a || b || c || d;
	};
	bool moveX = true;
	bool moveY = true;
	
	if(checkPosition(x, y)) // Movement not possible, check.
	{
		if(checkPosition(x, m_y))
		{
			moveX = false;
		}
		
		if(checkPosition(m_x, y)) 
		{
			moveY = false;
		}
	}
       
    // If movement is true, then move accordingly.
	if(moveX) m_x = x;
	if(moveY) m_y = y;
}
*/