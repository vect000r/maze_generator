#include <SFML/Graphics.hpp>
#include "graph.hpp"
#include "canvas.hpp"
#include <iostream>

int main() {
    
    
    Canvas my_canvas;
    Graph gr;
    
    std::vector<std::pair<int, int>> mst = gr.primMST();
    my_canvas.setMST(mst, 20);

    for (int i = 0; i < my_canvas.getCells().size(); i++) {
        for (int j = 0; j < my_canvas.getCells()[i].size(); j++) {
            std::cout << my_canvas.getCells()[i][j].getPath() << " ";
        }
        std::cout << "\n";
    }


    sf::RenderWindow window(sf::VideoMode(my_canvas.getWidth(), my_canvas.getHeight()), "Maze");


    for (const auto& edge : mst) {
        std::cout << "(" << edge.first << ", " << edge.second << ")\n";
    }
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        
        my_canvas.draw(window);
        
        
        window.display();
    }

    // intuicja:
    // chcemy miec drzewo rozpinajace grafu o losowych wagach krawędzi -> zrobione
    // siatka pikseli -> zrobione
    // TODO:
    // uzywajac siatki pikseli chcemy narysować mst na siatce

    return 0;
}