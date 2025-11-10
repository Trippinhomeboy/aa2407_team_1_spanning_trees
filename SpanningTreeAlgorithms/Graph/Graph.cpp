#include "Graph.h"
#include <queue>
#include <algorithm>
#include <sstream>
#include <unordered_set>

Graph::Graph(int v) : vertices(v), adjacencyList(v) {
    if (v <= 0) throw std::invalid_argument("Number of vertices must be positive");
}

void Graph::addEdge(int from, int to, int weight) {
    if (from >= vertices || to >= vertices || from < 0 || to < 0)
        throw std::invalid_argument("Invalid vertex index");
    if (weight <= 0)
        throw std::invalid_argument("Weight must be positive");


    for (const auto& edge : adjacencyList[from]) {
        if (edge.to == to) return;
    }

    Edge edge(from, to, weight);
    edges.push_back(edge);
    adjacencyList[from].emplace_back(from, to, weight);
    adjacencyList[to].emplace_back(to, from, weight);

    matrixCached = false;
}

void Graph::addDirectedEdge(int from, int to, int weight) {
    if (from >= vertices || to >= vertices || from < 0 || to < 0)
        throw std::invalid_argument("Invalid vertex index");

    Edge edge(from, to, weight);
    edges.push_back(edge);
    adjacencyList[from].emplace_back(from, to, weight);

    matrixCached = false;
}

const std::vector<Edge>& Graph::getAdjacentEdges(int vertex) const {
    if (vertex < 0 || vertex >= vertices)
        throw std::invalid_argument("Invalid vertex index");
    return adjacencyList[vertex];
}

void Graph::buildAdjacencyMatrix() const {
    adjacencyMatrix.assign(vertices, std::vector<int>(vertices, 0));
    for (const auto& edge : edges) {
        adjacencyMatrix[edge.from][edge.to] = edge.weight;
        adjacencyMatrix[edge.to][edge.from] = edge.weight;
    }
    matrixCached = true;
}

const std::vector<std::vector<int>>& Graph::getAdjacencyMatrix() const {
    if (!matrixCached) {
        buildAdjacencyMatrix();
    }
    return adjacencyMatrix;
}

bool Graph::hasEdge(int from, int to) const {
    if (from < 0 || from >= vertices || to < 0 || to >= vertices)
        return false;


    for (const auto& edge : adjacencyList[from]) {
        if (edge.to == to) return true;
    }
    return false;
}

int Graph::getEdgeWeight(int from, int to) const {
    if (from < 0 || from >= vertices || to < 0 || to >= vertices)
        return -1;

    for (const auto& edge : adjacencyList[from]) {
        if (edge.to == to) return edge.weight;
    }
    return -1;
}


Graph Graph::generateRandomGraph(int vertices, int edgesCount, int maxWeight) {
    if (vertices <= 0) throw std::invalid_argument("Number of vertices must be positive");

    Graph graph(vertices);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDist(1, maxWeight);
    std::uniform_int_distribution<> vertexDist(0, vertices - 1);

    
    for (int i = 1; i < vertices; ++i) {
        int parent = vertexDist(gen) % i;
        graph.addEdge(parent, i, weightDist(gen));
    }

    
    int maxPossibleEdges = vertices * (vertices - 1) / 2;
    edgesCount = std::min(edgesCount, maxPossibleEdges);

    std::unordered_set<long long> usedEdges;
    for (const auto& edge : graph.edges) {
        long long key = edge.from < edge.to ?
            (static_cast<long long>(edge.from) * vertices + edge.to) :
            (static_cast<long long>(edge.to) * vertices + edge.from);
        usedEdges.insert(key);
    }

    while (graph.getEdgesCount() < edgesCount) {
        int from = vertexDist(gen);
        int to = vertexDist(gen);
        if (from != to) {
            long long key = from < to ?
                (static_cast<long long>(from) * vertices + to) :
                (static_cast<long long>(to) * vertices + from);

            if (usedEdges.find(key) == usedEdges.end()) {
                graph.addEdge(from, to, weightDist(gen));
                usedEdges.insert(key);
            }
        }
    }

    return graph;
}


