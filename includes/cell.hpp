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
    Cell();

    std::pair<int, int> getPosition() const;
    void setPosition(std::pair<int, int> newPosition);

    void setPath(bool path);
    bool getPath() const;
};

#endif
