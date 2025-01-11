#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "canvas.hpp"
#include "cell.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Canvas {
private:
    std::vector<std::vector<Cell>> canvas;
    const int cellSize = 20;  // stały rozmiar pojedynczej komórki
    int mazeSize;  // rozmiar labiryntu (np. 5, 10, 20)
    int width;     // szerokość canvas w pikselach
    int height;    // wysokość canvas w pikselach
    int rows;      // liczba wierszy w canvas (2 * mazeSize + 1)
    int cols;      // liczba kolumn w canvas (2 * mazeSize + 1)

public:
    Canvas(int size = 5);
    Canvas& operator=(const Canvas& other);
    void setMST(const std::vector<std::pair<int, int>>& edges, int graphSize);
    void draw(sf::RenderWindow& window);
    int getWidth() const;
    int getHeight() const;
    const std::vector<std::vector<Cell>>& getCells() const;
};

#endif