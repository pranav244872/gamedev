### **Game Engine Architecture**

#### **GameEngine**
- **Purpose**: Manages the overall game, including scenes, assets, and the main game loop.
- **Attributes**:
  - `scenes`: `map<string, Scene>`
  - `window`: `sf::RenderWindow`
  - `assets`: `Assets`
  - `currentScene`: `string`
  - `running`: `bool`
- **Functions**:
  - `init()`: Initialize the game engine.
  - `currentScene()`: Returns the current `Scene`.
  - `run()`: Main game loop.
  - `update()`: Updates the game state.
  - `quit()`: Quit the game.
  - `changeScene(scene)`: Switch to a different scene.
  - `getAssets()`: Access game assets.
  - `window()`: Access the game window.
  - `sUserInput()`: Handle user input.

---

#### **Scene (Abstract Base)**
- **Purpose**: Base class for all scenes. Provides common functionality like managing entities and actions.
- **Attributes**:
  - `game`: Pointer to `GameEngine`.
  - `entities`: `EntityManager`
  - `currentFrame`: `int`
  - `actionMap`: `map<int, string>`
  - `paused`: `bool`
  - `hasEnded`: `bool`
- **Functions**:
  - `update() = 0`: Abstract method for updating the scene.
  - `sDoAction(action) = 0`: Abstract method for handling actions.
  - `sRender() = 0`: Abstract method for rendering.
  - `simulate(int)`: Simulate the scene for a given number of updates.
  - `doAction(action)`: Perform a specific action.
  - `registerAction(action)`: Register a new action.

---

#### **Scene_Play (Derived from Scene)**
- **Purpose**: Represents the gameplay scene with specific systems like movement and collision handling.
- **Attributes**:
  - `levelPath`: `string`
  - `player`: Pointer to `Entity`
  - `playerConfig`: `PlayerConfig`
- **Systems**:
  - `sAnimation()`: Handle animations.
  - `sMovement()`: Handle movement logic.
  - `sEnemySpawner()`: Spawn enemies.
  - `sCollision()`: Handle collisions.
  - `sRender()`: Render the scene.
  - `sDoAction(action)`: Perform scene-specific actions.
  - `sDebug()`: Debugging system.

---

#### **Scene_Menu (Derived from Scene)**
- **Purpose**: Represents the menu scene.
- **Attributes**:
  - `menuStrings`: `vector<string>`
  - `menuText`: `sf::Text`
  - `menuIndex`: `int`
- **Systems**:
  - `sRender()`: Render the menu.
  - `sDoAction(action)`: Handle menu-specific actions.

---

#### **EntityManager**
- **Purpose**: Manages all entities within a scene.
- **Attributes**:
  - `entities`: `vector<Entity*>`
  - `entityMap`: `map<string, Entity*>`
  - `toAdd`: `vector<Entity*>`
- **Functions**:
  - `init()`: Initialize the entity manager.
  - `update()`: Update all entities.
  - `addEntity(args)`: Add a new entity.
  - `getEntities()`: Get all entities.
  - `getEntities(tag)`: Get entities by tag.

---

#### **Entity**
- **Purpose**: Represents an object in the game with associated components.
- **Attributes**:
  - `components`: `tuple<C1, C2, ...>`
  - `tag`: `string`
  - `active`: `bool`
  - `id`: `int`
- **Functions**:
  - `destroy()`: Destroy the entity.
  - `addComponent<C>()`: Add a component.
  - `hasComponent<C>()`: Check if a component exists.
  - `getComponent<C>()`: Get a specific component.
  - `removeComponent<C>()`: Remove a component.

---

#### **Assets**
- **Purpose**: Manages all game assets like textures, animations, sounds, and fonts.
- **Attributes**:
  - `textures`: `map<string, sf::Texture>`
  - `animations`: `map<string, Animation>`
  - `sounds`: `map<string, sf::Sound>`
  - `fonts`: `map<string, sf::Font>`
- **Functions**:
  - `addTexture(name, path)`: Add a texture.
  - `addAnimation(name, Animation)`: Add an animation.
  - `addSound(name, path)`: Add a sound.
  - `addFont(name, path)`: Add a font.
  - `getTexture(name)`: Retrieve a texture.
  - `getAnimation(name)`: Retrieve an animation.
  - `getSound(name)`: Retrieve a sound.
  - `getFont(name)`: Retrieve a font.

---

#### **Animation**
- **Purpose**: Handles animations for sprites.
- **Attributes**:
  - `sprite`: `sf::Sprite`
  - `frameCount`: `int`
  - `currentFrame`: `int`
  - `speed`: `int`
  - `size`: `Vec2`
  - `name`: `string`
- **Functions**:
  - `update()`: Update the animation.
  - `hasEnded()`: Check if the animation has ended.
  - `getName()`: Get the animation's name.
  - `getSize()`: Get the size of the animation.
  - `getSprite()`: Get the associated sprite.

---

#### **Vec2**
- **Purpose**: Represents a 2D vector.
- **Attributes**:
  - `x`: `double`
  - `y`: `double`
- **Functions**:
  - `operator==()`, `operator!=()`: Comparison operators.
  - `operator+()`, `operator-()`, `operator*()`, `operator/()`: Arithmetic operators.
  - `normalize()`: Normalize the vector.
  - `length()`: Get the vector's length.

---

#### **Action**
- **Purpose**: Represents an action that can be triggered in the game.
- **Attributes**:
  - `name`: `string`
  - `type`: `string`
- **Functions**:
  - `name()`: Get the action's name.
  - `type()`: Get the action's type.

---

#### **Physics**
- **Purpose**: Handles physics-related functionality like collisions.
- **Functions**:
  - `IsCollision(Entity, Entity)`: Check for a collision between entities.
  - `IsIntersect(Line, Line)`: Check if two lines intersect.
  - `IsInside(Vec2, Line)`: Check if a point is inside a line.

---

#### **Component Interface**
- **Purpose**: Base interface for all components.
- **Derived Components**:
  - `CTransform`: Manages position, velocity, scale, and angle.
  - `CBoundingBox`: Handles the size of an entity.

--- 

This structured architecture represents all the core components, systems, and their interactions in the game engine for Assignment 3.
