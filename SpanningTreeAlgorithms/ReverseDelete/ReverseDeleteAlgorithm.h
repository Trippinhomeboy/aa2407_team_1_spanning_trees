//
// Created by Егор Резников on 11.11.2025.
//

#ifndef AA2407_TEAM_1_SPANNING_TREES_REVERSEDELETE_H
#define AA2407_TEAM_1_SPANNING_TREES_REVERSEDELETE_H
#pragma once
#include "../SpanninTreeAlgorithm/SpanningTreeAlgorithm.h"
#include <vector>
#include <string>
#include <algorithm>

class ReverseDeleteAlgorithm : public SpanningTreeAlgorithm {
public:
    vector<Edge> findMST(const Graph& graph) override;
    string getName() const override { return "Reverse Delete"; }

private:
    bool isConnected(const Graph& graph, const vector<Edge>& edges, int totalVertices);
    void DFS(const vector<vector<pair<int, int>>>& adjList, int vertex, vector<bool>& visited);
};


#endif //AA2407_TEAM_1_SPANNING_TREES_REVERSEDELETE_H