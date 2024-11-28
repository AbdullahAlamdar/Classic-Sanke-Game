# Snake Game

**Author**: M. Abdullah  
**Course**: Programming Fundamentals  
**Project Date**: 1st Semester, 2023  

## Description

This is a classic Snake game developed using **OpenGL** in C++. The game combines elements of strategy and reflex to provide an engaging experience. The objective is to control a snake, navigate the game grid, and eat food to grow longer while avoiding collisions with walls or itself. The game includes special power-ups and dynamic food mechanics to enhance the challenge.

---

## Features

### Core Gameplay
- **Snake Movement**: Navigate the snake in four directions (up, down, left, right) using arrow keys.
- **Dynamic Growth**: The snake grows longer each time it eats regular food.
- **Game Over Scenarios**:
  - Collision with walls.
  - Collision with itself.
- **Real-time Score Display**: The score is updated and displayed on-screen.

### Food Mechanics
- **Regular Food**:
  - Maximum of 5 regular food items present on the grid at any time.
  - Eating a food item increases the score by 5 points.
  - Food expires after 15 seconds if not eaten.
- **Power Food**:
  - A special power-up that adds 20 points to the score when consumed.
  - Only one power food appears on the grid at a time.
  - Expires after 15 seconds if not eaten.

### Graphics and Interface
- **Grid Design**: The grid is designed with a clean and colorful layout using OpenGL.
- **Snake Representation**: The snake is rendered as a series of connected green squares.
- **Food Representation**:
  - Regular food is represented as small circles.
  - Power food is represented as larger circles.
- **Interactive UI**:
  - Score is displayed dynamically during gameplay.
  - Alerts appear using Zenity when the game ends.

### Controls
- **Arrow Keys**:
  - `↑` Up
  - `↓` Down
  - `←` Left
  - `→` Right
- **Keyboard Commands**:
  - `ESC`: Exit the game.

---

## Code Overview

### Key Variables
- **Snake**:
  - `snake_x[]` and `snake_y[]`: Store the positions of the snake's segments.
  - `num_segments`: Number of segments in the snake.
  - `direction`: Current movement direction of the snake.
- **Food**:
  - `food_x[]` and `food_y[]`: Store the positions of regular food.
  - `food_creation_time[]`: Track when each food item was created.
  - `num_of_food`: Number of active regular food items.
- **Power Food**:
  - `power_food_x[]` and `power_food_y[]`: Store the position of power food.
  - `power_food_active[]`: Boolean to track whether power food is active.
  - `power_food_creation_time[]`: Track when power food was created.

### Functions
- **Display**:
  - Renders the game interface, snake, and food items on the screen.
- **NonPrintableKeys**:
  - Handles arrow key inputs for snake movement.
- **Timer**:
  - Updates the game state, moves the snake, and checks for collisions.
- **generatefood**:
  - Generates random positions for food and power food.
- **removalofexpiredfood**:
  - Removes expired food items from the grid.
- **isfoodpositionvalid**:
  - Ensures new food positions do not overlap with the snake or other elements.

---

## How to Run the Game

1. **Dependencies**:
   - OpenGL library (`glut`).
   - `Zenity` (for end-game alerts).
2. **Compile**:
   ```bash
   make
   ```
3.**Run**
   ```bash
   ./game-release
   ```
