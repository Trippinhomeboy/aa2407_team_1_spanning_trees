#include "BoruvkaAlgorithm.h"
#include <climits>

vector<Edge> BoruvkaAlgorithm::findMST(const Graph& graph) {
    int V = graph.getVerticesCount();
    const auto& edges = graph.getEdges();
    vector<Edge> mst;

    if (V <= 1) return mst;

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
            }
            else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            }
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            return true;
        }
        return false;
        };

    int components = V;
    int iterations = 0;

    while (components > 1 && iterations < V) {
        iterations++;
        vector<int> cheapest(V, -1);

        for (int i = 0; i < edges.size(); i++) {
            const Edge& edge = edges[i];
            int compU = find(edge.u);
            int compV = find(edge.v);

            if (compU != compV) {
                if (cheapest[compU] == -1 || edges[cheapest[compU]].weight > edge.weight) {
                    cheapest[compU] = i;
                }
                if (cheapest[compV] == -1 || edges[cheapest[compV]].weight > edge.weight) {
                    cheapest[compV] = i;
                }
            }
        }

        bool added = false;
        for (int i = 0; i < V; i++) {
            if (cheapest[i] != -1) {
                const Edge& edge = edges[cheapest[i]];
                if (unite(edge.u, edge.v)) {
                    mst.push_back(edge);
                    components--;
                    added = true;
                }
            }
        }

        if (!added) break;
    }

    return mst;
}