#ifndef _WELLSPRING_GRAPHICS_HPP
#define _WELLSPRING_GRAPHICS_HPP

#include <VILDHJARTA\ResourceCache.hpp>
#include <SFML\Graphics.hpp>
#include <string>

class Graphics
{
public:
	sf::Texture* getTexture(std::string gfx);
	void removeTexture(std::string gfx);
	void loadTexture(std::string gfx);
private:
	vh::ResourceCache<sf::Texture> m_cache;
};


#endif