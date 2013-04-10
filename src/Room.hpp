#ifndef _WELLSPRING_ROOM_HPP
#define _WELLSPRING_ROOM_HPP

#include <vector>

typedef std::vector< std::vector<unsigned int> > Tiles;

typedef enum Direction
{
	UPP,
	DOWN,
	LEFT,
	RIGHT
};


class Room
{
public:
	Room(unsigned int x, unsigned int y, unsigned int m_width, unsigned int m_height, unsigned int doorBX, unsigned int doorBY, Room* connectedRoom);
	void fill(Tiles& tiles);
	void remove(Tiles& tiles);
	bool validPlacement(Tiles& tiles, unsigned int width, unsigned int height);
	
	unsigned int getX();
	unsigned int getY();
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getDoorBX() { return m_doorBX; }
	unsigned int getDoorBY() { return m_doorBY; }
	
	unsigned int possibleDirections();
	Direction getPossibleDirection();
	
	void removeDirection(Direction direction);
	Room* getConnected() { return m_connectedRoom; }
private:
	unsigned int m_x, m_y;
	unsigned int m_doorAX, m_doorAY, m_doorBX, m_doorBY;
	unsigned int m_width, m_height;
	std::vector<Direction> m_possibleDirections;
	Room* m_connectedRoom;
};


#endif