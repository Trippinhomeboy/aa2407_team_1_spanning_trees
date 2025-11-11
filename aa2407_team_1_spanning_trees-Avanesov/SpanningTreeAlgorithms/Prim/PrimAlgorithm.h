#pragma once
#include "../SpanninTreeAlgorithm/SpanningTreeAlgorithm.h"

class PrimAlgorithm : public SpanningTreeAlgorithm {
public:
    vector<Edge> findMST(const Graph& graph) override;
    string getName() const override { return "Prim's Algorithm"; }
};