# Snake Game
This is the first draft of a simple 2D game using the SFML library. We decided to build a snake prototype, which has some clear differentiations with a normal version of snake. There are three types of food, static green food which makes the snake grow by one segment, static and moving red food, which remove thirty segments from the snake, and moving blue food, which adds thirty segments to the length of the snake.

## Dependencies
- This project depends on the [SFML library](https://www.sfml-dev.org/index.php). SFML can be installed via apt on Linux, brew on MacOS, or downloading from the website and linking the directory directly on the CMakeList.txt on Windows.
- The project is also built using `cstdlib`, `ctime`, and `cmath`, all of which are used to perform updated while the game is playing and creating new objects.
- The project is set to be tested using [GoogleTest](https://github.com/google/googletest), which is being directly fetched inside of the CMakeLists.txt file for a smooth integration across different platforms.

## Assumptions on the environment
- The game is built to be played on a 900x700 screen, and it is not responsive to different screen sizes.
- The game supports only one player at a time, and it is played by using the `arrow keys` to move the snake around the screen
- The game is built to be played in a Linux, macOS or Windows environment, although it has not been tested in Linux specifically.

## User's guide
- Once the game has been built, it can be run by using the run button on the IDE, or by running the executable file in the build folder.
- The game starts automatically once the executable is run.
- The objective of the game is to survive as long as possible, while eating the food.
- The game ends when the snake hits the wall or itself.
- There are three different types of food; `green, red, and blue`.
  - `Green` food makes the snake grow by one segment.
  - `Red` food
    - There are two types of red food; static and moving.
    - Both types of red food make the snake shrink by thirty segments.
  - `Blue` food makes the snake grow by thirty segments.
  - To move inside the game use the `arrow keys` (up, down, left, right).

## Developer's guide
### Overview
This documentation provides an insight into the development and functionality of the Snake Game implemented using SFML.

### Project Structure
There are 4 main files to build the game's functionality and logic, all inside of the `include` folder:
- `main.cpp` - This file contains the main function which is the entry point of the program. This file calls the game.h file to start the game.
- `game.h` - This file contains the game class which is responsible for the game's functionality and logic.
- `Position.h` - This file contains the Position class which is responsible for the position of the snake and the food.
- `PlayerMovement.h` - This file contains the PlayerMovement class which is responsible for updating the direction of the snake and apples

### Classes
- `Game` class
  - The `Game` class manages the game's functionality and logic. This class handles initialization, user input, updates as well as rendering.
- `Position` class
  - The `Position` struct manages the position of the snake and the apples. This class handles the position of the snake and the apples. It is used in the `PlayerMovement` class to update the position
- `PlayerMovement` class
  - The `PlayerMovement` class manages the direction of the snake and the apples. This class handles the direction of the snake and the apples.

### Member Variables
- `window` - This variable is of type `sf::RenderWindow` and is responsible for creating the window for the game.
- `background` - This variable is of type `sf::Sprite` and is responsible for creating the background for the game.
- `backgroundTexture` - This variable is of type `sf::Texture` and is responsible for creating the texture for the background.
- `playerTexture` - This variable is of type `sf::Texture` and is responsible for creating the texture for the snake.
- `player` - This variable is of type `sf::CircleShape` and is responsible for creating the snake.
- `apple` - This variable is of type `sf::CircleShape` and is responsible for creating the green food.
- `movingApple` - This variable is of type `sf::CircleShape` and is responsible for creating the blue food.
- `shrinkingApple` - This variable is of type `sf::CircleShape` and is responsible for creating the red food.
- `additionalShrinkingApple` - This variable is of type `sf::CircleShape` and is responsible for creating the red food.
- `playerPosition` - This variable is of type `Position` and is responsible for creating the position of the snake.
- `direction` - Enum class which is responsible for the direction of the snake.
- `snakeBody` - This variable is of type `std::vector<Position>` and is responsible for creating the snake's body.
- `isGameOver` - This variable is of type `bool` and is responsible for determining if the game is over.
- `x` & `y` - These variables are of type `float` and are responsible for telling us the position of the snake.

### Member Functions
- `Game` class
  - `initWindow()` - This function is responsible for initializing the window.
  - `initBackground()` - This function is responsible for initializing the background.
  - `initPlayer()` - This function is responsible for initializing the snake.
  - `initApple()` and `randomizeApplePosition()` - These functions are responsible for initializing the green food.
  - `initMovingApple()` and `randomizeMovingApplePosition()` - These functions are responsible for initializing the blue food.
  - `initShrinkingApple()` and `randomizeShrinkingApplePosition()` - These functions are responsible for initializing the red food.
  - `initAdditionalShrinkingApple()` and `randomizeAdditionalShrinkingApplePosition()` - These functions are responsible for initializing the red food.
  - `checkAppleOverlap()` - This function is responsible for checking if the food is overlapping (static food).
  - `processInput()` - This function is responsible for processing the user input (arrow keys).
  - `update()` - This function is responsible for updating the game's state.
  - `updateMovingApplePosition()` & `updateAdditionalShrinkingApplePosition()` - These functions are responsible for updating the position of the blue and red moving food.
  - `checkCollision()` - This function is responsible for checking if there are any collisions (snake crashing into itself or eating the food).
  - `growSnake()` & `shrinkSnake()` - These functions are responsible for growing and shrinking the snake.
  - `render()` - This function is responsible for rendering the game.
  - `run()` - This function is responsible for running the game.
  - `getSnakeSize()` - This function is responsible for getting the size of the snake.
  - `getSnakePosition()` - returns the current position of the snake for a specific segment.
- `Position` struct which is used in the `PlayerMovement` class
  - `x` & `y` - These variables are of type `float` and are responsible for telling us the position of the snake.
- `PlayerMovement` class
  - `updatePosition()` - This function is responsible for updating the position of the snake and the food.

### Testing
- The project is tested using [GoogleTest](https://github.com/google/googletest), which is fetched inside the CMakeLists.txt file for a smooth integration across different platforms.
- The tests are located inside the googletest.cpp file inside the src folder, and can be run by finding the game_tests executable, created by the CMakeLists file.
- The tests are divided into four different suites; one to check game initialization, one to check the game's functionality, one to check if the size of the snake is correct, and one to check for collision.
