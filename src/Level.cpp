#include "Level.hpp"
#include "Room.hpp"
#include <Vildhjarta\Random.hpp>
#include <fstream>
#include <iostream>

#include <stdlib.h>

using namespace vh::util;

Level::Level(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
	
	tiles.resize( width, std::vector<unsigned int>(height, 0) );
}

Level::~Level()
{
	
}
unsigned int Level::getHeight() const
{
	return m_height;
}
	
unsigned int Level::getWidth() const
{
	return m_width;
}

void Level::generate()
{
	const unsigned int MAX_FEATURES = 1000;
	
	unsigned int features = 1;
	
	std::vector<Room*> rooms;

	// Create the starting room.
	rooms.push_back(new Room((m_width/2)-10, (m_height/2)-10, 10, 10, -1, -1, nullptr));
	
	// Add it to the list of rooms.
	Room* currentRoom = rooms.back();
	
	// Generate the room.
	currentRoom->fill(tiles);
	
	// Create other rooms.
	while( features < MAX_FEATURES )
	{
		// Get a direction to generate a new room in.
		Direction direction = currentRoom->getPossibleDirection();

		// Setup variables to generate doors and rooms.
		int doorAX, doorAY, doorBX, doorBY, roomX, roomY, roomW, roomH;
		
		// Get Width and Height of the room.
		roomW = 3 + rand() % 16;
		roomH = 3 + rand() % 16;
		
		// Depending on direction, roomX and roomY is altered, as with Doors.
		switch((int)direction)
		{
			case 0:
				doorAX = (currentRoom->getX()+1) + rand() % (currentRoom->getWidth()-2);
				doorAY = currentRoom->getY();
				doorBX = doorAX;
				doorBY = doorAY - 1;
				
				roomX = doorAX - roomW/2;
				roomY = doorAY - roomH;
				// std::cout << direction << "=" << "UPP" << std::endl;
			break;
				
			case 1:
				doorAX = (currentRoom->getX()+1) + rand() % (currentRoom->getWidth()-2);
				doorAY = currentRoom->getY()+currentRoom->getHeight()-1;
				doorBX = doorAX;
				doorBY = doorAY + 1;
				
				roomX = doorAX - roomW/2;
				roomY = doorAY + 1;
				// std::cout << direction <<"=" << "DOWN" << std::endl;
			break;
				
			case 2:
				doorAX = currentRoom->getX();
				doorAY = (currentRoom->getY()+1) + rand() % (currentRoom->getHeight()-2);
				doorBX = doorAX - 1;
				doorBY = doorAY;
				
				roomX = doorAX - roomW;
				roomY = doorAY - roomH/2;
				// std::cout << direction <<"=" << "LEFT" << std::endl;
			break;
				
			case 3:
				doorAX = currentRoom->getX()+currentRoom->getWidth()-1;
				doorAY = (currentRoom->getY()+1) + rand() % (currentRoom->getHeight()-2);
				doorBX = doorAX + 1;
				doorBY = doorAY;
				
				roomX = doorAX + 1;
				roomY = doorAY - roomH/2;
				// std::cout << direction <<"=" << "RIGHT" << std::endl;
			break;
			
			default:
				std::cout << "Invalid direction" << std::endl;
			break;
		}
		
		// Adjust coordinates accordingly, else room placement will freak out.
		if( roomY < 0 ) roomY = 0;
		if( roomX < 0 ) roomX = 0;
		if( roomX >= m_width ) roomX = m_width - 1;
		if( roomY >= m_height ) roomX = m_height - 1;
		
		// Make the new room.
		Room* newRoom = new Room(roomX, roomY, roomW, roomH, doorBX, doorBY, currentRoom);
		
		// Check if it's valid placement.
		if(newRoom->validPlacement(tiles, m_width, m_height))
		{
			// Fill the tiles with the room.
			newRoom->fill(tiles);
			
			// Add the room to the vector.
			rooms.push_back(newRoom);
			
			// Remove the succeded Direction, because it's not available again.
			//currentRoom->removeDirection(direction);
			
			// Remove the opposite direction of current room.
			
			switch((int)direction)
			{
				case 0: newRoom->removeDirection(Direction::DOWN);  break;
				case 1: newRoom->removeDirection(Direction::UPP);   break;
				case 2: newRoom->removeDirection(Direction::RIGHT); break;
				case 3: newRoom->removeDirection(Direction::LEFT);  break;
			}
			
			// Set the current room to the new room.
			currentRoom = newRoom;
			
			// Alter the supposedly connected walls so a pathway is formed.
			tiles[doorAX][doorAY] = 1;
			tiles[doorBX][doorBY] = 1;
			
			// Increase the feature count.
			features++;
		}
		else
		{
			// Remove the room that failed.
			delete newRoom;
			
			// Remove the direction that failed
			currentRoom->removeDirection(direction);
			
			// If there are no more directions to go in the current room.
			if(currentRoom->possibleDirections() == 0)
			{
				// Move back one room and try to generate rooms in other directions
				Room* connectedRoom = currentRoom->getConnected();
				
				// If the connected room is start room then there is NO more to be done.
				if(connectedRoom == nullptr)
				{
					std::cout << "Every direction of starter room has been generated." << std::endl;
					break;
				}
				
				// Set the current room to the room before.
				currentRoom = connectedRoom;
			}
		}
		
	}
	
	// Write the level to a file.
	std::ofstream ofs;
	ofs.open("level.txt");
	
	for( int y = 0; y < m_height; y++ )
	{
		for( int x = 0; x < m_width; x++ )
		{
			if( tiles[x][y] == 0)
				ofs << " ";
			else if ( tiles[x][y] == 2 )
				ofs << "W";
			else
				ofs << "#";
		}
		ofs << "\n";
	}
	ofs.close();
	
	// Delete the rooms.
	for( int i = 0; i < rooms.size(); i++ )
		delete rooms[i];
		
	std::cout << features << " features generated" << std::endl;
}