#include "cell.hpp"

Cell::Cell() : sf::RectangleShape(sf::Vector2f(size, size)) {
    setFillColor(sf::Color::White);
}

std::pair<int, int> Cell::getPosition() const {
    return position;
}

void Cell::setPosition(std::pair<int, int> newPosition) {
    position = newPosition;
    sf::RectangleShape::setPosition(position.first * size, position.second * size);
}

void Cell::setPath(bool path) {
    isPath = path;
    setFillColor(isPath ? sf::Color::White : sf::Color::Black);
}

bool Cell::getPath() const {
    return isPath;
}
