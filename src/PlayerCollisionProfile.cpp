#include "PlayerCollisionProfile.hpp"
#include "Player.hpp"

PlayerCollisionProfile::PlayerCollisionProfile(Player* player)
{
	m_player = player;
}

bool PlayerCollisionProfile::checkForCollision(Entity* entity) {}
bool PlayerCollisionProfile::checkForCollision(Tilemap& tilemap) {}
bool PlayerCollisionProfile::handleCollision(Entity* entity) {}
bool PlayerCollisionProfile::handleCollision(Tilemap& tilemap)
{
	
}