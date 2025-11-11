#include "Graph.h"

Graph::Graph(int V) : vertices(V), adjacencyList(V) {}

void Graph::addEdge(int u, int v, int weight) {
    edges.emplace_back(u, v, weight);
    adjacencyList[u].emplace_back(v, weight);
    adjacencyList[v].emplace_back(u, weight);
}

int Graph::getVerticesCount() const {
    return vertices;
}

const vector<Edge>& Graph::getEdges() const {
    return edges;
}

const vector<vector<pair<int, int>>>& Graph::getAdjacencyList() const {
    return adjacencyList;
}

void Graph::printGraph() const {
    cout << "Graph with " << vertices << " vertices and " << edges.size() << " edges:\n";
    for (const auto& edge : edges) {
        cout << edge.u << " -- " << edge.v << " [weight=" << edge.weight << "]\n";
    }
}