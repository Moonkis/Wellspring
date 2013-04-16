#include "Room.hpp"
#include <Vildhjarta\Random.hpp>
#include <iostream>
#include "Level.hpp"
#include <stdlib.h>

Room::Room(unsigned int x, unsigned int y, unsigned int width, unsigned int height, Room* connectedRoom)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	
	
	/* Add directions. */
	m_possibleDirections.reserve(4);
	m_possibleDirections.push_back(Direction::UPP);
	m_possibleDirections.push_back(Direction::DOWN);
	m_possibleDirections.push_back(Direction::LEFT);
	m_possibleDirections.push_back(Direction::RIGHT);
	
	m_connectedRoom = connectedRoom;
	
}

unsigned int Room::possibleDirections()
{
	return m_possibleDirections.size();
}

Direction Room::getPossibleDirection()
{
	if( m_possibleDirections.size() == 1)
		return m_possibleDirections[0];
	else
	{
	int index = rand() % (m_possibleDirections.size()-1);
	return m_possibleDirections[index];
	}
}

void Room::removeDirection(Direction direction)
{
	std::vector<Direction>::iterator it;
	it = m_possibleDirections.begin();
	for(; it != m_possibleDirections.end(); ++it )
	{
		if( (*it) == direction )
		{
			m_possibleDirections.erase(it);
			--it;
			break;
		}
	}
}

int walltype()
{
	int id = 2;
	int chance = 1 + rand() % 100;
	if( chance <= 15 )
	{
		id = 3;
	}
		
	return id;
}

void Room::fill(Tiles& tiles)
{
	/* Make room */
	for(unsigned int y = m_y; y < m_y+m_height; y++ )
	{
		for( unsigned int x = m_x; x < m_x+m_width; x++ )
		{
			/* Floor */
			tiles[x][y] = 1;
			
			/* Top and Bottom Wall */
			tiles[x][m_y] = walltype();
			tiles[x][m_y+m_height-1] = walltype();

			/* Left and Right Wall */
			tiles[m_x][y] = walltype();
			tiles[m_x+m_width-1][y] = walltype();
		}
	}
}

void Room::remove(Tiles& tiles)
{
	
}

bool Room::validPlacement(Tiles& tiles,  unsigned int width, unsigned int height)
{
	for(unsigned int y = m_y; y < m_y+m_height; y++ )
	{
		for( unsigned int x = m_x; x < m_x+m_width; x++ )
		{
			/* Floor */
			if( x < 0 || x >= width-1 )
				return false;
			if( y < 0 || y > height-1 )
				return false;
			
			if( tiles[x][y] > 0 && tiles[x][y] < 2 )
				return false;
		}
	}
	return true;
}

void Room::showRoom(FogMap& fogmap)
{
	for( unsigned int y = m_y; y < m_y+m_height; y++ )
	{
		for( unsigned int x = m_x; x < m_x+m_width; x++ )
		{
			fogmap[x][y] = false;
		}
	}
}
	
unsigned int Room::getX()
{
	return m_x;
}

unsigned int Room::getY()
{
	return m_y;
}

unsigned int Room::getWidth()
{
	return m_width;
}

unsigned int Room::getHeight()
{
	return m_height;
}