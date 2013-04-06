#ifndef _WELLSPRING_STATE_HPP
#define _WELLSPRING_STATE_HPP

#include <VILDHJARTA\Context.hpp>
#include <SFML\Graphics.hpp>
class State
{
public:
	virtual void handleEvent(sf::Event& event, sf::RenderWindow& window){};
	virtual void update(float dt, float time, vh::Context& context){};
	virtual void render(sf::RenderWindow& window){};
	
	bool finished();
	bool remove();
	State* next();
	
	State()
	{
		m_next = nullptr;
		m_finished = false;
		m_remove = true;
	}
	
	virtual ~State() {};
protected:
	bool m_finished;
	bool m_remove;
	State* m_next;
};

#endif