### Vectors in Games

In game development, especially for 2D games, vectors are essential for representing quantities or properties that have both magnitude and direction. These properties include **position**, **velocity**, **acceleration**, and more. While vectors can exist in higher dimensions (e.g., 3D or 4D), this discussion focuses on **2D vectors** used in 2D games.

---

### Why Use Vectors in Games?

1. **Unified Representation**:
   - Many game properties like position `(x, y)` or velocity `(x, y)` naturally exist in 2D space. Using a single vector to represent these properties simplifies code and reduces errors.

2. **Mathematical Operations**:
   - Vectors enable us to perform calculations like addition, subtraction, scaling, and normalization in a way that mirrors their mathematical definitions.

3. **Convenience**:
   - It is cumbersome and error-prone to manage `x` and `y` values separately. A vector class encapsulates these properties, making the code more readable and maintainable.

---

### What is a Vector?

- A **vector** in mathematics is a quantity that has both a **magnitude** (length) and a **direction**. 
- In 2D games, a vector is represented as `(x, y)`, where `x` and `y` are coordinates or components.

#### Examples in Games:
1. **Position Vector**:
   - Represents the location of an object in 2D space, e.g., `(100, 200)`.

2. **Velocity Vector**:
   - Represents how fast and in what direction an object is moving, e.g., `(5, -3)` means the object moves 5 units right and 3 units up per frame.

---

### Why Create a Custom Vector Class?

Game frameworks like **SFML** already provide built-in 2D vector classes like `sf::Vector2f`. However, creating a custom class like `Vec2` allows for:
- Full control over functionality and operations.
- Tailoring to specific game requirements.
- Learning and understanding vector operations in depth.

---

### Designing the `Vec2` Class

#### What to Store in `Vec2`?
- Member variables:
  - `x`: Represents the horizontal component of the vector.
  - `y`: Represents the vertical component of the vector.

#### What Operations Should `Vec2` Support?
1. **Arithmetic**:
   - Add, subtract, multiply, and divide vectors.
2. **Vector Properties**:
   - Calculate length (magnitude).
   - Normalize the vector (convert to a unit vector).
   - Rotate the vector by a given angle.
3. **Chaining Operations**:
   - Allow methods to return references to the same object for chaining.

---

### Implementation of `Vec2`

Here’s how we might implement a simple 2D vector class in C++:

```cpp
class Vec2 {
public:
    // Member variables for the x and y components
    float x = 0;
    float y = 0;

    // Default constructor (no arguments)
    Vec2() {}

    // Constructor to initialize x and y
    Vec2(float xin, float yin) : x(xin), y(yin) {}

    // Addition operator
    Vec2 operator+(const Vec2& rhs) const {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    // Subtraction operator
    Vec2 operator-(const Vec2& rhs) const {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    // Scalar multiplication
    Vec2 operator*(float scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    // Scalar division
    Vec2 operator/(float scalar) const {
        return Vec2(x / scalar, y / scalar);
    }

    // Add vector values to the current vector (modifies the object)
    Vec2& add(const Vec2& v) {
        x += v.x;
        y += v.y;
        return *this; // Return reference for chaining
    }

    // Calculate the length (magnitude) of the vector
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalize the vector (convert to a unit vector)
    Vec2 normalize() const {
        float len = length();
        return len > 0 ? Vec2(x / len, y / len) : Vec2(0, 0);
    }

    // Rotate the vector by a given angle (in degrees)
    Vec2 rotate(float angleDegrees) const {
        float angleRadians = angleDegrees * (3.14159265f / 180.0f); // Convert to radians
        float cosA = std::cos(angleRadians);
        float sinA = std::sin(angleRadians);
        return Vec2(
            x * cosA - y * sinA,
            x * sinA + y * cosA
        );
    }
};
```

---

### Explanation of the Code

1. **Constructors**:
   - **Default Constructor**: Initializes `x` and `y` to 0.
   - **Parameterized Constructor**: Allows creating a vector with specific `x` and `y` values.

2. **Arithmetic Operations**:
   - Addition, subtraction, multiplication, and division are overloaded as operators (`+`, `-`, `*`, `/`) for intuitive use.
   - Example:
     ```cpp
     Vec2 v1(3, 4), v2(1, 2);
     Vec2 v3 = v1 + v2; // v3 = (4, 6)
     ```

3. **Vector Properties**:
   - `length()`: Computes the magnitude of the vector using the Pythagorean theorem:  
     \[
     \text{length} = \sqrt{x^2 + y^2}
     \]
   - `normalize()`: Divides each component by the vector’s length to create a unit vector (magnitude = 1).
   - `rotate()`: Rotates the vector by a specified angle using trigonometric functions.

4. **Chaining Operations**:
   - The `add` method returns a reference to `*this` so that operations can be chained:
     ```cpp
     Vec2 v(1, 2);
     v.add(Vec2(3, 4)).add(Vec2(-1, -1)); // v = (3, 5)
     ```

---

### Usage Examples

#### Creating and Using `Vec2` Objects:
```cpp
int main() {
    Vec2 v1(3, 4); // Create a vector (3, 4)
    Vec2 v2(1, 2); // Create another vector (1, 2)

    // Vector addition
    Vec2 v3 = v1 + v2; // v3 = (4, 6)

    // Scalar multiplication
    Vec2 v4 = v1 * 2; // v4 = (6, 8)

    // Normalization
    Vec2 v5 = v1.normalize(); // v5 = (0.6, 0.8)

    // Rotation
    Vec2 v6 = v1.rotate(90); // Rotates v1 by 90 degrees

    // Chaining
    v1.add(Vec2(1, 1)).add(Vec2(-2, -2)); // Updates v1 to (2, 3)
}
```

---

### Advantages of Using `Vec2`

1. **Readability**:
   - Encapsulating `x` and `y` in a single class makes code cleaner and easier to understand.

2. **Reusability**:
   - The `Vec2` class can be reused across various parts of the game (e.g., for positions, velocities, and directions).

3. **Extensibility**:
   - New methods (e.g., dot product, cross product) can easily be added without affecting existing functionality.

4. **Performance**:
   - Using a dedicated class for vector operations reduces redundant calculations and ensures consistent behavior.

---

### Conclusion

A custom `Vec2` class is a powerful tool for handling 2D vector operations in games. It simplifies code, provides meaningful abstractions, and allows for flexibility and extensibility in implementing game mechanics. While built-in libraries like `sf::Vector2f` exist, creating your own class helps tailor functionality to specific needs and deepens understanding of vector mathematics.
