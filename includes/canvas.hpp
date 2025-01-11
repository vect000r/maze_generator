#ifndef CANVAS_HPP
#define CANVAS_HPP

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
    Canvas(int size = 5) : mazeSize(size) {  // domyślny rozmiar to 5
        // Oblicz wymiary canvasu
        rows = 2 * size + 1;
        cols = 2 * size + 1;
        width = cols * cellSize;
        height = rows * cellSize;

        std::cout << "Creating canvas for maze " << size << "x" << size << std::endl;
        std::cout << "Canvas dimensions: " << rows << "x" << cols << std::endl;

        // Zainicjuj canvas
        canvas.clear();  // Wyczyść poprzedni canvas
        canvas.resize(rows, std::vector<Cell>(cols));
        
        // Inicjalizacja komórek
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                canvas[i][j].setPosition({j, i});
                canvas[i][j].setPath(false);  // domyślnie wszystkie ściany
            }
        }
    }


    // operator przypisania
    Canvas& operator=(const Canvas& other) {
        if (this != &other) {
            mazeSize = other.mazeSize;
            rows = other.rows;
            cols = other.cols;
            width = other.width;
            height = other.height;
            canvas = other.canvas;
        }
        return *this;
    }
    
    
    void setMST(const std::vector<std::pair<int, int>>& edges, int graphSize) {
        std::cout << "Setting MST for size " << graphSize << std::endl;
        
        // Reset canvas
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                canvas[i][j].setPath(false);
            }
        }

        // Procesuj krawędzie
        for (const auto& edge : edges) {
            int x1 = edge.first % graphSize;
            int y1 = edge.first / graphSize;
            int x2 = edge.second % graphSize;
            int y2 = edge.second / graphSize;

            // Przekształć współrzędne grafu na współrzędne canvasu
            int cx1 = x1 * 2 + 1;
            int cy1 = y1 * 2 + 1;
            int cx2 = x2 * 2 + 1;
            int cy2 = y2 * 2 + 1;

            // Sprawdź zakres przed użyciem
            if (cy1 >= 0 && cy1 < rows && cx1 >= 0 && cx1 < cols) {
                canvas[cy1][cx1].setPath(true);
            }
            if (cy2 >= 0 && cy2 < rows && cx2 >= 0 && cx2 < cols) {
                canvas[cy2][cx2].setPath(true);
            }

            // Ustaw ścieżkę między komórkami
            if (cx1 == cx2) { // pionowa ścieżka
                int midY = (cy1 + cy2) / 2;
                if (midY >= 0 && midY < rows && cx1 >= 0 && cx1 < cols) {
                    canvas[midY][cx1].setPath(true);
                }
            } else if (cy1 == cy2) { // pozioma ścieżka
                int midX = (cx1 + cx2) / 2;
                if (cy1 >= 0 && cy1 < rows && midX >= 0 && midX < cols) {
                    canvas[cy1][midX].setPath(true);
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(j * cellSize, i * cellSize);
                cell.setFillColor(canvas[i][j].getPath() ? sf::Color::White : sf::Color::Black);
                window.draw(cell);
            }
        }
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    const std::vector<std::vector<Cell>>& getCells() const { return canvas; }
};



#endif