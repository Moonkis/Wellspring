#include "Room.hpp"
#include <Vildhjarta\Random.hpp>
#include <iostream>

#include <stdlib.h>

Room::Room(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int doorBX, unsigned int doorBY, Room* connectedRoom)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_doorBX = doorBX;
	m_doorBY = doorBY;
	
	
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

void Room::fill(Tiles& tiles)
{
	/* Make room */
	for(int y = m_y; y < m_y+m_height; y++ )
	{
		for( int x = m_x; x < m_x+m_width; x++ )
		{
			/* Floor */
			tiles[x][y] = 1;
			
			/* Top and Bottom Wall */
			tiles[x][m_y] = 2;
			tiles[x][m_y+m_height-1] = 2;
			
			/* Left and Right Wall */
			tiles[m_x][y] = 2;
			tiles[m_x+m_width-1][y] = 2;
		}
	}
}

void Room::remove(Tiles& tiles)
{
	
}

bool Room::validPlacement(Tiles& tiles,  unsigned int width, unsigned int height)
{
	for(int y = m_y; y < m_y+m_height; y++ )
	{
		for( int x = m_x; x < m_x+m_width; x++ )
		{
			/* Floor */
			if( x < 0 || x >= width )
				return false;
			if( y < 0 || y > height )
				return false;
			
			if( tiles[x][y] > 0 )
				return false;
		}
	}
	return true;
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