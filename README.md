# Maze Generator

A C++ project whose objective is to generate mazes and present them (preferably visually) to the user. 

## Table of Contents
- [Functionality](#functionality)
- [Algorithm Intuition](#intuition)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Functionality

Maze generator provides the user with a choice of the size of the maze (5, 10, 20). 
When the user picks the size of the maze, the app draws it on the screen. When the user closes the app, a screenshot of the maze is saved in the maze.png file.

## Algorithm Intuition

Prim's algorithm is used to find the minimum spanning tree of a lattice graph with randomly generated edges (this ensures that the mazes are almost always different)

The SFML library was used in order to make a GUI and the representation of the maze. A canvas consisting of cells (which can have two colors, black and white) was created. Based on the minimum spanning tree edges, paths where drawn on the canvas.

## Requirements
- C++ compiler supporting C++17 
- SFML library
- Make build system


## Installation

1. Clone the repository:
```bash
git clone https://github.com/vect000r/maze-generator
cd maze-generator
```
2. Compile the project
```bash
make
```
3. Run the application
```bash
make run
```

## Usage

1. Launch the application
2. Select maze size from available options (5x5, 10x10, or 20x20)
3. The maze will be generated and displayed on screen
4. Close the application to save the maze as 'maze.png'

## Project Structure

```plaintext
maze_generator/
├── assets/
│   └── Tiny5-Regular.ttf
├── bin/
├── includes/
│   ├── canvas.hpp
│   ├── cell.hpp
│   ├── graph.hpp
│   ├── mazegame.hpp
│   └── menu.hpp
├── src/
│   ├── canvas.cpp
│   ├── cell.cpp
│   ├── graph.cpp
│   ├── main.cpp
│   ├── mazegame.cpp
│   └── menu.cpp
├── Makefile
└── README.md
```

## Contributing

Contributions/forks are welcome.


