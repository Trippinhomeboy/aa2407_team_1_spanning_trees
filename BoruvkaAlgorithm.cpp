#include "BoruvkaAlgorithm.h"
#include <climits>
#include <algorithm>

BoruvkaAlgorithm::UnionFind::UnionFind(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

int BoruvkaAlgorithm::UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void BoruvkaAlgorithm::UnionFind::unite(int x, int y) {
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
    }
}

bool BoruvkaAlgorithm::UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}

SpanningTreeResult BoruvkaAlgorithm::execute(const Graph& graph) {
    SpanningTreeResult result;
    int V = graph.getVerticesCount();
    const std::vector<Edge>& edges = graph.getEdges();

    UnionFind uf(V);

    // Вектор для хранения самого дешевого ребра для каждого компонента
    std::vector<int> cheapest(V, -1);

    int numTrees = V;
    result.totalWeight = 0;

    while (numTrees > 1) {
        // Сбрасываем массив cheapest
        std::fill(cheapest.begin(), cheapest.end(), -1);

        // Проходим по всем ребрам и находим самое дешевое ребро для каждого компонента
        for (int i = 0; i < edges.size(); ++i) {
            const Edge& edge = edges[i];
            int set1 = uf.find(edge.from);
            int set2 = uf.find(edge.to);

            if (set1 == set2) continue;

            // Обновляем cheapest для set1 (ИСПРАВЛЕННАЯ СТРОКА)
            if (cheapest[set1] == -1 || edges[cheapest[set1]].weight > edge.weight) {
                cheapest[set1] = i;
            }

            // Обновляем cheapest для set2 (ИСПРАВЛЕННАЯ СТРОКА)
            if (cheapest[set2] == -1 || edges[cheapest[set2]].weight > edge.weight) {
                cheapest[set2] = i;
            }
        }

        // Добавляем найденные ребра в остовное дерево
        bool edgeAdded = false;
        for (int i = 0; i < V; ++i) {
            if (cheapest[i] != -1) {
                const Edge& edge = edges[cheapest[i]];
                int set1 = uf.find(edge.from);
                int set2 = uf.find(edge.to);

                if (set1 == set2) continue;

                result.edges.push_back(edge);
                result.totalWeight += edge.weight;
                uf.unite(set1, set2);
                numTrees--;
                edgeAdded = true;
            }
        }

        // Защита от бесконечного цикла для несвязных графов
        if (!edgeAdded) {
            break;
        }
    }

    return result;
}