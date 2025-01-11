#ifndef CELL_HPP
#define CELL_HPP

#include <iomanip>
#include <SFML/Graphics.hpp>

class Cell : public sf::RectangleShape {
private:
    std::pair<int, int> position;
    bool isPath = false;
    int size = 10;

public:
    Cell() : sf::RectangleShape(sf::Vector2f(size, size)) {
        setFillColor(sf::Color::White);
    }

    std::pair<int, int> getPosition() const { return position; }
    void setPosition(std::pair<int, int> newPosition)  { 
        position = newPosition;
        sf::RectangleShape::setPosition(position.first * size, position.second * size);
    }

    void setPath(bool path) {
        isPath = path;
        setFillColor(isPath ? sf::Color::White : sf::Color::Black);
    }
    
    bool getPath() const {return isPath; }
};

#endif