#include "SplashState.hpp"
#include <iostream>

SplashState::SplashState(float fadetime, float timeBeforeFade, std::string background, vh::Context& context)
: State()
{
	m_fadetime = fadetime;
	m_timeBeforeFade = timeBeforeFade;
	m_color = sf::Color::White;
	m_gfx = background;
	m_context = &context;
	sf::Texture* texture = context.graphics->getTexture(background);
	m_background.setTexture(*texture);
}

SplashState::~SplashState()
{
	m_context->graphics->removeTexture(m_gfx);
}

void SplashState::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if( event.key.code == sf::Keyboard::Return )
	{
		m_timeBeforeFade = 0;
	}
}

void SplashState::update(float dt, float time, vh::Context& context)
{
	m_timeBeforeFade -= dt;
	if(m_timeBeforeFade < 0 )
	{
		m_timeBeforeFade = 0;
		float alpha = m_color.a - ( 255 / m_fadetime ) * dt;
		if( alpha < 0 ) alpha = 0;
		std::cout << alpha << std::endl;
		if( alpha == 0 )
		{
			std::cout << "SPLASH DONE" << std::endl;
			m_finished = true;
			m_remove = true;
			return;
		}
		m_color.a = alpha;
	}
	m_background.setColor(m_color);
}

void SplashState::render(sf::RenderWindow& window)
{
	window.draw(m_background);
}