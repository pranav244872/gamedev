# TODO

### 1. **Read descriptions of shapes from a configuration file, and then drawing those shapes to the screen.**

   - **Current Status**: The program can successfully read shapes (only circles at this point) from the configuration file. The shape's color, position, and speed are read and processed.
   
   - **Pending**: Implement support for additional shape types (e.g., `Rectangle`), as well as handling the bouncing behavior when shapes hit the window boundaries.

### 2. **Each Shape will have a name, position, speed, color, as well as properties unique to each shape type. For example, a Rectangle will have width and height, a circle will have a radius.**

   - **Current Status**: The `Circle` class has been implemented with the required properties: `name`, `position`, `speed`, `color`, and `radius`. A `Rectangle` class has not yet been implemented.

   - **Pending**: Implement the `Rectangle` class with similar properties and unique features like `width` and `height`.

### 3. **For this assignment, the position of a shape refers to its SFML default of the upper-left corner of the shape.**

   - **Current Status**: The position is being correctly set for circles according to the config file, and the shape is rendered with the upper-left corner at the specified coordinates.

   - **Pending**: Verify that this works similarly for other shape types (e.g., rectangles).

### 4. **You are also required to make these shapes "bounce off" the sides of the window which contains them. This means that if the shape's left side hits the left side of the window, its X speed reverses.**

   - **Current Status**: This functionality has not yet been implemented. The program currently reads the configuration file and renders the shapes, but no logic exists to reverse the speed when the shapes hit the window boundaries.

   - **Pending**: Implement logic to handle shape collisions with window boundaries, reversing the direction of motion when a shape hits the edge of the window.

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
g++ -o MyGame src/main.cpp src/ConfigReader.cpp src/Circle.cpp src/Shape.cpp -I./include -lsfml-graphics -lsfml-window -lsfml-system
```

### To Run the Program:

1. **After Compilation**: Run the program by executing the following command:

   ```bash
   ./MyGame
   ```

   This will launch the SFML window with the shapes as described in the `config.txt` file.

---

## Remaining Tasks

1. **Add Bouncing Logic**: Implement the logic that makes shapes bounce off the window edges. Specifically, if a shape hits the left, right, top, or bottom boundary of the window, reverse its speed along that axis.

   You can modify the `Circle` class to include this behavior by checking the position of the shape in the `draw()` method or in an update method, and reversing the speed when the shape hits a boundary.

2. **Implement Rectangle Class**: You should also implement the `Rectangle` class in a similar way to `Circle`. This will involve setting up the appropriate properties (like `width` and `height`) and drawing the rectangle to the screen.

3. **Parse Rectangle Shapes in `ConfigReader`**: Once you have implemented the `Rectangle` class, you need to modify the `ConfigReader` to correctly handle the parsing of rectangle shapes from the configuration file, just as you did for circles.
