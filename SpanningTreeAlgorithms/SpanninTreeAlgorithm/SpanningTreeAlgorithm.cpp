#include "SpanningTreeAlgorithm.h"
#include <iostream>

using namespace std;

int SpanningTreeAlgorithm::calculateTotalWeight(const vector<Edge>& mst) const {
    int total = 0;
    for (const auto& edge : mst) {
        total += edge.weight;
    }
    return total;
}

void SpanningTreeAlgorithm::printMST(const vector<Edge>& mst) const {
    if (mst.empty()) {
        cout << "Spanning tree is empty (no edges)\n";
        return;
    }

    cout << "Minimum Spanning Tree (" << getName() << "):\n";
    for (const auto& edge : mst) {
        cout << edge.u << " -- " << edge.v << " [weight=" << edge.weight << "]\n";
    }
    cout << "Total weight: " << calculateTotalWeight(mst) << "\n";
}