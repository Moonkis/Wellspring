#include "Door.hpp"
#include "Room.hpp"
#include "Player.hpp"
#include <iostream>

Door::Door(vh::Context& context)
{
	m_sprite.setTexture(*context.graphics->getTexture("door.png"));
	m_textureRect.top = 0;
	m_textureRect.left = 32;
	m_textureRect.width = 32;
	m_textureRect.height = 32;
	m_sprite.setTextureRect(m_textureRect);
	m_open = false;
	m_collisionProfile = nullptr;
}
	
void Door::setFogmap(Fogmap* fogmap)
{
	m_fogmap = fogmap;
}

void Door::setConnectedRoom(Room* room)
{
	m_room = room;
}
	
void Door::render(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_x, m_y);
	window.draw(m_sprite);
}

void Door::checkForCollision(Player& player)
{
	int x = player.getX();
	int y = player.getY();
	
	sf::IntRect AABBPlayer(x+8,y+20,16,8);
	sf::IntRect AABBDoor(m_x,m_y,32,32);
	
	if( !m_open && AABBPlayer.intersects(AABBDoor) )
	{
		m_textureRect.left = 0;
		m_sprite.setTextureRect(m_textureRect);
		m_room->showRoom(*m_fogmap);
		m_open = true;
	}
}