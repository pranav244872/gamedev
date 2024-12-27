#include "EntityManager.h"

void EntityManager::update() {
  for (auto e : m_entitiesToAdd) {
    // - add them to the vector of all entities
    m_entities.push_back(e);
    // - add them to the vector inside the map, with the tage as a key
    m_entityMap[e->tag()].push_back(e);
  }
  // Clear the entities-to-add buffer to avoid duplication
  m_entitiesToAdd.clear();

  // remove dead enties from the vector of all entities
  removeDeadEntities(m_entities);

  // remove dead entities from the map of entities by tag
  // c++17 way of iterating through [key,value] pairs in a map
  for (auto &[tag, entityVec] : m_entityMap) {
    removeDeadEntities(entityVec);
  }
}

void EntityManager::removeDeadEntities(EntityVec &vec) {
  // remove all dead entities from the input vector
  // this is called by the update() function
  // Use erase-remove idiom to remove dead entities
  vec.erase(std::remove_if(vec.begin(), vec.end(),
                           [](const std::shared_ptr<Entity> &e) {
                             return !e->isActive();
                           }),
            vec.end());
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
  auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
  m_entitiesToAdd.push_back(entity);
  return entity;
}

const EntityVec &EntityManager::getEntities() const { return m_entities; }

const EntityVec &EntityManager::getEntitiesByTag(const std::string &tag) const {
  // Use `find()` to avoid modifying the map
  auto it = m_entityMap.find(tag);
  if (it != m_entityMap.end()) {
    return it->second; // Return the EntityVec corresponding to the tag
  }

  // If the tag does not exist, return an empty EntityVec
  static const EntityVec emptyVec; // Static empty vector for non-existent tags
  return emptyVec;
}
