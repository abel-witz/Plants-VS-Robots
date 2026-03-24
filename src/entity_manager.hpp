#pragma once

#include "entity.hpp"
#include <string>
#include <vector>
#include <map>

typedef std::vector<Entity*> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager {
private:
	size_t m_totalEntities = 0;
	EntityVector m_entities;
	EntityMap m_entityMap;
	EntityVector m_toAdd;

public:
	void update();
	Entity* create(const std::string& tag);
	const EntityVector& getEntities() const;
	const EntityVector& getEntities(const std::string& tag) const;
	~EntityManager();
};