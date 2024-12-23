#include "Entity.h"

using EntityVec = std::vector<std::shared_ptr<Entity>>;

class EntityManager {
  EntityVec m_entities;
  EntityVec m_entitiesToAdd;
  std::map<std::string, EntityVec> m_entityMap;
  size_t m_totalEntities = 0;

  void removeDeadEntities(EntityVec &vec);

public:
  EntityManager() = default;
  void update();
  std::shared_ptr<Entity> addEntity(const std::string &tag);

  const EntityVec &getEntities() const;
  const EntityVec &getEntitiesByTag(const std::string &tag) const;
};
