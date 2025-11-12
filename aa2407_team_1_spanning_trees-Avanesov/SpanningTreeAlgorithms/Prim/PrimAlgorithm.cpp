#include "PrimAlgorithm.h"
#include <queue>
#include <climits>

vector<Edge> PrimAlgorithm::findMST(const Graph& graph) {
    int V = graph.getVerticesCount();
    const auto& adj = graph.getAdjacencyList();
    
    vector<Edge> mst;
    
    if (V == 0) {
        return mst;
    }
    
    if (V == 1) {
        return mst;
    }
    
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    
    using MinHeap = priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    >;
    
    MinHeap pq;
    key[0] = 0;
    pq.push({0, 0});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (inMST[u]) continue;
        inMST[u] = true;
        
        if (parent[u] != -1) {
            int weight = key[u];
            mst.emplace_back(parent[u], u, weight);
        }
        
        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }
    
    return mst;
}