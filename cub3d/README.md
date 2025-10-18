# cub3D Project Summary

## Project Overview
cub3D is a 3D graphics programming project inspired by Wolfenstein 3D, the first first-person shooter game. The goal is to create a dynamic 3D representation of a maze using ray-casting techniques with the miniLibX graphics library. Students must implement a first-person perspective navigation system through a customizable maze environment.

## Key Features & Requirements

### Core Functionality
- **Ray-casting implementation** for 3D perspective rendering
- **Window management** using miniLibX with smooth operation
- **Player movement** using W, A, S, D keys for navigation
- **Camera rotation** using left/right arrow keys
- **Multiple wall textures** for different orientations (North, South, East, West)
- **Customizable floor and ceiling colors**
- **Map parsing** from `.cub` configuration files
- **Proper error handling** with descriptive error messages

### Map Requirements
- **Valid characters**: `0` (empty space), `1` (wall), `N/S/E/W` (player start position and orientation)
- **Must be surrounded by walls** (closed environment)
- **Spaces are valid map elements** that must be handled appropriately
- **Map must be the last element** in the `.cub` file

### File Format Specifications
The `.cub` file must contain:
- **Texture paths**: NO, SO, WE, EA for north, south, west, and east textures
- **Color definitions**: F for floor, C for ceiling in RGB format (0-255 range)
- **Map layout** as the final element

### Technical Requirements
- **Programming Language**: C
- **Graphics Library**: miniLibX
- **Memory Management**: No memory leaks, proper cleanup
- **Makefile Requirements**: $(NAME), all, clean, fclean, re, bonus rules
- **Compilation Flags**: -Wall, -Wextra, -Werror
- **Error Handling**: No unexpected crashes, clean exit on errors

### Input Controls
- **Movement**: W, A, S, D keys
- **Camera Rotation**: Left/Right arrow keys
- **Exit**: ESC key or window close button

### Bonus Features (Optional)
- Wall collisions
- Minimap system
- Interactive doors (open/close)
- Animated sprites
- Mouse-based view rotation

## External Functions & Libraries
- **System Calls**: open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday
- **Mathematics Library**: All math functions (-lm)
- **Graphics**: All miniLibX functions
- **Authorization**: libft library permitted

## Error Conditions
The program must return "Error" followed by an explicit message for:
- Invalid map configurations
- Unclosed maps
- File parsing errors
- Any misconfiguration in the `.cub` file

This project emphasizes mathematical applications in computer graphics, efficient algorithm design, and rigorous C programming practices while introducing students to fundamental 3D rendering techniques.
