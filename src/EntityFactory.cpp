#include "EntityFactory.hpp"
#include "Entity.hpp"

Entity* EntityFactory::createEntity(std::string id)
{
	std::map< std::string, CreateEntityFn >::iterator it = m_functionRegister.find(id);
	if( it != m_functionRegister.end() )
	{
		Entity* entity = it->second(*m_context);
		m_entityVecotrs[id].push_back(entity);
		return entity;
	}
	return nullptr;
}

Entity* getEntityById(unsigned int id) { return nullptr; }

void EntityFactory::registerEntity(std::string id, CreateEntityFn fn)
{
	m_functionRegister[id] = fn;
}

std::vector<Entity*>& EntityFactory::getEntityVector(std::string id)
{
	std::map< std::string, std::vector<Entity*> >::iterator it = m_entityVecotrs.find(id);
	if( it != m_entityVecotrs.end() )
		return it->second;
	return m_nullVector;
}

EntityFactory* EntityFactory::get()
{
	static EntityFactory ef;
	return &ef;
}

void EntityFactory::registerContext(vh::Context* context)
{
	m_context = context;
}

void EntityFactory::performGarbageCollect()
{
	std::map< std::string, std::vector<Entity*> >::iterator it = m_entityVecotrs.begin();
	for(; it != m_entityVecotrs.end(); ++it )
	{
		std::vector<Entity*>& vector = it->second;
		for( int i = 0; i < vector.size(); i++ )
		{
			
			if( vector[i]->garbageCollect() )
			{
				delete vector[i];
				vector.erase(vector.begin()+i);
				i--;
			}
		}
	}
}