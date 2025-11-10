#pragma once
#include "SpanningTreeAlgorithm.h"
#include <vector>

class BoruvkaAlgorithm : public SpanningTreeAlgorithm {
public:
    std::string getName() const override { return "Boruvka's Algorithm"; }
    std::string getTimeComplexity() const override { return "O(E log V)"; }
    std::string getSpaceComplexity() const override { return "O(V)"; }

private:
    SpanningTreeResult execute(const Graph& graph) override;

    class UnionFind {
    private:
        std::vector<int> parent;
        std::vector<int> rank;

    public:
        UnionFind(int n);
        int find(int x);
        void unite(int x, int y);
        bool connected(int x, int y);
    };
};