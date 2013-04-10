#ifndef _WELLSPRING_LEVEL_HPP
#define _WELLSPRING_LEVEL_HPP

#include <vector> 
typedef std::vector< std::vector<unsigned int> > Tiles;


class Level
{
public:
	Level(unsigned int width, unsigned int height);
	~Level();
	
	unsigned int getHeight() const;
	unsigned int getWidth() const;
	void generate();
private:
	Tiles tiles;
	unsigned m_width, m_height;
};

#endif
