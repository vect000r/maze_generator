#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "cell.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Canvas {
private:
    std::vector<std::vector<Cell>> canvas;
    int width = 400;
    int height = 400;
    const int cellSize = 10;
    int cols;
    int rows;

public:
    Canvas() : cols(width / cellSize), rows(height / cellSize) {
        canvas.resize(rows, std::vector<Cell>(cols));
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                canvas[row][col].setPosition({col, row});
            }
        }
    }

    void setMST(const std::vector<std::pair<int, int>>& edges, int graphSize) {
        // Reset canvas: All cells default to walls (black)
        for (auto& row : canvas) {
            for (auto& cell : row) {
                cell.setPath(false); // Black (wall)
            }
        }

        // Mark paths based on MST edges
        for (const auto& edge : edges) {
            int x1 = edge.first % graphSize;
            int y1 = edge.first / graphSize;
            int x2 = edge.second % graphSize;
            int y2 = edge.second / graphSize;

            // Convert graph nodes to canvas positions
            int cx1 = x1 * 2 + 1;
            int cy1 = y1 * 2 + 1;
            int cx2 = x2 * 2 + 1;
            int cy2 = y2 * 2 + 1;

            // Mark cells as paths
            canvas[cy1][cx1].setPath(true); // Node 1
            canvas[cy2][cx2].setPath(true); // Node 2

            // Mark intermediate path
            if (cx1 == cx2) { // Vertical connection
                int midY = (cy1 + cy2) / 2;
                canvas[midY][cx1].setPath(true);
            } else if (cy1 == cy2) { // Horizontal connection
                int midX = (cx1 + cx2) / 2;
                canvas[cy1][midX].setPath(true);
            }
        }
    }


    void draw(sf::RenderWindow& window) {
        for (const auto& row : canvas) {
            for (const auto& cell : row) {
                if (cell.getPath()) { // Only draw paths (white)
                    sf::RectangleShape cellShape(sf::Vector2f(cellSize - 1, cellSize - 1));
                    cellShape.setPosition(cell.getPosition().first * cellSize,
                                        cell.getPosition().second * cellSize);
                    cellShape.setFillColor(sf::Color::White);
                    window.draw(cellShape);

                }
            }
        }
    }


    std::vector<std::vector<Cell>>& getCells() {
        return canvas;
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif
