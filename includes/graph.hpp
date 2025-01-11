#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <random>
#include <vector>
#include <utility>

class Graph {
private:
    int SIZE;
    std::vector<std::vector<double>> horizontalEdges;
    std::vector<std::vector<double>> verticalEdges;
    std::mt19937 rng;

public:
    Graph(int size = 20);
    double getEdgeWeight(int fromNode, int toNode) const;
    std::vector<std::pair<int, int>> primMST();
    int getSize() const;
};

#endif
