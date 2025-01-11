#include <random>
#include <vector>
#include <limits>
#include <iostream>
#include <iomanip>
#include "graph.hpp"

Graph::Graph(int size) : SIZE(size), rng(std::random_device{}()),
          horizontalEdges(size, std::vector<double>(size - 1)),
          verticalEdges(size - 1, std::vector<double>(size)) {
    
    std::uniform_real_distribution<double> dist(1.0, 10.0);
    
    // poziome krawędzie
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            horizontalEdges[i][j] = dist(rng);
        }
    }
    
    // pionowe krawędzie
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE; j++) {
            verticalEdges[i][j] = dist(rng);
        }
    }
}

double Graph::getEdgeWeight(int fromNode, int toNode) const {
    // Sprawdzamy czy węzły są w zakresie
    if (fromNode < 0 || fromNode >= SIZE * SIZE || toNode < 0 || toNode >= SIZE * SIZE) {
        return std::numeric_limits<double>::infinity();
    }

    int fromRow = fromNode / SIZE;
    int fromCol = fromNode % SIZE;
    int toRow = toNode / SIZE;
    int toCol = toNode % SIZE;

    // Sprawdzamy czy węzły są sąsiadami
    if (abs(fromRow - toRow) + abs(fromCol - toCol) != 1) {
        return std::numeric_limits<double>::infinity();
    }

    if (fromRow == toRow) {  // pozioma krawędź
        int minCol = std::min(fromCol, toCol);
        return horizontalEdges[fromRow][minCol];
    } else if (fromCol == toCol) {  // pionowa krawędź
        int minRow = std::min(fromRow, toRow);
        return verticalEdges[minRow][fromCol];
    }
    return std::numeric_limits<double>::infinity();
}

std::vector<std::pair<int, int>> Graph::primMST() {
    std::vector<bool> visited(SIZE * SIZE, false);
    std::vector<double> key(SIZE * SIZE, std::numeric_limits<double>::infinity());
    std::vector<int> parent(SIZE * SIZE, -1);
    std::vector<std::pair<int, int>> mst;

    key[0] = 0;

    for (int count = 0; count < SIZE * SIZE; count++) {
        // Znajdź wierzchołek o najmniejszej wadze
        int u = -1;
        double min = std::numeric_limits<double>::infinity();
        for (int v = 0; v < SIZE * SIZE; v++) {
            if (!visited[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        // Dodaj krawędź do MST
        if (parent[u] != -1) {
            mst.push_back({parent[u], u});
        }

        // Sprawdź sąsiadów
        int row = u / SIZE;
        int col = u % SIZE;

        // Sprawdź wszystkich 4 sąsiadów
        std::vector<std::pair<int, int>> neighbors = {
            {row - 1, col}, // góra
            {row + 1, col}, // dół
            {row, col - 1}, // lewo
            {row, col + 1}  // prawo
        };

        for (const auto& [r, c] : neighbors) {
            if (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
                int v = r * SIZE + c;
                double weight = getEdgeWeight(u, v);
                if (!visited[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }
    }

    return mst;
}

int Graph::getSize() const {
    return SIZE;
}


