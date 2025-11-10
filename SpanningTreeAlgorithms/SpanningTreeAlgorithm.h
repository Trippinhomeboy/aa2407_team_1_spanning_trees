#pragma once
#include "Graph.h"
#include <chrono>
#include <string>

struct SpanningTreeResult {
    std::vector<Edge> edges;
    int totalWeight;
    double executionTime;
    std::string algorithmName;

    SpanningTreeResult() : totalWeight(0), executionTime(0.0) {}

    bool isValid(const Graph& graph) const;
    void print() const;
};

class SpanningTreeAlgorithm {
protected:
    virtual SpanningTreeResult execute(const Graph& graph) = 0;

public:
    virtual ~SpanningTreeAlgorithm() = default;

    SpanningTreeResult findSpanningTree(const Graph& graph);
    virtual std::string getName() const = 0;
    virtual std::string getTimeComplexity() const = 0;
    virtual std::string getSpaceComplexity() const = 0;

protected:
    void validateGraph(const Graph& graph) const;
    int calculateTotalWeight(const std::vector<Edge>& edges) const;
};