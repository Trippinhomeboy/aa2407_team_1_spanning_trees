//
// Created by Егор Резников on 11.11.2025.
//

#include "ReverseDeleteAlgorithm.h"

#include <algorithm>

using namespace std;

vector<Edge> ReverseDeleteAlgorithm::findMST(const Graph& graph) {
    int V = graph.getVerticesCount();
    vector<Edge> mst;
    vector<Edge> allEdges = graph.getEdges();

    // Если граф пустой или с одной вершиной
    if (V <= 1) return mst;

    // Сортируем ребра по убыванию веса
    sort(allEdges.begin(), allEdges.end(), [](const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    });

    // Начинаем с полного графа и удаляем ребра
    vector<Edge> currentEdges = allEdges;

    for (const Edge& edge : allEdges) {
        // Временно удаляем ребро
        vector<Edge> tempEdges;
        for (const Edge& e : currentEdges) {
            if (e != edge) {
                tempEdges.push_back(e);
            }
        }

        // Проверяем, остается ли граф связным без этого ребра
        if (isConnected(graph, tempEdges, V)) {
            currentEdges = tempEdges; // Удаляем ребро
        }
    }

    return currentEdges;
}

bool ReverseDeleteAlgorithm::isConnected(const Graph& graph, const vector<Edge>& edges, int totalVertices) {
    if (totalVertices == 0) return true;

    // Создаем список смежности из оставшихся ребер
    vector<vector<pair<int, int>>> adjList(totalVertices);
    for (const Edge& edge : edges) {
        adjList[edge.u].emplace_back(edge.v, edge.weight);
        adjList[edge.v].emplace_back(edge.u, edge.weight);
    }

    // Проверяем связность с помощью DFS
    vector<bool> visited(totalVertices, false);
    DFS(adjList, 0, visited);

    // Если все вершины посещены - граф связный
    for (int i = 0; i < totalVertices; i++) {
        if (!visited[i]) return false;
    }
    return true;
}

void ReverseDeleteAlgorithm::DFS(const vector<vector<pair<int, int>>>& adjList, int vertex, vector<bool>& visited) {
    visited[vertex] = true;
    for (const auto& neighbor : adjList[vertex]) {
        if (!visited[neighbor.first]) {
            DFS(adjList, neighbor.first, visited);
        }
    }
}