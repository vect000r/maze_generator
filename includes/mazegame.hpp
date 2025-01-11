#include <SFML/Graphics.hpp>
#include "graph.hpp"
#include "canvas.hpp"
#include "menu.hpp"
#include <iostream>

class MazeGame {
private:
    Canvas canvas;
    Graph graph;
    Menu menu;
    sf::RenderWindow window;
    std::vector<std::pair<int, int>> mst;
    int size;
    bool start = false;

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if (menu.is_drawn) {
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.moveUp();
                    } else if (event.key.code == sf::Keyboard::Down) {
                        menu.moveDown();
                    } else if (event.key.code == sf::Keyboard::Return) {
                        try {  // Dodaj obsługę wyjątków
                            std::cout << "Selected option: " << menu.getPressed() << std::endl;
                            switch(menu.getPressed()) {
                                case 1:  // "5x5"
                                    std::cout << "Creating graph 5x5" << std::endl;
                                    size = 5;
                                    graph = Graph(size);
                                    std::cout << "Creating canvas 5x5" << std::endl;
                                    canvas = Canvas(size);
                                    std::cout << "Generating maze" << std::endl;
                                    generateMaze();
                                    start = true;
                                    menu.is_drawn = false;
                                    break;
                                case 2:  // "10x10"
                                    std::cout << "Creating graph 10x10" << std::endl;
                                    size = 10;
                                    graph = Graph(size);
                                    std::cout << "Creating canvas 10x10" << std::endl;
                                    canvas = Canvas(size);
                                    std::cout << "Generating maze" << std::endl;
                                    generateMaze();
                                    start = true;
                                    menu.is_drawn = false;
                                    break;
                                case 3:  // "20x20"
                                    std::cout << "Creating graph 20x20" << std::endl;
                                    size = 20;
                                    graph = Graph(size);
                                    std::cout << "Creating canvas 20x20" << std::endl;
                                    canvas = Canvas(size);
                                    std::cout << "Generating maze" << std::endl;
                                    generateMaze();
                                    start = true;
                                    menu.is_drawn = false;
                                    break;
                                case 4:
                                    window.close();
                                    break;
                            }
                        } catch (const std::exception& e) {
                            std::cout << "Error: " << e.what() << std::endl;
                        }
                    }
                }
            }
        }
    }

    void render() {
        window.clear();
        canvas.draw(window);
        window.display();
    }

    void generateMaze() {
        if (size == 0) return;  // zabezpieczenie
        mst = graph.primMST();
        canvas.setMST(mst, size);
    }

    void debugPrint() {
        // Funkcja służąca do debugowania ścieżek i krawędzi
        for (int i = 0; i < canvas.getCells().size(); i++) {
            for (int j = 0; j < canvas.getCells()[i].size(); j++) {
                std::cout << canvas.getCells()[i][j].getPath() << " ";
            }
            std::cout << "\n";
        }

        for (const auto& edge : mst) {
            std::cout << "(" << edge.first << ", " << edge.second << ")\n";
        }
    }

public:
    MazeGame() : canvas(5), window(sf::VideoMode(800, 800), "Maze") {  // stały rozmiar okna
        menu.is_drawn = true;
        size = 5;  // domyślny rozmiar
    }
    
    void run() {
        while (window.isOpen()) {
            processEvents();
            
            window.clear(sf::Color::Black);
            
            if (menu.is_drawn) {
                menu.draw(window);
            } else {
                // Wycentruj canvas w oknie
                int xOffset = (800 - canvas.getWidth()) / 2;
                int yOffset = (800 - canvas.getHeight()) / 2;
                
                // Ustaw widok na środek
                sf::View view = window.getDefaultView();
                view.setCenter(400, 400);
                window.setView(view);
                
                canvas.draw(window);
            }
            
            window.display();
        }
    }
};