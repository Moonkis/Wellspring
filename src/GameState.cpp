#include "GameState.hpp"
#include "EntityFactory.hpp"
#include <Vildhjarta\Context.hpp>
#include <iostream>
#include "Room.hpp"
#include "Door.hpp"
#include <vector>
#include "Stairway.hpp"

typedef std::vector< std::vector<bool> > Fogmap;

GameState::GameState(vh::Context& context, sf::RenderWindow* window)
: m_level(30, 30, context.graphics->getTexture("tileset.png")),
  m_window(window),
  m_hud(context)
{
	m_level.generate(this);
	Room* room = m_level.getStarterRoom();
	
	// Make a new player object.
	m_player = static_cast<Player*>(EntityFactory::get()->createEntity("player"));
	m_player->setX(32*5+room->getX()*32);
	m_player->setY(32*5+room->getY()*32);
	
	m_levelChange = false;
}

GameState::~GameState()
{
	m_player->disposeEntity();
}

void GameState::notifyLevelChange()
{
	m_levelChange = true;
}

void GameState::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	
}


void GameState::update( float dt, float time, vh::Context& context )
{
	//////////////////////////////////////
	// Level Changing and Handling      //
	//////////////////////////////////////
	if(m_levelChange)
	{
		m_level.changeLevel(*m_player, this);
		m_levelChange = false;
	}
	
	//////////////////////////////////////
	// Update Player and Handle Camera  //
	//////////////////////////////////////
	m_player->update( dt, time, m_level.getTiles() );
	sf::View v = m_window->getView();
	v.setCenter(m_player->getX()+16, m_player->getY()+16);
	m_window->setView(v);
	
	//////////////////////////////////////
	// Collision Detection and Handling //
	//////////////////////////////////////
	std::vector<Entity*>& doors = EntityFactory::get()->getEntityVector("door");
	std::vector<Entity*>& stairways = EntityFactory::get()->getEntityVector("stairway");
	
	ICollisionProfile* collisionProfile = m_player->getCollisionProfile();
	if(collisionProfile)
	{
		// Check player movement.
		collisionProfile->checkForCollision(m_level.getTiles());
		
		// Doors against Player
		for( int i = 0; i < doors.size(); i++ )
		{
			ICollisionProfile* doorCollisionProfile = doors[i]->getCollisionProfile();
			if(doorCollisionProfile)
			{
				if(doorCollisionProfile->checkForCollision(m_player))
				{
					doorCollisionProfile->handleCollision(m_player);
				}
			}
		}
		
		// Stairways against Player
		for( int i = 0; i < stairways.size(); i++ )
		{
			ICollisionProfile* stairwayCollisionProfile = stairways[i]->getCollisionProfile();
			if(stairwayCollisionProfile)
			{
				if(stairwayCollisionProfile->checkForCollision(m_player))
				{
					stairwayCollisionProfile->handleCollision(m_player);
				}
			}
		}
		
		
	}

	//////////////////////////////////////
	// Update HUD Position and Logic    //
	//////////////////////////////////////
	m_hud.update(dt, time, v.getCenter().x - (v.getSize().x / 2) ,  v.getCenter().y - (v.getSize().y / 2) );
}

void GameState::render(sf::RenderWindow& window)
{
	// Render Level
	m_level.render(window);
	
	// Get Fogmap
	Fogmap& fogmap = m_level.getFogmap();
	
	// Render Doors
	std::vector<Entity*>& doors = EntityFactory::get()->getEntityVector("door");
	for( unsigned int i = 0; i < doors.size(); i++ )
	{
		int x = doors[i]->getX()/32;
		int y = doors[i]->getY()/32;
		if(!fogmap[x][y])
			doors[i]->render(window);
	}
	
	// Render Stairways
	std::vector<Entity*>& stairways = EntityFactory::get()->getEntityVector("door");
	for( unsigned int i = 0; i < stairways.size(); i++ )
	{
		int x = stairways[i]->getX()/32;
		int y = stairways[i]->getY()/32;
		if(!fogmap[x][y])
			stairways[i]->render(window);
	}
	
	// Render Player
	m_player->render(window);
	
	// Render HUD
	m_hud.render(window, *m_player);
}