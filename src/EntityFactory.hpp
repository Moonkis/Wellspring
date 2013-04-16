#ifndef WELLSPRING_ENTITYFACTORY_HPP
#define WELLSPRING_ENTITYFACTORY_HPP

#include <Vildhjarta/Context.hpp>

class Entity;

typedef Entity* (*CreateEntityFn)(vh::Context&);

#include <Vildhjarta/Context.hpp>
#include <string>
#include <vector>
#include <map>

class EntityFactory
{
public:
	Entity* createEntity(std::string id);
	Entity* getEntityById(std::string idString, unsigned int idNumber);
	
	void registerEntity(std::string id, CreateEntityFn fn);
	std::vector<Entity*>& getEntityVector(std::string id);
	
	static EntityFactory* get();
	
	void registerContext(vh::Context* context);
	void performGarbageCollect();
private:
	std::map< std::string, std::vector<Entity*> > m_entityVecotrs;
	std::map< std::string, CreateEntityFn > m_functionRegister;
	std::vector<Entity*> m_nullVector;
	vh::Context* m_context;
};



#endif