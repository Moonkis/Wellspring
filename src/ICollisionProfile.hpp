#ifndef WELLSPRING_ICOLLISIONPROFILE_HPP
#define WELLSPRING_ICOLLISIONPROFILE_HPP

class Entity;
#include <vector>
typedef std::vector< std::vector<unsigned int> > Tilemap;

class ICollisionProfile
{
public:
	virtual bool checkForCollision(Entity* entity)=0;
	virtual bool checkForCollision(Tilemap& tilemap)=0;
	virtual bool handleCollision(Entity* entity)=0;
	virtual bool handleCollision(Tilemap& tilemap)=0;
};

#endif