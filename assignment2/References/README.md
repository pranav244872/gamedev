# Assignment 2: Game Development Instructions

This assignment involves creating a game with specific mechanics and features. Follow the steps below to implement the required functionality.

---

## Features and Mechanics

### **Player**
- **Representation:** A shape defined in the configuration file.
- **Spawn:** 
  - At the center of the screen at the start.
  - Respawn after collision with an enemy.
- **Movement:** Controlled by `W`, `A`, `S`, `D` keys at a speed specified in the configuration file. Movement is confined to window bounds.
- **Shooting:** 
  - Fires bullets toward the mouse pointer when the left mouse button is clicked.
  - Bullets have speed, size, and lifespan specified in the configuration file.
- **Special Ability:** 
  - Triggered by the right mouse button.
  - Must:
    - Spawn multiple entities (e.g., bullets).
    - Use unique graphics.
    - Introduce a new game mechanic via a new component.
    - Include a cooldown timer.

---

### **Enemy**
- **Spawn:** 
  - At random locations within screen bounds every X frames (X is specified in the configuration file).
  - Must not overlap screen edges.
- **Properties:**
  - Randomized number of vertices between a minimum and maximum (config file).
  - Radius specified in the configuration file.
  - Random color and speed (within a config-defined range).
- **Behavior:**
  - Bounce off window edges while maintaining speed.
  - On collision with bullets or the player:
    - Destroy large enemies and spawn smaller enemies.
    - Number of smaller enemies = number of vertices of the original enemy.
    - Smaller enemies have the same color and move outward at intervals of `360 / vertices`.

---

### **Score**
- **Points:**
  - Large enemy: `N * 100` (N = number of vertices).
  - Small enemy: Double the large enemy’s score.
- **Display:** 
  - Font, size, and color defined in the configuration file.
  - Displayed at the top-left corner of the screen.

---

### **Drawing**
- **Entity Rotation:** Slow rotation for visual enhancement.
- **Entity Alpha Transparency:**
  - Alpha decreases proportionally with the lifespan.
  - Example: A 100-frame lifespan entity alive for 50 frames will have an alpha value of `0.5 * 255`.

---

### **Miscellaneous**
- `P` Key: Pause the game.
- `ESC` Key: Exit the game.

---

## Configuration File Format

### Example:
```plaintext
Window 1280 720 60 0
Font fonts/tech.ttf 24 255 255 255
Player 32 32 5 255 0 0 4 8
Enemy 32 32 3 3 255 255 255 8 12 60 90
Bullet 10 10 20 255 255 255 4 20 90
```

### **Structure**
1. **Window:**  
   Format: `Window W H FL FS`  
   - `W, H`: Width and height (integers).  
   - `FL`: Frame limit.  
   - `FS`: Fullscreen mode (1 = yes, 0 = no).

2. **Font:**  
   Format: `Font F S R G B`  
   - `F`: Font file path.  
   - `S`: Font size.  
   - `R, G, B`: Font color (RGB integers).

3. **Player Specification:**  
   Format: `Player SR CR S FR FG FB OR OG OB OT V`  
   - `SR, CR`: Shape and collision radius.  
   - `S`: Speed.  
   - `FR, FG, FB`: Fill color (RGB).  
   - `OR, OG, OB, OT`: Outline color and thickness.  
   - `V`: Number of vertices.

4. **Enemy Specification:**  
   Format: `Enemy SR CR SMIN SMAX OR OG OB OT VMIN VMAX L SI`  
   - `SR, CR`: Shape and collision radius.  
   - `SMIN, SMAX`: Speed range.  
   - `OR, OG, OB, OT`: Outline color and thickness.  
   - `VMIN, VMAX`: Vertex count range.  
   - `L`: Small enemy lifespan.  
   - `SI`: Spawn interval (frames).

5. **Bullet Specification:**  
   Format: `Bullet SR CR S FR FG FB OR OG OB OT V L`  
   - `SR, CR`: Shape and collision radius.  
   - `S`: Speed.  
   - `FR, FG, FB`: Fill color.  
   - `OR, OG, OB, OT`: Outline color and thickness.  
   - `V`: Number of vertices.  
   - `L`: Lifespan.

---

## Development Plan

### **Preliminary Steps**
1. **Vec2 Class:**  
   Implement a class for vector operations (used in components).

2. **EntityManager:**  
   - Implement `addEntity()` and `update()`.  
   - Focus on adding entities and basic updates. Delayed entity removal can be implemented later.

---

### **Basic Game Setup**
1. **Game Class:**
   - Create a player entity using `spawnPlayer()`.
   - Implement basic drawing in `sRender()`.
   - Spawn enemies using `spawnEnemy()`.
   - Spawn a bullet using `spawnBullet()`.

2. **Player Movement:**  
   Implement in `sUserInput` and `sMovement`.

3. **EntityManager Update:**  
   Implement `update()` to remove dead entities.

---

### **Core Mechanics**
1. **Tag-Based Entity Retrieval:**  
   Implement `getEntities(tag)` in `EntityManager`.

2. **Collision System:**  
   Implement `sCollision` and handle entity destruction.

---

### **Advanced Features**
1. **Special Ability:**  
   Add new components, unique mechanics, and cooldown logic.

2. **Config File Parsing:**  
   Read and use configuration file data for window, player, enemy, and bullet properties.

3. **Score System:**  
   Display score on screen using specified font.

---

## Additional Notes
- Start with simpler mechanics and incrementally build complexity.
- Test each feature thoroughly before proceeding to the next.  
