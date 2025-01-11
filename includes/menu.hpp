#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#define ITEMS 5

class Menu {
public:
    Menu();
    ~Menu();
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressed();
    bool is_drawn;

private:
    sf::Font font;
    sf::Text menu[ITEMS];
    sf::Text title;
    int selected_index;
};

#endif