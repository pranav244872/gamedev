Here’s a **comprehensive explanation** of the functionality and design concepts outlined, organized for clarity.

---

### **Overview of Design**

In this assignment, the game architecture is refactored to separate general game functionality from scene-specific functionality. The two primary classes introduced are:

1. **GameEngine**: Manages high-level, universal game functions and the overarching structure of the game.
2. **Scene**: A base class for all individual game scenes, allowing specific behavior to be implemented in derived classes.

This modular approach ensures better scalability, maintainability, and reusability of the code.

---

### **GameEngine Class**

#### **Purpose**
The `GameEngine` acts as the main controller of the game, managing:
1. Universal game resources (e.g., assets, rendering window).
2. The main game loop.
3. Scene transitions.

#### **Key Responsibilities**
1. **Top-Level Game Data**:
   - Stores shared resources like assets and the rendering window.
   - Maintains a map of all scenes (`scenes`) and a reference to the current scene (`currentScene`).

2. **Scene Management**:
   - Adds, removes, or switches between scenes dynamically using `changeScene`.
   - Mimics a finite-state machine (FSM) where each state corresponds to a game scene (e.g., Menu, Play).

3. **Main Game Loop**:
   - Handles the primary game cycle:
     - Process user input.
     - Update game logic and active scene.
     - Render the current scene.
   - Ensures seamless transitions between scenes while maintaining game state.

4. **Input Handling**:
   - Captures and processes player inputs.
   - Passes input events to the currently active scene for action-specific handling.

#### **Design Notes**
- The `GameEngine` pointer is passed to all `Scene` objects. This ensures scenes can access shared resources like:
  - The rendering window.
  - Game assets (textures, sounds, fonts).
  - Scene management functions (`changeScene`, etc.).

#### **Advantages**
- Centralized control ensures consistent behavior across scenes.
- Decouples high-level game management from scene-specific logic.

---

### **Scene Base Class**

#### **Purpose**
The `Scene` class is an abstract base class representing a generic game scene (e.g., Menu, Play). Derived classes (like `Scene_Play`) implement specific functionality.

#### **Key Responsibilities**
1. **Scene-Specific Data**:
   - Stores entities, input mappings, and frame counts relevant to the scene.
   - Maintains state flags (`paused`, `hasEnded`) to manage scene behavior.

2. **Scene Functionality**:
   - Defines core methods (`update`, `sRender`, `sDoAction`) that derived scenes must implement.
   - Includes systems for handling entities, animations, input, and rendering.

3. **Entity Management**:
   - Uses an `EntityManager` to store and manage all entities within the scene.
   - Updates entities and their components during each frame.

4. **Input Mapping**:
   - Maps user input (e.g., keyboard or controller events) to in-game actions.
   - Allows flexible input handling by associating keys with action strings (e.g., `W` -> "MoveUp").

#### **Special Methods**
1. **`simulate(frames)`**:
   - Advances the scene's state by simulating a specified number of frames.
   - Useful for testing or debugging without rendering.

2. **`doAction(action)`**:
   - Executes a specific action mapped to player input.
   - Calls `sDoAction` for scene-specific behavior.

3. **`registerAction(action)`**:
   - Associates a key or input event with an action.

#### **Design Notes**
- `Scene` is abstract and cannot be instantiated directly.
- Derived classes must implement the core methods to define their unique behavior.

#### **Advantages**
- Provides a common interface for all scenes, promoting consistency.
- Decouples shared scene functionality from specific implementations.

---

### **Scene_Play (Derived Scene)**

#### **Purpose**
`Scene_Play` is a concrete implementation of the `Scene` class for gameplay. It encapsulates all systems and logic specific to the play scene, such as player control, collision handling, and level management.

#### **Key Responsibilities**
1. **Gameplay Logic**:
   - Updates player and enemy behavior.
   - Spawns enemies dynamically during gameplay.

2. **Scene-Specific Systems**:
   - **Animation**: Manages sprite animations for entities.
   - **Movement**: Updates entity positions based on velocity.
   - **Collision**: Detects and resolves collisions between entities.
   - **Rendering**: Draws entities and level elements to the screen.
   - **Debugging**: Provides tools for visualizing entities, collision boxes, or other data.

3. **Level Management**:
   - Loads level data from external files.
   - Configures the scene with level-specific attributes, such as terrain and enemy spawn points.

4. **Player Management**:
   - Tracks the player's state (e.g., health, position).
   - Handles player-specific input and actions.

#### **Design Notes**
- `Scene_Play` demonstrates how each derived scene can define its own systems while leveraging shared functionality from the base `Scene`.

---

### **Scene Switching**

#### **Mechanism**
- The `GameEngine` maintains a map of scene names to shared pointers of `Scene` objects.
- The `currentScene` string is used to reference the active scene.
- The `changeScene` method:
  - Switches to a new or pre-existing scene.
  - Updates the `currentScene` pointer.

#### **FSM Analogy**
- Each scene represents a state in a finite-state machine.
- Transitions between states are triggered by events, such as user input or game logic.

#### **Example Workflow**
1. The game starts with a menu scene:
   - `game->changeScene("menu", sp<Scene_Menu>())`.
2. The player selects a level:
   - `Scene_Menu` triggers `game->changeScene("play", sp<Scene_Play>(levelPath))`.
3. The play scene is loaded, and gameplay begins.

---

### **Asset Management**

#### **Purpose**
The `Assets` class provides centralized management of game resources like textures, animations, sounds, and fonts. It ensures resources are loaded once and reused across scenes.

#### **Key Responsibilities**
1. **Resource Loading**:
   - Reads asset definitions from a configuration file.
   - Loads resources into memory during game initialization.

2. **Resource Access**:
   - Allows scenes to retrieve resources by name using getter methods.

#### **Design Notes**
- The `Assets` object is a member of the `GameEngine` class.
- Scenes access it via the `GameEngine` pointer.

#### **Advantages**
- Prevents redundant loading of assets.
- Simplifies resource management and ensures consistency.

#### **Use Cases**
1. **Textures**:
   - `m_assets->getTexture("MegaMan")` retrieves a preloaded texture.
2. **Animations**:
   - Combines multiple textures with timing data for smooth animations.
3. **Sounds**:
   - Loads sound effects (e.g., `death.wav`) for use in scenes.
4. **Fonts**:
   - Loads font files for rendering text in menus or gameplay.

---

### **Conclusion**

This refactored architecture separates game management and scene-specific functionality, enabling clean code organization and flexibility. The `GameEngine` handles universal concerns, while `Scene` and its derivatives focus on specific game behavior, making the system modular and maintainable. This design also lays the groundwork for future extensions, such as new scenes, assets, or gameplay mechanics.
