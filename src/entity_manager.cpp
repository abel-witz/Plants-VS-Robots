#include "entity.hpp"
#include <string>
#include "entity_manager.hpp"
#include <algorithm>

bool isMarkedForDeletion(Entity* entity) {
    return entity == nullptr || !entity->isActive();
}

void EntityManager::update() {
    for (Entity* e : m_entities) {
        if (e != nullptr && !e->isActive()) {
            delete e;
        }
    }
    
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), isMarkedForDeletion), m_entities.end());
    for (auto& pair : m_entityMap) {
        pair.second.erase(std::remove_if(pair.second.begin(), pair.second.end(), isMarkedForDeletion), pair.second.end());
    }

    for (Entity* e : m_toAdd) {
        m_entities.push_back(e);
        m_entityMap[e->getTag()].push_back(e);
    }
    m_toAdd.clear();
}

Entity* EntityManager::create(const std::string& tag) {
    Entity* newEntity = new Entity(tag);
    newEntity->m_id = m_totalEntities++;
    m_toAdd.push_back(newEntity);
    return newEntity;
}

const EntityVector& EntityManager::getEntities() const {
    return m_entities;
}

const EntityVector& EntityManager::getEntities(const std::string& tag) const {
    return m_entityMap.at(tag);
}

EntityManager::~EntityManager() {
    for (Entity* e : m_entities) {
        delete e;
    }
}