#ifndef MAZEGAME_HPP
#define MAZEGAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "graph.hpp"
#include "canvas.hpp"
#include "menu.hpp"

class MazeGame {
private:
    Canvas canvas;
    Graph graph;
    Menu menu;
    sf::RenderWindow window;
    std::vector<std::pair<int, int>> mst;
    int size;
    bool start = false;

    void processEvents();
    void render();
    void generateMaze();
    void debugPrint();

public:
    MazeGame();
    void run();
};

#endif // MAZEGAME_HPP
