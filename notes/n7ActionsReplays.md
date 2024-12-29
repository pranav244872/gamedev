### **Comprehensive and Detailed Notes: Game Input & Actions**

---

#### **Introduction to Game Input & Actions**
- **Games are interactive experiences** where players influence gameplay through various input devices.
- **Player Input**:
  - Players provide commands using devices like keyboards, mice, game controllers, VR controllers, etc.
  - These inputs directly influence game entities (e.g., moving characters, shooting).
- **Action**:
  - Represents the desired behavior or event triggered by the player.
  - Examples: "Jump", "Move Right", "Shoot".
- **Command**:
  - Another term for an action; focuses on the idea that the input represents a **command** for the game.

---

#### **Key Principles of Game Input Handling**
1. **Player Perspective**:
   - Players don’t care which button or key triggers an action as long as it’s intuitive and easy to use.
   - Example: In some games, "shoot" could be triggered by either a mouse button or a controller button.
2. **Engine Perspective**:
   - The game engine should **focus on the action logic** itself, not the specific input device or key that triggered it.
   - Decoupling the input from action logic provides flexibility for remapping keys, integrating alternate input methods, and adding new devices.

---

#### **Challenges with Traditional Input Handling**
- **Coupled Input and Logic**:
  - In basic game engines, actions are directly tied to specific key presses in the event loop.
  - Example: If `space` is hardcoded to trigger "jump," it's difficult to change or reassign that action later.
- **No Input Flexibility**:
  - The system can’t support:
    - Re-mapping controls (e.g., "jump" to a different key).
    - Alternate inputs (e.g., mouse, VR controllers, or network commands).
    - Replay functionality or input abstraction.
- **Solution**: **Decouple input handling from action execution**.

---

#### **Proposed Solution: Action-Based System**
1. **Core Idea**:
   - Abstract the input mechanism (e.g., key press) from the resulting action.
   - Use an **Action** class to represent desired behaviors or commands in the game.
   - Input handling is done centrally (in `GameEngine`), while scenes handle actions through a standardized `doAction()` function.
2. **Benefits**:
   - Flexibility to re-map keys or switch input devices.
   - Easy integration of replays, network-based inputs, or alternate controls.
   - Clean separation of concerns:
     - `GameEngine`: Handles input, creates actions, and passes them to scenes.
     - `Scene`: Executes actions without knowing their source.

---

#### **Action Class**
- **Purpose**: Encapsulates information about the action the player wants to perform.
- **Attributes**:
  - `m_name`: Name of the action (e.g., "jump", "move_left").
  - `m_type`: Type of action:
    - **START**: Triggered when the input begins (e.g., key press).
    - **END**: Triggered when the input ends (e.g., key release).
- **Structure**:
  ```cpp
  class Action {
      std::string m_name = "NONE";
      std::string m_type = "NONE";
  public:
      Action(); // Default constructor
      Action(const std::string &name, const std::string &type); // Initialize action
      const std::string &name() const; // Get action name
      const std::string &type() const; // Get action type
      std::string toString() const;    // Debug string representation
  };
  ```

---

#### **Understanding Action Start and End**
- **START**:
  - Triggered by a key/button press.
  - Represents the beginning of an action.
  - Example: `{"Right", "START"}` tells the game to start moving the player to the right.
- **END**:
  - Triggered by a key/button release.
  - Represents the end of an action.
  - Example: `{"Right", "END"}` tells the game to stop moving the player.

---

#### **Mapping Keys to Actions**
1. **Key Mapping**:
   - Assign specific input keys (keyboard, controller buttons, etc.) to action names.
   - Use a mapping (`std::map<int, std::string>`) to store this association:
     - Key: SFML key code (integer representing a key).
     - Value: Name of the action associated with the key.
2. **Per-Scene Action Map**:
   - Each Scene stores its own key-to-action map.
   - This allows different scenes to define unique input mappings and actions.
3. **Registering Actions**:
   - A function (`registerAction(int, std::string)`) is used to add key-to-action mappings.
   - Example in `Scene_Menu`:
     ```cpp
     void Scene_Menu::init() {
         registerAction(sf::Keyboard::W, "UP");
         registerAction(sf::Keyboard::S, "DOWN");
         registerAction(sf::Keyboard::D, "PLAY");
         registerAction(sf::Keyboard::Escape, "QUIT");
     }
     ```

---

#### **Input Handling in `GameEngine`**
1. **Detect Input Events**:
   - The SFML event loop detects player input (e.g., key press or release).
   - Example:
     ```cpp
     if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
         // Handle input
     }
     ```
2. **Check for Mapped Actions**:
   - Query the active Scene’s action map to check if the key has an associated action.
   - Skip unmapped keys:
     ```cpp
     if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) {
         continue;
     }
     ```
3. **Create Action Object**:
   - Determine the action **type** (`START` for key press, `END` for key release).
   - Create an `Action` object with the appropriate `name` and `type`.
   - Example:
     ```cpp
     const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
     currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
     ```

---

#### **Executing Actions in Scenes**
- **Scene Logic**:
  - The `doAction()` function in each Scene is responsible for handling the received `Action` object.
  - The Scene determines:
    - The action’s **name** (`action.name()`).
    - The action’s **type** (`action.type()`).
- **Example**: Handling menu actions in `Scene_Menu`:
  ```cpp
  void Scene_Menu::sDoAction(const Action &action) {
      if (action.type() == "START") {
          if (action.name() == "UP") {
              m_selectedMenuIndex = (m_selectedMenuIndex > 0) ? m_selectedMenuIndex - 1 : m_menuStrings.size() - 1;
          } else if (action.name() == "DOWN") {
              m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size();
          } else if (action.name() == "PLAY") {
              m_game->changeScene("PLAY", std::make_shared<Scene_Play>(m_game, m_levelPaths[m_selectedMenuIndex]));
          } else if (action.name() == "QUIT") {
              onEnd();
          }
      }
  }
  ```

---

#### **Replays**
- **Purpose**: Record and replay gameplay by saving the sequence of player actions.
- **Implementation**:
  1. **Record Actions**:
     - Store `Action` objects in a file, along with the game frame in which they occurred.
     - Example: `"Frame: 120, Action: {"Right", "START"}"`.
  2. **Replay Actions**:
     - Load the recorded file during playback.
     - Feed `Action` objects into the Scene at the appropriate frames.
- **Benefits**:
  - Replays are easy to implement because Actions are abstract and independent of input methods.

---

#### **Advantages of the Action System**
1. **Decoupling**:
   - Separates input logic from game logic.
   - Scenes focus on executing actions, not handling input directly.
2. **Input Flexibility**:
   - Allows for re-mapping of controls without modifying game logic.
   - Easily integrates new input devices (e.g., mouse, VR controllers).
3. **Replay System**:
   - Simplified replay functionality through stored Actions.
4. **Scene-Specific Customization**:
   - Each Scene can define unique mappings and actions.
5. **Extensibility**:
   - Future-proof design supports advanced features like multiplayer actions or network commands.

---

This detailed system enhances flexibility, scalability, and modularity in input handling and action execution for modern game engines.
