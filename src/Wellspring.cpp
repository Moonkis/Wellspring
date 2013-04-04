#include "Wellspring.hpp"
#include <Vildhjarta\State.hpp>
#include <Vildhjarta\Audio.hpp>
#include <Vildhjarta\Graphics.hpp>
#include "SplashState.hpp"

bool Wellspring::initialize()
{
	// Create a new SFML window
	m_wind.create(sf::VideoMode(600,400,32), "@Wellspring", sf::Style::Titlebar);
	
	// Create Audio and Graphics Handlers
	m_context.audio = new vh::Audio();
	m_context.graphics = new vh::Graphics();
	
	// Create and Add SplashStates
	m_states.push( new SplashState(3,5,"victorsplash.png", m_context) );
	m_states.push( new SplashState(3,5,"ogamsplash.png", m_context) );
	
	return true;
}
void Wellspring::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if( !m_states.empty() )
	{
		vh::State* state = m_states.top();
		state->handleEvent(event, window);
		
		if( state->finished() )
		{
			m_states.pop();
			vh::State* next = state->next();
			if(next != nullptr)
			{
				m_states.push(next);
			}
				
			if( state->remove() )
			{
				delete state;
			}
		}
			

	}
	
	if( event.key.code == sf::Keyboard::Escape )
		m_wind.close();
}

void Wellspring::update(float dt, float time, vh::Context& context)
{
	if( !m_states.empty() )
	{
		vh::State* state = m_states.top();
		state->update(dt, time, context);
		
		if( state->finished() )
		{
			m_states.pop();
			vh::State* next = state->next();
			if(next != nullptr)
			{
				m_states.push(next);
			}
				
			if( state->remove() )
			{
				delete state;
			}
		}
	}
}
void Wellspring::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	
	if(!m_states.empty())
	{
		vh::State* state = m_states.top();
		state->render(window);
	}
	window.display();
}
Wellspring::~Wellspring()
{
	delete m_context.audio;
	delete m_context.graphics;
	
	while( !m_states.empty() )
	{
		delete m_states.top();
		m_states.pop();
	}
}
