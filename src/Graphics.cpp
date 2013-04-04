#include "Graphics.hpp"

sf::Texture* Graphics::getTexture(std::string gfx)
{
	sf::Texture* texture = m_cache.get(gfx);
	if( texture == nullptr )
	{
		texture = new sf::Texture();
		if( !texture->loadFromFile(gfx) )
		{
			delete texture;
			return nullptr;
		}
		m_cache.add(gfx, texture);
	}
	return texture;
}

void Graphics::loadTexture(std::string gfx)
{
	if( m_cache.contains(gfx) )
		return;
		
	sf::Texture* texture = new sf::Texture();
	if( !texture->loadFromFile(gfx) )
	{
		delete texture;
		return;
	}
	m_cache.add(gfx, texture);
}

void Graphics::removeTexture(std::string gfx)
{
	m_cache.remove(gfx);
}