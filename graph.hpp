#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <random>
#include <vector>
#include <limits>
#include <iostream>
#include <iomanip>

class Graph {
private:
    static const int SIZE = 20;  // nxn lattice
    std::vector<std::vector<double>> horizontalEdges;  // horizontal edges between vertices
    std::vector<std::vector<double>> verticalEdges;    // vertical edges between vertices
    std::mt19937 rng;

public:
    Graph() : rng(std::random_device{}()),
              horizontalEdges(SIZE, std::vector<double>(SIZE - 1)),
              verticalEdges(SIZE - 1, std::vector<double>(SIZE)) {
        // Initialize random weights
        std::uniform_real_distribution<double> dist(1.0, 10.0);
        
        // Initialize horizontal edges
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE - 1; j++) {
                horizontalEdges[i][j] = dist(rng);
            }
        }
        
        // Initialize vertical edges
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE; j++) {
                verticalEdges[i][j] = dist(rng);
            }
        }
    }

    double getEdgeWeight(int fromNode, int toNode) const {
        int fromRow = fromNode / SIZE;
        int fromCol = fromNode % SIZE;
        int toRow = toNode / SIZE;
        int toCol = toNode % SIZE;

        if (fromRow == toRow) {  // horizontal edge
            int minCol = std::min(fromCol, toCol);
            return horizontalEdges[fromRow][minCol];
        } else if (fromCol == toCol) {  // vertical edge
            int minRow = std::min(fromRow, toRow);
            return verticalEdges[minRow][fromCol];
        }
        return std::numeric_limits<double>::infinity();
    }

    int getSize() const {
        return SIZE * SIZE;
    }

    void printGraph() const {
        // Print horizontal edges
        for (int i = 0; i < SIZE; i++) {
            // Print vertices and horizontal connections
            for (int j = 0; j < SIZE; j++) {
                std::cout << "o";
                if (j < SIZE - 1) {
                    std::cout << std::fixed << std::setprecision(1) << "—" << horizontalEdges[i][j] << "—";
                }
            }
            std::cout << "\n";
            
            // Print vertical connections
            if (i < SIZE - 1) {
                for (int j = 0; j < SIZE; j++) {
                    std::cout << "|" << std::fixed << std::setprecision(1) << verticalEdges[i][j];
                    if (j < SIZE - 1) {
                        std::cout << "   ";
                    }
                }
                std::cout << "\n";
            }
        }
    }

    // Prim's algorithm to find Minimum Spanning Tree
    std::vector<std::pair<int, int>> primMST() {
        std::vector<bool> visited(SIZE * SIZE, false);
        std::vector<double> key(SIZE * SIZE, std::numeric_limits<double>::infinity());
        std::vector<int> parent(SIZE * SIZE, -1);
        std::vector<std::pair<int, int>> mst;

        key[0] = 0;  // Start from node 0

        for (int count = 0; count < SIZE * SIZE; count++) {
            // Find minimum key vertex
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

            if (parent[u] != -1) {
                mst.push_back({parent[u], u});
            }

            // Check adjacent vertices
            int row = u / SIZE;
            int col = u % SIZE;

            // Check all possible neighbors
            if (row > 0) { // Up
                int v = (row - 1) * SIZE + col;
                double weight = getEdgeWeight(u, v);
                if (!visited[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
            if (row < SIZE - 1) { // Down
                int v = (row + 1) * SIZE + col;
                double weight = getEdgeWeight(u, v);
                if (!visited[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
            if (col > 0) { // Left
                int v = row * SIZE + (col - 1);
                double weight = getEdgeWeight(u, v);
                if (!visited[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
            if (col < SIZE - 1) { // Right
                int v = row * SIZE + (col + 1);
                double weight = getEdgeWeight(u, v);
                if (!visited[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }

        return mst;
    }
};

#endif
