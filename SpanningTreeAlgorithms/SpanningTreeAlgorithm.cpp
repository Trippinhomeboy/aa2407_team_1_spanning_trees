#include "SpanningTreeAlgorithm.h"

SpanningTreeResult SpanningTreeAlgorithm::findSpanningTree(const Graph& graph) {
    auto start = std::chrono::high_resolution_clock::now();

    validateGraph(graph);
    SpanningTreeResult result = execute(graph);

    auto end = std::chrono::high_resolution_clock::now();
    result.executionTime = std::chrono::duration<double>(end - start).count();
    result.algorithmName = getName();
    result.totalWeight = calculateTotalWeight(result.edges);

    return result;
}

void SpanningTreeAlgorithm::validateGraph(const Graph& graph) const {
    if (graph.getVerticesCount() == 0) {
        throw std::invalid_argument("Graph has no vertices");
    }
    if (!graph.isConnected()) {
        throw std::invalid_argument("Graph is not connected");
    }
    if (graph.hasNegativeWeights()) {
        throw std::invalid_argument("Graph has negative weights");
    }
}

int SpanningTreeAlgorithm::calculateTotalWeight(const std::vector<Edge>& edges) const {
    int total = 0;
    for (const auto& edge : edges) {
        total += edge.weight;
    }
    return total;
}

bool SpanningTreeResult::isValid(const Graph& graph) const {
    if (edges.size() != graph.getVerticesCount() - 1) return false;

    // Проверяем, что все вершины покрыты
    std::vector<bool> visited(graph.getVerticesCount(), false);
    for (const auto& edge : edges) {
        visited[edge.from] = true;
        visited[edge.to] = true;
    }

    for (bool v : visited) {
        if (!v) return false;
    }

    return true;
}

void SpanningTreeResult::print() const {
    std::cout << "=== " << algorithmName << " ===\n";
    std::cout << "Total weight: " << totalWeight << "\n";
    std::cout << "Execution time: " << std::fixed << std::setprecision(6)
        << executionTime << " seconds\n";
    std::cout << "Edges in spanning tree (" << edges.size() << "):\n";

    for (const auto& edge : edges) {
        std::cout << "  " << edge.from << " -- " << edge.to
            << " [weight=" << edge.weight << "]\n";
    }
    std::cout << "\n";
}