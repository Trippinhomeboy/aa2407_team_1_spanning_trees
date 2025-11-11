#pragma once
#include "../Graph/Graph.h"
#include <vector>
#include <string>

using namespace std;

class SpanningTreeAlgorithm {
public:
    virtual ~SpanningTreeAlgorithm() = default;
    virtual vector<Edge> findMST(const Graph& graph) = 0;
    virtual string getName() const = 0;
    int calculateTotalWeight(const vector<Edge>& mst) const;
    void printMST(const vector<Edge>& mst) const;
};