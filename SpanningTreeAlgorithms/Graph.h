#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <stdexcept>
#include <memory>
#include <fstream>
#include <queue>

struct Edge {
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

    bool operator==(const Edge& other) const {
        return from == other.from && to == other.to && weight == other.weight;
    }
};

class Graph {
private:
    int vertices;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<Edge> edges;
    mutable std::vector<std::vector<int>> adjacencyMatrix;
    mutable bool matrixCached = false;

    void buildAdjacencyMatrix() const;

public:
    Graph(int v);

    
    void addEdge(int from, int to, int weight);
    void addDirectedEdge(int from, int to, int weight);

    
    int getVerticesCount() const { return vertices; }
    int getEdgesCount() const { return edges.size(); }
    const std::vector<Edge>& getEdges() const { return edges; }
    const std::vector<Edge>& getAdjacentEdges(int vertex) const;
    const std::vector<std::vector<int>>& getAdjacencyMatrix() const;

    
    bool hasEdge(int from, int to) const;
    int getEdgeWeight(int from, int to) const;

    
    static Graph generateRandomGraph(int vertices, int edges, int maxWeight = 100);
    static Graph generateCompleteGraph(int vertices, int maxWeight = 100);
    static Graph generateSparseGraph(int vertices, double density = 0.1, int maxWeight = 100);
    static Graph generateDenseGraph(int vertices, double density = 0.9, int maxWeight = 100);
    static Graph generateTree(int vertices, int maxWeight = 100);
    static Graph generateGridGraph(int rows, int cols, int maxWeight = 100);

    
    static Graph loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    
    bool isConnected() const;
    bool hasNegativeWeights() const;

    
    void printGraph() const;
    void printAdjacencyList() const;
    void printAdjacencyMatrix() const;

    
    int getTotalWeight() const;
    int getMaxDegree() const;
    int getMinDegree() const;
};