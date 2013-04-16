#include "Level.hpp"
#include "Room.hpp"
#include "Door.hpp"
#include <stdlib.h>
#include <fstream>
#include "Stairway.hpp"
#include "Player.hpp"
#include "GameState.hpp"
#include "EntityFactory.hpp"

Level::Level(unsigned int width, unsigned int height, sf::Texture* tileset)
{
	m_width = width;
	m_height = height;
	m_tileset = tileset;
	tiles.resize( width, std::vector<unsigned int>(height, 0) );
	m_fogmap.resize( width, std::vector<bool>(height,false) );
}

Level::~Level()
{
	// Handling rooms, delete them.
	for( unsigned int i = 0; i < rooms.size(); i++ )
	{
		delete rooms[i];
	}
	
	// Tell the EntityFactory::garbageCollect() to collect them.
	std::vector<Entity*>& doors = EntityFactory::get()->getEntityVector("door");
	std::vector<Entity*>& stairways = EntityFactory::get()->getEntityVector("door");
	
	for( unsigned int i = 0; i < doors.size();     i++ ) doors[i]->disposeEntity();
	for( unsigned int i = 0; i < stairways.size(); i++ ) stairways[i]->disposeEntity();
}

unsigned int Level::getHeight() const
{
	return m_height;
}
	
unsigned int Level::getWidth() const
{
	return m_width;
}

void Level::generate(GameState* state)
{
	// Create the starting room.
	rooms.push_back(new Room((m_width/2)-10, (m_height/2)-10, 10, 10, nullptr));
	
	// Add it to the list of rooms.
	Room* currentRoom = rooms.back();

	// Generate the room.
	currentRoom->fill(tiles);
	
	// Create other rooms.
	while( true )
	{
		// Get a direction to generate a new room in.
		Direction direction = currentRoom->getPossibleDirection();

		// Setup variables to generate doors and rooms.
		int doorAX, doorAY, roomX, roomY, roomW, roomH;
		
		// Get Width and Height of the room.
		roomW = 5 + rand() % 10;
		roomH = 5 + rand() % 10;
		
		// Depending on direction, roomX and roomY is altered, as with Doors.
		switch((int)direction)
		{
			case 0:
				doorAX = (currentRoom->getX()+1) + rand() % (currentRoom->getWidth()-2);
				doorAY = currentRoom->getY();
				
				roomX = doorAX - roomW/2;
				roomY = doorAY - roomH + 1;
			break;
				
			case 1:
				doorAX = (currentRoom->getX()+1) + rand() % (currentRoom->getWidth()-2);
				doorAY = currentRoom->getY()+currentRoom->getHeight()-1;
				
				roomX = doorAX - roomW/2;
				roomY = doorAY;
			break;
				
			case 2:
				doorAX = currentRoom->getX();
				doorAY = (currentRoom->getY()+1) + rand() % (currentRoom->getHeight()-2);
				
				roomX = doorAX - roomW + 1;
				roomY = doorAY - roomH/2;
			break;
				
			case 3:
				doorAX = currentRoom->getX()+currentRoom->getWidth()-1;
				doorAY = (currentRoom->getY()+1) + rand() % (currentRoom->getHeight()-2);
				
				roomX = doorAX;
				roomY = doorAY - roomH/2;
			break;
			
			default:
			break;
		}
		
		// Adjust coordinates accordingly, else room placement will freak out.
		if( roomY < 0 ) roomY = 0;
		if( roomX < 0 ) roomX = 0;
		if( roomX >= static_cast<int>(m_width) ) roomX = m_width - 1;
		if( roomY >= static_cast<int>(m_height) ) roomX = m_height - 1;
		
		// Make the new room.
		Room* newRoom = new Room(roomX, roomY, roomW, roomH, currentRoom);
		
		// Check if it's valid placement.
		if(newRoom->validPlacement(tiles, m_width, m_height))
		{
			// Fill the tiles with the room.
			newRoom->fill(tiles);
			fillAreaWithFog(newRoom);
			
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
			Door* door = static_cast<Door*>( EntityFactory::get()->createEntity("door") );
			door->setX(doorAX*32);
			door->setY(doorAY*32);
			door->setConnectedRoom(currentRoom);
			door->setFogmap(&m_fogmap);
			
			tiles[doorAX][doorAY] = 1;
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
					break;
				}
				
				// Set the current room to the room before.
				currentRoom = connectedRoom;
			}
		}
		
	}
	rooms[0]->showRoom(m_fogmap);
	
	int stairIndex = rand() % rooms.size();
	float stx = rooms[stairIndex]->getX() + rooms[stairIndex]->getWidth() / 2;
	float sty = rooms[stairIndex]->getY() + rooms[stairIndex]->getHeight()/ 2;
	
	Stairway* stairway = static_cast<Stairway*>(EntityFactory::get()->createEntity("stairway"));
	stairway->setX(stx*32);
	stairway->setY(sty*32);
	stairway->setGameState(state);
	
	std::ofstream ofs;
	ofs.open("level.txt");
	
	for( unsigned int y = 0; y < m_height; y++ )
	{
		for( unsigned int x = 0; x < m_width; x++ )
		{
			if( tiles[x][y] == 0)
				ofs << " ";
			else if ( tiles[x][y] == 2 || tiles[x][y] == 3 || tiles[x][y] == 4 )
				ofs << "W";
			else if ( tiles[x][y] == 5 )
				ofs << "D";
			else
				ofs << "#";
		}
		ofs << "\n";
	}
	ofs.close();
}

