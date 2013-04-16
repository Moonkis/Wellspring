#ifndef WELLSPRING_PLAYERCOLLISIONPROFILE_HPP
#define WELLSPRING_PLAYERCOLLISIONPROFILE_HPP

#include "ICollisionProfile.hpp"

class Player;

class PlayerCollisionProfile : public ICollisionProfile
{
public:
		PlayerCollisionProfile(Player* player);
		
		bool checkForCollision(Entity* entity);
		bool checkForCollision(Tilemap& tilemap);
		bool handleCollision(Entity* entity);
		bool handleCollision(Tilemap& tilemap);
private:
		Player* m_player;
};


#endif