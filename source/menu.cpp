#include <iostream>
#include "menu.hpp"

Menu::Menu()
{
    if(!font.loadFromFile("assets/Tiny5-Regular.ttf"))
    {
        std::cout << "Error loading font\n";
    }

    float width = 400;
    float height = 400;

    // Dozwolone rozmiary
    const int sizes[3] = {5, 10, 20};

    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setScale(1.5f, 1.5f); 
    title.setString("Maze generator");
    title.setPosition(sf::Vector2f(10, height / (ITEMS + 1) * 0.25));

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Green);
    menu[0].setString("Pick size of the maze");
    menu[0].setScale(0.8f, 0.8f);  
    menu[0].setPosition(sf::Vector2f(10, height / (ITEMS + 1) * 1));

    // Tworzymy opcję dla każdego rozmiaru
    for(int i = 0; i < 3; i++) {
        menu[i + 1].setFont(font);
        menu[i + 1].setFillColor(sf::Color::White);
        menu[i + 1].setString(std::to_string(sizes[i]) + "x" + std::to_string(sizes[i]));
        menu[i + 1].setScale(0.8f, 0.8f);  
        menu[i + 1].setPosition(sf::Vector2f(10, height / (ITEMS + 1) * (i + 2)));
    }

    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("Exit");
    menu[4].setScale(0.8f, 0.8f);  
    menu[4].setPosition(sf::Vector2f(10, height / (ITEMS + 1) * 5));

    selected_index = 0;
    is_drawn = false;
}

Menu::~Menu(){}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(title);
    for (int i = 0; i < ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()
{
    if (selected_index - 1 >= 0)
    {
        menu[selected_index].setFillColor(sf::Color::White);
        selected_index--;
        menu[selected_index].setFillColor(sf::Color::Green);
    }
}

void Menu::moveDown()
{
    if (selected_index + 1 < ITEMS)
    {
        menu[selected_index].setFillColor(sf::Color::White);
        selected_index++;
        menu[selected_index].setFillColor(sf::Color::Green);
    }
}

int Menu::getPressed()
{
    return selected_index;
}