### Entity Management and Separation of Logic and Data in Game Development

Managing entities efficiently is a cornerstone of game programming. An **entity** represents a game object with specific properties and behaviors. Separating **logic** (how things behave) from **data** (what things are) ensures clean, maintainable, and scalable code. This document explains the design and implementation of an **Entity Manager**, which handles the lifecycle of game entities using the Factory design pattern.

---

### **Entity Class Overview**

The `Entity` class encapsulates data and functionality for game objects. It stores the components associated with an entity, such as position, name, shape, and bounding box. Here's the design:

#### **Entity Class Members:**
- **Unique Identifier (`m_id`)**:
  - Each entity has a unique identifier to distinguish it from others.
- **Tag (`m_tag`)**:
  - A string that categorizes the entity (e.g., "Player", "Enemy", "Bullet").
- **Alive Status (`m_alive`)**:
  - A boolean indicating whether the entity is active or marked for destruction.

#### **Components:**
- **`cTransform`**: Transform component (position, scale, rotation).
- **`cName`**: Name component for debugging or categorization.
- **`cShape`**: Shape component for rendering.
- **`cBBox`**: Bounding box for collision detection.

#### **Entity Constructor:**
The constructor initializes the tag and ID. Components can be added later using shared pointers:
```cpp
Entity(const std::string& tag, size_t id);
```

#### **Entity Methods:**
- **`destroy()`**: Marks the entity as inactive (`m_alive = false`).
- **`tag()`**: Returns the tag of the entity.

---

### **Separation of Logic and Data**

A key principle in programming is to separate the management of data from the logic that operates on it. By encapsulating data in structures (like the `Entity` class) and using managers (like the `EntityManager`), you:
1. Prevent logic from being tightly coupled with data representation.
2. Make changes to data structures without affecting logic code.
3. Simplify complex algorithms by abstracting low-level details (e.g., whether to use a vector, map, or set).

---

### **Entity Manager Overview**

The `EntityManager` is responsible for creating, storing, retrieving, and managing the lifecycle of all entities. It uses the **Factory design pattern**, ensuring all entities are created and managed in a consistent and controlled manner.

---

### **Features of EntityManager**

#### 1. **Centralized Creation and Management**
- All entities are created via the `EntityManager` using the `addEntity()` method.
- This prevents users from creating entities manually, ensuring centralized control.

#### 2. **Storage**
- Entities are stored in a **vector** for efficient iteration:
  ```cpp
  typedef std::vector<std::shared_ptr<Entity>> EntityVec;
  EntityVec m_entities;
  ```
- Entities are also grouped by their tags for quick access:
  ```cpp
  typedef std::map<std::string, EntityVec> EntityMap;
  EntityMap m_entityMap;
  ```

#### 3. **Efficient Retrieval**
- Methods to get all entities:
  ```cpp
  EntityVec& getEntities();
  ```
- Methods to get entities by tag:
  ```cpp
  EntityVec& getEntities(const std::string& tag);
  ```

#### 4. **Iterator Invalidation Prevention**
Iterator invalidation occurs when modifying a collection during iteration. For example:
```cpp
for (auto& entity : entities) {
    if (entity->isDead()) {
        entities.erase(entity); // Invalidates iterators
    }
}
```
- The `EntityManager` avoids this by **delaying modifications** (like adding or removing entities) until it is safe to do so, typically at the start of the next frame.

---

### **EntityManager Implementation**

#### **Data Members**
```cpp
class EntityManager {
    EntityVec m_entities;        // Stores all entities
    EntityVec m_toAdd;           // Entities to be added next frame
    EntityMap m_entityMap;       // Map of tags to entities
    size_t m_totalEntities = 0;  // Counter for unique entity IDs
};
```

#### **Adding Entities**
Entities are added via the `addEntity` method. They are initially stored in `m_toAdd` and moved to the main list during the next frame:
```cpp
std::shared_ptr<Entity> addEntity(const std::string& tag) {
    auto e = std::make_shared<Entity>(tag, m_totalEntities++);
    m_toAdd.push_back(e);
    return e;
}
```

#### **Updating Entities**
The `update()` method handles:
1. Adding entities from `m_toAdd` to the main list and tag map.
2. Removing inactive entities.
```cpp
void EntityManager::update() {
    // Add new entities
    for (auto e : m_toAdd) {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear();

    // Remove dead entities
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
        [](auto& e) { return !e->isAlive(); }), m_entities.end());
    
    for (auto& [tag, vec] : m_entityMap) {
        vec.erase(std::remove_if(vec.begin(), vec.end(),
            [](auto& e) { return !e->isAlive(); }), vec.end());
    }
}
```

---

### **EntityManager Usage**

#### **Spawning Entities**
Entities are created through the `EntityManager`. Example:
```cpp
void spawnEnemy() {
    auto enemy = m_entities.addEntity("enemy");
    enemy->cTransform = std::make_shared<CTransform>(...);
    enemy->cShape = std::make_shared<CShape>(...);
}
```

#### **Processing Entities**
Example of collision detection between bullets and enemies:
```cpp
void handleCollisions() {
    for (auto& bullet : m_entities.getEntities("bullet")) {
        for (auto& enemy : m_entities.getEntities("enemy")) {
            if (Physics::CheckCollision(bullet, enemy)) {
                bullet->destroy();
                enemy->destroy();
            }
        }
    }
}
```

---

### **Private Constructor for Entities**

To enforce safe creation of entities, the constructor of `Entity` can be made private, with `EntityManager` declared as a friend class:
```cpp
class Entity {
    friend class EntityManager;

private:
    Entity(const std::string& tag, size_t id) : m_tag(tag), m_id(id) {}
};
```
Instead of using `std::make_shared<Entity>`, we create shared pointers using:
```cpp
std::shared_ptr<Entity>(new Entity(...));
```

---

### **Avoiding Common Pitfalls**

#### **Iterator Invalidation**
Modify collections only when it is safe (e.g., at the start of a frame). Use `std::remove_if` to filter out entities while iterating safely.

#### **Memory Usage vs. Speed**
Storing entities in multiple structures (e.g., vector and map) increases memory usage but significantly speeds up retrieval.

---

### **Game Loop Integration**
The `EntityManager` is updated at the start of each frame, ensuring entities are added and removed in a controlled manner:
```cpp
void GameEngine::mainLoop() {
    m_entityManager.update();  // Manage entities
    processInput();
    handleCollisions();
    renderFrame();
}
```

---

### **Conclusion**

The `EntityManager` provides a robust framework for managing game entities, ensuring separation of logic and data, efficient retrieval, and safe modifications. This design is scalable, flexible, and prevents common pitfalls like iterator invalidation, making it an essential tool for game development.
