## **Program Specification**

This assignment involves creating a game with various components, such as assets, animations, entities, and player mechanics. Below are the key details and requirements for each part of the game.

---

### **Assets**

- **Entities** in the game are represented using various **Textures** and **Animations**. These are collectively referred to as **Assets** (including Fonts).
- Assets are **loaded once at the beginning** of the program and stored in the `Assets` class, which is then managed by the `GameEngine` class.
- All assets are defined in an **assets.txt** file with the following syntax.

---

### **Player Mechanics**

1. **Player Entity (Megaman)**:
   - The player has several animations: **Stand, Run, Air**.
   - The player’s current state determines which animation is used.
   
2. **Player Controls**:
   - **Left**: Press the **A** key
   - **Right**: Press the **D** key
   - **Jump**: Press the **W** key (only if standing on a tile)
   - **Shoot**: Press the **Space** key
   
3. **Player Movement**:
   - Can move left/right at any time, even in the air.
   - Player can only **jump** if standing on a **tile**.
   - **Gravity** accelerates the player downward when not on a tile.
   - The player has a **maximum speed** defined in the level file.
   
4. **Player Collision**:
   - The player **collides** with **Tile** entities.
   - The player **does not collide** with **Decoration** entities.
   - If the player falls below the screen, they **respawn** at the start.
   
5. **Player Behavior**:
   - The player’s **sprite** faces the direction they are moving.
   - The player’s **bounding box** is centered on their sprite.

---

### **Animations**

1. **Animation Assets**:
   - Animations consist of multiple **frames** inside a **texture**.
   - The **Animation class** handles frame progression and animation speed.
   
2. **Animation Methods**:
   - Implement `Animation::update()` to update the animation state.
   - Implement `Animation::hasEnded()` to check if the animation is complete.
   - Non-repeating animations are destroyed once `hasEnded()` is true.
   
3. **Animation Types**:
   - **Repeating**: Loops indefinitely.
   - **Non-repeating**: Plays once and then is destroyed.

---

### **Decoration Entities**

1. **Decoration Entities (Dec)**:
   - Do not interact with other entities in the game.
   - Can use any animation but are typically used for things like clouds, bushes, etc.
   
2. **Behavior**:
   - Decorations do not have collision boxes and are simply drawn on the screen.

---

### **Tile Entities**

1. **Tile Entities**:
   - Tiles define the level geometry and interact with players.
   - Tiles have a **Bounding Box** equal to the size of their animation.
   
2. **Tile Types**:
   - **Brick Tiles**:
     - Animation: `Brick`.
     - When hit by a bullet or player from below, it changes to the `Explosion` animation.
     - The `BoundingBox` is removed when the explosion animation ends.
     
   - **Question Tiles**:
     - Animation: `Question`.
     - When hit by a player from below, the animation changes to `Question2`, and a **Coin** entity is spawned above.

---

### **Game Controls**

1. **General Controls**:
   - **P**: Pause the game.
   - **T**: Toggle drawing textures.
   - **C**: Toggle drawing bounding boxes of entities.
   - **G**: Toggle drawing the grid (helpful for debugging).
   - **ESC**: Return to the MainMenu or quit if on the Main Menu.

---

### **Level Creation**

1. **Level Specification File**:
   - The level is defined in the `level.txt` file and contains the following entity types:
   
   - **Tile Entity**:
     ```
     Tile N GX GY
     ```
     - Animation name `N`, grid position `GX, GY` (float).
     
   - **Decoration Entity**:
     ```
     Dec N X Y
     ```
     - Animation name `N`, position `X, Y` (float).
   
   - **Player Entity**:
     ```
     Player GX GY CW CH SX SY SM GY B
     ```
     - Grid position `GX, GY`, bounding box size `CW, CH`, movement speed `SX`, jump speed `SY`, max speed `SM`, gravity `GY`, bullet animation `B`.
     
---

### **Assets File Specification**

1. **Texture Asset**:
   ```
   Texture N P
   ```
   - `N`: Texture Name (string).
   - `P`: Texture Filepath (string).
   
2. **Animation Asset**:
   ```
   Animation N T F S
   ```
   - `N`: Animation Name (string).
   - `T`: Texture Name (string).
   - `F`: Frame Count (integer).
   - `S`: Animation Speed (integer).
   
3. **Font Asset**:
   ```
   Font N P
   ```
   - `N`: Font Name (string).
   - `P`: Font File Path (string).

---

### **Implementation Hints**

1. **Rendering**:
   - You can use the **T** key to toggle drawing textures.
   - You can use the **C** key to toggle drawing bounding boxes.
   - You can use the **G** key to toggle the grid display (useful for debugging).
   
2. **Animation Functions**:
   - Implement `Animation::update()` and `Animation::hasEnded()`.
   - These implementations do not affect the gameplay directly but are required for proper animation handling.

3. **Functions to Implement**:
   - **`Scene_Play::loadLevel()`**: Load the level data from the level file, parse it, and add the correct entities to the `EntityManager`.
   - **`Scene_Play::gridToMidPixel()`**: Convert grid positions to pixel positions for entity placement (consider entity size and animation).
   - **`Scene_Play::spawnPlayer()`**: Read player configuration from the level file and spawn the player.
   - **Player movement**: Implement basic **WASD** movement for testing.
   - **`Scene_Play::spawnBullet()`**: Implement bullet firing on **Space** key press. Bullets should travel in the direction the player is facing and should not continuously fire when holding the key.

---

### **Example Level Definition**

Here’s an example of how entities and the player are defined in a `level.txt` file:

```
Tile Ground 0 0
Tile Ground 1 0
Tile Ground 2 0

Dec Flag 82.5 6
Dec CloudSmall 2 7

Player 2 6 48 48 5 -20 20 0.75 Buster
```

This defines:
- **Tiles** at positions (0, 0), (1, 0), (2, 0).
- **Decoration Entities**: Flag at (82.5, 6) and small cloud at (2, 7).
- **Player** starts at position (2, 6) with specific attributes like speed, jump, max speed, gravity, and bullet animation.

---

### **General Approach**

1. **Create and load assets**: Load all assets (textures, animations, fonts) from `assets.txt`.
2. **Parse the level file**: Define and load the entities from `level.txt`, including tiles, decorations, and the player.
3. **Handle player input**: Implement controls for movement, jumping, and shooting.
4. **Animation management**: Handle animations for entities, updating and checking if they have finished.
5. **Implement game logic**: Handle collisions, tile interactions, and respawn logic for the player.
