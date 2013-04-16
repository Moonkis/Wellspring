#ifndef _WELLSPRING_DOOR_HPP
#define _WELLSPRING_DOOR_HPP

#include <SFML\Graphics.hpp>
#include <Vildhjarta/Context.hpp>
#include <vector>
#include "Entity.hpp"

typedef std::vector< std::vector<bool> > Fogmap;

class Room;
class Player;

class Door : public Entity
{
public:
	Door(vh::Context& context);
	void render(sf::RenderWindow& window);
	void update(float dt, float time, Tilemap& tilemap) {};
	void checkForCollision(Player& player);
	
	
	void setFogmap(Fogmap* fogmap);
	void setConnectedRoom(Room* room);
	
	
	static Entity* createDoor(vh::Context& context) { return new Door(context); }
private:
	bool m_open;
	Room* m_room;
	Fogmap* m_fogmap;
	sf::IntRect m_textureRect;
};


#endif