Graph Graph::generateCompleteGraph(int vertices, int maxWeight) {
    Graph graph(vertices);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDist(1, maxWeight);

    for (int i = 0; i < vertices; ++i) {
        for (int j = i + 1; j < vertices; ++j) {
            graph.addEdge(i, j, weightDist(gen));
        }
    }

    return graph;
}


Graph Graph::generateSparseGraph(int vertices, double density, int maxWeight) {
    int maxEdges = vertices * (vertices - 1) / 2;
    int edgesCount = static_cast<int>(maxEdges * density);
    edgesCount = std::max(edgesCount, vertices - 1); 
    return generateRandomGraph(vertices, edgesCount, maxWeight);
}


Graph Graph::generateDenseGraph(int vertices, double density, int maxWeight) {
    int maxEdges = vertices * (vertices - 1) / 2;
    int edgesCount = static_cast<int>(maxEdges * density);
    return generateRandomGraph(vertices, edgesCount, maxWeight);
}


Graph Graph::generateTree(int vertices, int maxWeight) {
    Graph graph(vertices);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDist(1, maxWeight);

    for (int i = 1; i < vertices; ++i) {
        int parent = gen() % i;
        graph.addEdge(parent, i, weightDist(gen));
    }

    return graph;
}


Graph Graph::generateGridGraph(int rows, int cols, int maxWeight) {
    int vertices = rows * cols;
    Graph graph(vertices);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDist(1, maxWeight);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int current = i * cols + j;

           
            if (j < cols - 1) {
                graph.addEdge(current, i * cols + (j + 1), weightDist(gen));
            }

            
            if (i < rows - 1) {
                graph.addEdge(current, (i + 1) * cols + j, weightDist(gen));
            }
        }
    }

    return graph;
}


Graph Graph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);

    int vertices, edgesCount;
    file >> vertices >> edgesCount;

    Graph graph(vertices);
    for (int i = 0; i < edgesCount; ++i) {
        int from, to, weight;
        file >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }

    return graph;
}


void Graph::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);

    file << vertices << " " << edges.size() << "\n";
    for (const auto& edge : edges) {
        file << edge.from << " " << edge.to << " " << edge.weight << "\n";
    }
}


bool Graph::isConnected() const {
    if (vertices == 0) return true;

    std::vector<bool> visited(vertices, false);
    std::queue<int> q;
    int visitedCount = 0;

    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        visitedCount++;

        for (const auto& edge : adjacencyList[current]) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                q.push(edge.to);
            }
        }
    }

    return visitedCount == vertices;
}

bool Graph::hasNegativeWeights() const {
    for (const auto& edge : edges) {
        if (edge.weight < 0) return true;
    }
    return false;
}

void Graph::printGraph() const {
    std::cout << "Graph: " << vertices << " vertices, " << edges.size() << " edges\n";
    std::cout << "Total weight: " << getTotalWeight() << "\n";
    std::cout << "Connected: " << (isConnected() ? "Yes" : "No") << "\n";
}

void Graph::printAdjacencyList() const {
    std::cout << "Adjacency List:\n";
    for (int i = 0; i < vertices; ++i) {
        std::cout << i << ": ";
        for (const auto& edge : adjacencyList[i]) {
            if (edge.from == i) {
                std::cout << edge.to << "(" << edge.weight << ") ";
            }
        }
        std::cout << "\n";
    }
}

void Graph::printAdjacencyMatrix() const {
    const auto& matrix = getAdjacencyMatrix();
    std::cout << "Adjacency Matrix:\n  ";

    for (int i = 0; i < vertices; ++i) std::cout << i << " ";
    std::cout << "\n";

    for (int i = 0; i < vertices; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < vertices; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int Graph::getTotalWeight() const {
    int total = 0;
    for (const auto& edge : edges) {
        total += edge.weight;
    }
    return total;
}

int Graph::getMaxDegree() const {
    int maxDegree = 0;
    for (int i = 0; i < vertices; ++i) {
        maxDegree = std::max(maxDegree, static_cast<int>(adjacencyList[i].size()));
    }
    return maxDegree;
}

int Graph::getMinDegree() const {
    if (vertices == 0) return 0;
    int minDegree = adjacencyList[0].size();
    for (int i = 1; i < vertices; ++i) {
        minDegree = std::min(minDegree, static_cast<int>(adjacencyList[i].size()));
    }
    return minDegree;
}