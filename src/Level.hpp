#ifndef _WELLSPRING_LEVEL_HPP
#define _WELLSPRING_LEVEL_HPP

#include <SFML\Graphics.hpp>
#include "Room.hpp"
#include <vector> 

class Door;
class Player;
class Stairway;
class GameState;

typedef std::vector< std::vector<unsigned int> > Tilemap;
typedef std::vector< std::vector<bool> > Fogmap;

class Level
{
public:
	Level(unsigned int width, unsigned int height, sf::Texture* tileset);
	~Level();
	
	
	void render(sf::RenderWindow& window);
	
	
	unsigned int getHeight() const;
	unsigned int getWidth() const;
	Tilemap& getTiles() { return tiles; }
	void generate(GameState* state);
	void changeLevel(Player& player, GameState* state);
	
	Room* getStarterRoom() { return rooms[0]; }
	Fogmap& getFogmap() { return m_fogmap; }
private:
	Tilemap tiles;
	Fogmap m_fogmap;
	
	void fillAreaWithFog(Room* room);
	
	unsigned m_width, m_height;
	
	std::vector<Room*> rooms;
	
	sf::Texture* m_tileset;
};

#endif
