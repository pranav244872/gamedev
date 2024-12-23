### **Engine Architecture Progression**

This progression outlines a basic framework for a game engine, including the relationships and responsibilities of its core components. The structure ensures modularity and scalability, focusing on Entities, Components, and Systems.

---

### **Game**

The `Game` class represents the top-level object controlling the entire game. It manages game data, entities, systems, and the main game loop.

#### **Responsibilities:**
- **Data Management**:
  - Stores all game data and manages entities via `EntityManager`.
- **System Integration**:
  - Executes systems for movement, rendering, user input, etc.
- **Gameplay Logic**:
  - Handles user interactions, game updates, and state transitions (e.g., pause, resume, exit).
- **Initialization**:
  - Can initialize and load configurations from a file.
- **Restrictions**:
  - Only displays one scene at a time.
  - Does not manage textures, sounds, animations, or user interfaces (e.g., menus).

#### **Attributes:**
- **`m_window`**: A `sf::RenderWindow` for rendering.
- **`m_entities`**: Manages entities via `EntityManager`.
- **`m_player`**: A specific player-controlled entity.
- **`m_paused`**: Boolean indicating if the game is paused.
- **`m_running`**: Boolean indicating if the game loop is active.

#### **Functions:**
- **`init(): void`**: Initializes the game.
- **`update(): void`**: Updates the game and calls relevant systems.

---

### **Systems**

Systems are the logic handlers that operate on entities and their components.

#### **Implemented Systems:**
1. **`sMovement(): void`**
   - Updates entity positions based on their `CTransform` components.
2. **`sUserInput(): void`**
   - Handles user input to update entities or game state.
3. **`sRender(): void`**
   - Renders all visible entities using their `CShape` components.
4. **`sEnemySpawner(): void`**
   - Spawns new enemy entities periodically.
5. **`sCollision(): void`**
   - Detects and handles collisions between entities.

---

### **EntityManager**

The `EntityManager` is responsible for creating, storing, and managing the lifecycle of all entities.

#### **Responsibilities:**
- **Entity Creation**:
  - Acts as a factory for creating entities.
  - Uses delayed addition to avoid iterator invalidation issues.
- **Entity Organization**:
  - Maintains a vector of all entities (`m_entities`).
  - Maintains a map of tags to entities (`m_entityMap`) for efficient retrieval.
- **Lifecycle Management**:
  - Updates entity states and removes inactive entities.

#### **Attributes:**
- **`m_entities`**: A vector storing all entities.
- **`m_entityMap`**: A map for grouping entities by tag (e.g., "Player", "Enemy").
- **`m_toAdd`**: A vector for entities waiting to be added.
- **`m_totalEntities`**: Counter for assigning unique IDs to entities.

#### **Functions:**
- **`init(): void`**: Initializes the manager.
- **`update(): void`**: Processes additions and removes inactive entities.
- **`addEntity(args): std::shared_ptr<Entity>`**: Creates and queues a new entity.
- **`getEntities(): std::vector<std::shared_ptr<Entity>>&`**: Retrieves all entities.
- **`getEntities(tag): std::vector<std::shared_ptr<Entity>>&`**: Retrieves entities by tag.

---

### **Entity**

The `Entity` class represents a game object. It contains a unique ID, tag, active state, and pointers to its components.

#### **Attributes:**
- **`m_tag`**: A string categorizing the entity (e.g., "Player", "Enemy").
- **`m_active`**: Boolean indicating whether the entity is active.
- **`m_id`**: A unique identifier for the entity.

#### **Component Pointers** (Stored as `std::shared_ptr`):
- **`cTransform`**: Transform data (position, speed, scale, angle).
- **`cShape`**: Shape data for rendering.
- **`cCollision`**: Collision data (e.g., radius).
- **`cInput`**: Input handling data.
- **`cScore`**: Score tracking.
- **`cLifespan`**: Lifespan management.

#### **Functions:**
- **`destroy(): void`**: Marks the entity as inactive (`m_active = false`).
- **`isActive(): bool`**: Returns whether the entity is active.
- **`tag(): const std::string&`**: Returns the entity's tag.
- **`id(): size_t`**: Returns the entity's unique ID.

---

### **Vec2**

The `Vec2` class represents a 2D vector used for positions, velocities, and other vector-related computations.

#### **Attributes:**
- **`x`**: The x-coordinate.
- **`y`**: The y-coordinate.

#### **Operators**:
- **`==, !=`**: Equality and inequality checks.
- **`+, -, *, /`**: Vector arithmetic.

#### **Functions**:
- **`normalize(): void`**: Normalizes the vector to unit length.
- **`length(): double`**: Returns the magnitude of the vector.

---

### **Components**

Components store pure data and provide features for entities. Each component is its own class and implements an intuitive entity feature.

#### **Examples:**
1. **`CTransform`**:
   - **Attributes**:
     - `pos`: Position as a `Vec2`.
     - `speed`: Speed as a `Vec2`.
     - `scale`: Scale as a `Vec2`.
     - `angle`: Rotation angle.

2. **`CCollision`**:
   - **Attributes**:
     - `radius`: Radius for collision detection.

3. **`CScore`**:
   - **Attributes**:
     - `score`: Integer score value.

4. **`CInput`**:
   - Handles user input for the entity.

5. **`CLifespan`**:
   - Tracks how long an entity should remain active.

---

### **UML Diagram Summary**

Below is a textual representation of the architecture:

```
Game
+ m_window: sf::RenderWindow
+ m_entities: EntityManager
+ m_player: Entity
+ m_paused: bool
+ m_running: bool
+ init(): void
+ update(): void
+ Systems: sMovement, sUserInput, sRender, sEnemySpawner, sCollision

EntityManager
+ m_entities: Vector<Entity>
+ m_entityMap: Map<string, Vector<Entity>>
+ m_toAdd: Vector<Entity>
+ init(): void
+ update(): void
+ addEntity(tag): sp<Entity>
+ getEntities(): Vector<sp<Entity>>&
+ getEntities(tag): Vector<sp<Entity>>&

Entity
+ m_tag: string
+ m_active: bool
+ m_id: size_t
+ Components: cTransform, cShape, cCollision, cInput, cScore, cLifespan
+ destroy(): void
+ isActive(): bool
+ tag(): string&
+ id(): size_t

Vec2
+ x: double
+ y: double
+ Operators: ==, !=, +, -, *, /
+ normalize(): void
+ length(): double

Components
- CTransform: pos, speed, scale, angle
- CCollision: radius
- CScore: score
```

This structured approach ensures clarity in managing entities, their components, and the game systems that operate on them.
