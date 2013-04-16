#include "Stairway.hpp"
#include "Player.hpp"
#include "GameState.hpp"

Stairway::Stairway(vh::Context& context)
{
	m_sprite.setTexture(*context.graphics->getTexture("stairway.png"));
	m_collisionProfile = nullptr;
}

void Stairway::setGameState(GameState* owner)
{
	m_owner = owner;
}

void Stairway::render(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_x, m_y);
	window.draw(m_sprite);
}


void Stairway::handleCollision(Player& player)
{
	sf::IntRect AABBPlayer(player.getX(), player.getY(), 32,32 );
	sf::IntRect AABBStairway(m_x+16, m_y+16, 1,1);
	if(AABBPlayer.intersects(AABBStairway))
	{
		m_owner->notifyLevelChange();
	}
}