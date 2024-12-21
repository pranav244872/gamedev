## Assingment 1

### 1. **Read descriptions of shapes from a configuration file, and then draw those shapes to the screen.**

   - **Current Status**: The program can successfully read shapes (both circles and rectangles) from the configuration file. The shape's color, position, and speed are read and processed, and shapes are correctly rendered on the screen.

   - **Completed**: Logic has been implemented for both `Circle` and `Rectangle` classes, including setting the initial position, color, and speed, as well as rendering these shapes on the SFML window.

### 2. **Each Shape will have a name, position, speed, color, as well as properties unique to each shape type. For example, a Rectangle will have width and height, a circle will have a radius.**

   - **Current Status**: The `Circle` class has been implemented with the required properties: `name`, `position`, `speed`, `color`, and `radius`. The `Rectangle` class has also been implemented with similar properties, including `width` and `height`.

   - **Completed**: Both `Circle` and `Rectangle` classes are fully implemented, and shapes are correctly initialized and drawn according to the config file.

### 3. **For this assignment, the position of a shape refers to its SFML default of the upper-left corner of the shape.**

   - **Current Status**: The position is being correctly set for both circles and rectangles according to the config file, and the shape is rendered with the upper-left corner at the specified coordinates.

   - **Completed**: The program correctly initializes shapes based on the upper-left corner position, and rendering works as intended for both shape types.

### 4. **You are also required to make these shapes "bounce off" the sides of the window which contains them. This means that if a shape's left side hits the left side of the window, its X speed reverses.**

   - **Current Status**: Implemented the bouncing logic for both `Circle` and `Rectangle` shapes when they hit the window boundaries, reversing the speed along the respective axes.

   - **Completed**: The program now handles collisions with the window boundaries and reverses the direction of movement for both `Circle` and `Rectangle` shapes appropriately.

---

## Example config.txt

```txt
Window 800 600  
Circle CGreen 100 100 -0.03 0.02 0 225 0 50  
Circle CBlue 200 200 0.02 0.04 0 0 225 100  
Rectangle RRed 200 200 0.1 0.15 225 0 0 250 25  
Rectangle RGrey 300 250 -0.02 0.02 100 100 100 50 100  
```

### Explanation of each term

- **Rectangle N X Y SX SY R G B W H**
  - `N`: Shape Name (std::string)
  - `X`, `Y`: Initial Position (float, float)
  - `SX`, `SY`: Initial Speed (float, float)
  - `R`, `G`, `B`: RGB Color (int, int, int)
  - `W`, `H`: Size (Width, Height) (float, float)

- **Circle N X Y SX SY R G B R**
  - `N`: Shape Name (std::string)
  - `X`, `Y`: Initial Position (float, float)
  - `SX`, `SY`: Initial Speed (float, float)
  - `R`, `G`, `B`: RGB Color (int, int, int)
  - `R`: Radius (float)

---

## Code to Run

To compile and run the project, you can use the following `g++` command:

```bash
g++ -o MyGame src/main.cpp src/ConfigReader.cpp src/Circle.cpp src/Rectangle.cpp src/Shape.cpp -I./include -lsfml-graphics -lsfml-window -lsfml-system
```

### To Run the Program:

1. **After Compilation**: Run the program by executing the following command:

   ```bash
   ./MyGame
   ```

   This will launch the SFML window with the shapes as described in the `config.txt` file.

---

## Remaining Tasks (Completed)

1. **Add Bouncing Logic**: Implemented logic to make shapes bounce off the window edges when they hit the left, right, top, or bottom boundary of the window, reversing their speed along the respective axes.

2. **Implement Movement Logic**: The program now updates the position of each shape based on its speed in each frame before rendering the shape again.

---
