#pragma once
#include <vector>
#include <iostream>

using namespace std;

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

    bool operator==(const Edge& other) const {
        return u == other.u && v == other.v && weight == other.weight;
    }

    bool operator!=(const Edge& other) const {
        return !(*this == other);
    }
};

class Graph {
private:
    int vertices;
    vector<Edge> edges;
    vector<vector<pair<int, int>>> adjacencyList;

public:
    Graph(int V);
    void addEdge(int u, int v, int weight);
    int getVerticesCount() const;
    const vector<Edge>& getEdges() const;
    const vector<vector<pair<int, int>>>& getAdjacencyList() const;
    void printGraph() const;
};