void Level::changeLevel(Player& player, GameState* state)
{
	for( unsigned int i = 0; i < rooms.size(); i++ )
		delete rooms[i];
	rooms.clear();
	
	// Tell the EntityFactory::garbageCollect() to collect them.
	std::vector<Entity*>& doors = EntityFactory::get()->getEntityVector("door");
	std::vector<Entity*>& stairways = EntityFactory::get()->getEntityVector("door");
	
	for( unsigned int i = 0; i < doors.size();     i++ ) doors[i]->disposeEntity();
	for( unsigned int i = 0; i < stairways.size(); i++ ) stairways[i]->disposeEntity();
	
	tiles.clear();
	m_fogmap.clear();
	
	tiles.resize( m_width, std::vector<unsigned int>(m_height, 0) );
	m_fogmap.resize( m_width, std::vector<bool>(m_height,false) );
	
	generate(state);
	
	Room* room = getStarterRoom();
	
	player.setX(32*5+room->getX()*32);
	player.setY(32*5+room->getY()*32);
}

void Level::render(sf::RenderWindow& window)
{
	sf::Sprite tile;
	tile.setTexture(*m_tileset);
	
	int startX = ( window.getView().getCenter().x - (window.getView().getSize().x / 2) ) / 32;
	int startY = ( window.getView().getCenter().y - (window.getView().getSize().y / 2) ) / 32;
	int endX = startX + ( window.getView().getSize().x/32 ) + 2;
	int endY = startY + ( window.getView().getSize().y/32 ) + 2;
	
	
	if( startX < 0 ) startX = 0;
	if( startY < 0 ) startY = 0;
	if( startX > static_cast<int>(m_width) ) startX = m_width;
	if( startY > static_cast<int>(m_height) ) startY = m_height;
	if( endX < 0 ) endX = 0;
	if( endY < 0 ) endY = 0;
	if( endX > static_cast<int>(m_width) ) endX = m_width;
	if( endY > static_cast<int>(m_height) ) endY = m_height;
	
	for( int y = startY; y < endY; y++ )
	{
		for( int x = startX; x < endX; x++ )
		{
			if(!m_fogmap[x][y] && tiles[x][y] != 0)
			{
				int id = tiles[x][y];
				
				sf::IntRect subrect( id * 32, 0, 32, 32 );
				tile.setTextureRect(subrect);
				
				tile.setPosition(x * 32, y * 32);
				window.draw(tile);
			}
		}
	}
}

void Level::fillAreaWithFog(Room* room)
{
	int rx = room->getX();
	int ry = room->getY();
	int rw = room->getWidth();
	int rh = room->getHeight();
	
	for(int y = ry; y < ry+rh; y++ )
	{
		for( int x = rx; x < rx+rw; x++ )
		{
			m_fogmap[x][y] = true;
		}
	}
}
