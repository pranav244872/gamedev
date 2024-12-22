### Entity-Component-System (ECS) Framework

ECS is a design pattern widely used in game development for managing and organizing the data and behavior of game objects. It separates the data (components) from the behavior (systems), leading to modularity, flexibility, and better performance.

---

### Key Concepts in ECS

#### 1. **Component**
- **Definition**: 
  A component is **just data** that represents a specific attribute or property of an entity (e.g., position, health, shape).  
  - A component has no functionality except for basic initialization (e.g., in its constructor).  
  - Example components: `Position`, `Velocity`, `Health`.

- **Characteristics**:
  - Does not include helper functions or business logic.
  - Adds intuitive meaning to the entity that contains it.

- **Examples**:
  - `CTransform`: Contains position and velocity of an entity.
  - `CHealth`: Tracks health points.

- **Implementation in C++**:
  Components are typically implemented as lightweight classes.  
  Example:
  ```cpp
  class CTransform {
  public:
      Vec2 pos = {0, 0};
      Vec2 velocity = {0, 0};
      CTransform() {}
      CTransform(const Vec2 &p, const Vec2 &v) : pos(p), velocity(v) {}
  };
  ```

---

#### 2. **Entity**
- **Definition**: 
  An entity represents a unique game object. It is a container or identifier that holds a collection of components.

- **Characteristics**:
  - Contains no unique functionality of its own.
  - Stores at most one instance of each component type.

- **Storage Options**:
  1. **Component Variables**:
     Components are stored as member variables:
     ```cpp
     class Entity {
     public:
         std::shared_ptr<CTransform> cTransform;
         std::shared_ptr<CShape> cShape;
         Entity() {}
     };
     ```

  2. **Component Collection**:
     Components are stored in a generalized container, such as a `std::vector` or `std::tuple`:
     ```cpp
     class Entity {
         std::vector<std::shared_ptr<Component>> m_components;
     public:
         void addComponent<T>(args);
         void getComponent<T>(args);
     };
     ```

  - **Shared Pointers**:
    Using `std::shared_ptr` ensures safe memory management.

---

#### 3. **System**
- **Definition**: 
  A system contains the game logic and operates on entities that have the relevant components. 

- **Examples**:
  - **Movement System**: Updates positions based on velocity (`CTransform`).
  - **Rendering System**: Draws entities on the screen (`CTransform` + `CShape`).
  - **Collision System**: Detects and resolves collisions (`CBoundingBox`).

- **Characteristics**:
  - Each system operates independently on a subset of entities.
  - Requires entities to have specific components.

- **Implementation in C++**:
  Example of a movement system:
  ```cpp
  void sMovement(std::vector<Entity> &entities) {
      for (auto &e : entities) {
          if (e.cTransform) {
              e.cTransform->pos += e.cTransform->velocity;
          }
      }
  }
  ```

---

### ECS Workflow Example

1. **Declaring an Entity**:
   Create and initialize an entity with components.
   ```cpp
   int main() {
       std::vector<Entity> entities;
       Vec2 p(100, 200), v(10, 10);
       Entity e;
       e.cTransform = std::make_shared<CTransform>(p, v);
       e.cName = std::make_shared<CName>("Red Box");
       entities.push_back(e);
   }
   ```

2. **Using Entities**:
   Use systems to operate on entities.
   ```cpp
   void doStuff(std::vector<Entity> &entities) {
       for (auto &e : entities) {
           if (e.cTransform && e.cShape) {
               e.cTransform->pos += e.cTransform->velocity;
               e.cShape->shape.setPosition(e.cTransform->pos);
               window.draw(e.cShape->shape);
           }
       }
   }
   ```

3. **Filtering Entities**:
   Some systems only operate on entities that contain specific components.
   ```cpp
   void sRender(std::vector<Entity> &entities) {
       for (auto &e : entities) {
           if (e.cTransform && e.cShape) {
               e.cShape->shape.setPosition(e.cTransform->pos);
               window.draw(e.cShape->shape);
           }
       }
   }
   ```

---

### Advantages of ECS

1. **Modularity**:
   - Components and systems are independent, allowing easy addition of new features.

2. **Scalability**:
   - ECS can handle a large number of entities and components efficiently.

3. **Performance**:
   - Systems operate only on entities with relevant components, reducing overhead.
   - Contiguous storage of components (e.g., `std::vector`) optimizes memory usage.

4. **Flexibility**:
   - Adding new components or systems does not affect existing functionality.

---

### Example Systems

1. **Movement System**:
   Updates the position of entities based on their velocity.
   ```cpp
   void sMovement(std::vector<Entity> &entities) {
       for (auto &e : entities) {
           if (e.cTransform) {
               e.cTransform->pos += e.cTransform->velocity;
           }
       }
   }
   ```

2. **Collision System**:
   Checks for collisions and applies damage.
   ```cpp
   void sCollision(std::vector<Entity> &bullets, std::vector<Entity> &enemies) {
       for (auto &b : bullets) {
           for (auto &e : enemies) {
               if (Physics::IsCollision(b, e)) {
                   e.cHealth->value -= b.cDamage->value;
                   b.destroy();
               }
           }
       }
   }
   ```

3. **Rendering System**:
   Draws entities to the screen.
   ```cpp
   void sRender(std::vector<Entity> &entities, sf::RenderWindow &window) {
       for (auto &e : entities) {
           if (e.cTransform && e.cShape) {
               e.cShape->shape.setPosition(e.cTransform->pos);
               window.draw(e.cShape->shape);
           }
       }
   }
   ```

---

### Summary of ECS

- **Entity**: Represents game objects; contains no functionality but holds components.
- **Component**: Represents specific attributes or properties; contains only data.
- **System**: Operates on entities with specific components; contains game logic.

ECS allows for a clean, modular, and efficient structure for game development, ensuring maintainability and scalability of codebases.
