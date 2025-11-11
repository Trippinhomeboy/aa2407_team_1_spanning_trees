
#include "KruskalAlgorithm.h"
#include <algorithm>

vector<Edge> KruskalAlgorithm::findMST(const Graph& graph) {
    int V = graph.getVerticesCount();
    vector<Edge> edges = graph.getEdges();
    vector<Edge> mst;
    
    if (V == 0 || V == 1) {
        return mst;
    }
    
    sort(edges.begin(), edges.end());
    
    vector<int> parent(V);
    vector<int> rank(V, 0);
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }
    
    auto find = [&](int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    };
    
    auto unite = [&](int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            return true;
        }
        return false;
    };
    
    for (const Edge& edge : edges) {
        if (unite(edge.u, edge.v)) {
            mst.push_back(edge);
            if (mst.size() == V - 1) {
                break;
            }
        }
    }
    
    return mst;
}