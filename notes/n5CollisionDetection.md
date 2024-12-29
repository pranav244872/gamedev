### **Collision Programming in Games**

Collision programming involves two main stages: 

1. **Collision Detection**:  
   - Determines if two entities intersect based on their shapes or bounds.  
   - Focuses on solving geometric problems.

2. **Collision Resolution**:  
   - Resolves what happens after a collision, often based on the game's physics rules.  

---

### **Assumptions**
- **Entities** are defined as objects with the following properties:  
  - **Position**: Defined by \(x, y\) coordinates.  
  - **Bounding Shape**: Simple geometric shapes (circle, rectangle, etc.) to approximate the entity.  
  - **Velocity**: \(dx, dy\), which describes the entity's movement in both axes.  

- **Goal**:  
  - Develop methods to detect and resolve collisions between entities for interactive gameplay.

---

### **Collision Detection**

#### Collision Detection Problems

1. **Future Collision**:  
   - Determine if, when, and where two entities with positions, velocities, and shapes will collide.

2. **Current Collision**:  
   - Check if two entities at specific positions currently intersect (returns true or false).

3. **Overlap Calculation**:  
   - If two entities intersect, compute:  
     - The coordinates of the overlapping region.  
     - The width and height of the overlap.

---

### **Entity Bounding Shapes**

#### Real-World vs. Bounding Shapes  
- Real-world objects are complex and irregular, making precise calculations computationally expensive.  
- Bounding shapes simplify entities into basic geometric forms for collision detection.  

#### Common Bounding Shapes  
- **2D**: Circles, rectangles, triangles, and lines.  
- **3D**: Spheres, boxes, cones, planes, and cylinders.  

**Example**:  
- In games, a character's bounding box is often the smallest rectangle that can contain its sprite.

---

### **2D Bounding Shapes**

#### Circle  
- Simplest shape to compute.  
- Requires only the center and radius.  
- Used for fast intersection checks.

#### Rectangle  
- Most common shape in 2D sprite-based games.  
- Aligning rectangles to the axes simplifies collision checks (Axis-Aligned Bounding Boxes).

---

### **Axis-Aligned Bounding Boxes (AABB)**

#### Overview  
- An **AABB** is a rectangle whose edges align with the X and Y axes.  
- Simplifies collision detection compared to rectangles with arbitrary angles.

#### Intersection Check for AABBs  
For two rectangles:  
- First rectangle: Top-left (x1, y1), width w1, height h1.  
- Second rectangle: Top-left (x2, y2), width w2, height h2.  

- **Horizontal Overlap**:  
  y1 is less than or equal to y2 + h2  
  and  
  y1 + h1 is greater than or equal to y2  

- **Vertical Overlap**:  
  x1 is less than or equal to x2 + w2  
  and  
  x1 + w1 is greater than or equal to x2  

If both conditions are true, the rectangles intersect.

#### Point Inside AABB  
To check if a point (px, py) lies inside an AABB:  
- x1 <= px <= x2  
- y1 <= py <= y2  

---

### **Centered AABB Intersection**

#### Centered AABB  
- The center of the entity defines the AABB position.  
- The width and height are divided in half (half-size) for calculations.

#### Overlap Calculation  
For two AABBs with centers (cx1, cy1) and (cx2, cy2):  

- **X-Direction Overlap**:  
  dx = absolute difference of x2 - x1  
  ox = (w1 / 2) + (w2 / 2) - dx  
  - If ox is positive, the AABBs overlap in the X direction.  

- **Y-Direction Overlap**:  
  dy = absolute difference of y2 - y1  
  oy = (h1 / 2) + (h2 / 2) - dy  
  - If oy is positive, the AABBs overlap in the Y direction.

#### Combined Overlap  
The overlap vector is (ox, oy).  

---

### **Collision Resolution**

#### Resolving Overlap  
- Push entities apart based on the overlap direction to resolve the collision.  

#### Detecting Collision Direction  
- Use overlap values and previous positions to identify the collision direction.  
  - If overlap.y > 0: Collision is likely from the sides.  
  - If overlap.x > 0: Collision is likely from above or below.  

#### Examples  
- If a player collides with a tile, push the player out of the tile.  
- For bullets hitting entities, mark the entity as "hit."

---

### **Special Cases**

#### Super Mario Bros Example  
- Mario kills an enemy by jumping on it if:  
  - Mario is moving downward.  
  - X-direction overlap is ignored.  

---

### **Diagrams**

#### Point Inside AABB
A point is inside the rectangle if it satisfies:  
- x1 <= px <= x2  
- y1 <= py <= y2  

Example Diagram:
```
+----------------+
|                |
|      (px, py)  |
|                |
+----------------+
```

#### AABB Overlap  
Horizontal and vertical overlaps determine if rectangles intersect.  

Example Diagram:  
```
+-------+       +-------+
|   A   |       |   B   |
+-------+       +-------+
```

#### Centered AABB  
Center positions and half-sizes are used for overlap calculations.  

Example Diagram:  
```
+------------+     +------------+
|    cx1     |     |    cx2     |
|            |     |            |
+------------+     +------------+
```

---

### **Advanced Collision Resolution**

- **Elastic/Inelastic Collisions**: Consider changes in velocity after collisions.  
- **Physics Simulation**: Use mass, forces, and momentum for more realistic behavior.  

This breakdown covers all points in detail, providing explanations, conditions, and diagrams for better understanding.
