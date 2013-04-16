#include "Entity.hpp"


unsigned int Entity::objectIdCount = 0;

Entity::Entity()
{
	m_garbageCollect = false;
	m_id = Entity::objectIdCount++;
}

Entity::~Entity()
{
	
}

unsigned int Entity::getId() { return m_id; }

float Entity::getX() { return m_x; }
float Entity::getY() { return m_y; }

void Entity::setX(float x) { m_x = x; }
void Entity::setY(float y) { m_y = y; }

bool Entity::garbageCollect() { return m_garbageCollect; }

void Entity::disposeEntity()
{
	m_garbageCollect = true;
}

EntityType Entity::getType() { return m_type; }

ICollisionProfile* Entity::getCollisionProfile() { return m_collisionProfile; }


