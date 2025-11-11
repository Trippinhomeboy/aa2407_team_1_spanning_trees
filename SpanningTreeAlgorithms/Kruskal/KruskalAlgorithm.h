#pragma once
#include "../SpanninTreeAlgorithm/SpanningTreeAlgorithm.h"
#include "../Graph/Graph.h"

class KruskalAlgorithm : public SpanningTreeAlgorithm {
public:
    vector<Edge> findMST(const Graph& graph) override;
    string getName() const override { return "Kruskal's Algorithm"; }
};