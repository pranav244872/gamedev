#pragma once
#include "Component.h"
#include <memory>
#include <string>
#undef string

class EntityManager;
class Entity {

  bool m_active = true;
  size_t m_id = 0;
  std::string m_tag = "default";

  // constructor and destructor
  Entity(const size_t id, const std::string &tag);

  // Friend class
  friend class EntityManager;

public:
  // component pointers
  std::shared_ptr<CTransform> cTransform;
  std::shared_ptr<CShape> cShape;
  std::shared_ptr<CCollision> cCollision;
  std::shared_ptr<CInput> cInput;
  std::shared_ptr<CScore> cScore;
  std::shared_ptr<CLifespan> cLifespan;

  // private member access functions
  bool isActive() const;
  const std::string &tag() const;
  size_t id() const;
  void destroy();
};
