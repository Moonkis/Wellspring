#ifndef WELLSPRING_ENTITY_HPP
#define WELLSPRING_ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "ICollisionProfile.hpp"

enum EntityType
{
	PLAYER,
	DOOR,
	STAIRWAY,
	MONSTER,
	BULLET
};

typedef std::vector< std::vector<unsigned int> > Tilemap;


class Entity
{
public:
	virtual void render(sf::RenderWindow& window)=0;
	virtual void update(float dt, float time, Tilemap& tilemap)=0;
	
	ICollisionProfile* getCollisionProfile();
	
	unsigned int getId();
	
	float getX();
	float getY();
	
	void setX(float x);
	void setY(float y);
	
	EntityType getType();
	bool garbageCollect();
	void disposeEntity();
	
	Entity();
	virtual ~Entity();
protected:
	static unsigned int objectIdCount;
	unsigned int m_id;
	float m_x, m_y;
	sf::Sprite m_sprite;
	EntityType m_type;
	bool m_garbageCollect;
	ICollisionProfile* m_collisionProfile;
};


#endif