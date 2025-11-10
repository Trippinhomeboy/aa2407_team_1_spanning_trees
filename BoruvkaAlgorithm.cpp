#include "BoruvkaAlgorithm.h"
#include "Graph.h" // Предполагается, что у вас есть класс Graph
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

BoruvkaResult BoruvkaAlgorithm::findMST(const Graph& graph) {
    BoruvkaResult result;
    result.success = false;

    try {
        // Получаем информацию о графе
        int V = graph.getVertexCount(); // Предполагаем, что такой метод есть в Graph
        const auto& adjMatrix = graph.getAdjacencyMatrix(); // И такой метод

        if (V == 0) {
            result.message = "Граф пуст";
            return result;
        }

        vector<int> component(V);
        for (int i = 0; i < V; i++) {
            component[i] = i;
        }

        vector<Edge> MST;
        int numComponents = V;

        // Основной цикл алгоритма Борувки
        while (numComponents > 1) {
            vector<Edge> minEdge(V, Edge(-1, -1, INT_MAX));

            // Поиск минимальных ребер для каждой компоненты
            for (int u = 0; u < V; u++) {
                for (int v = u + 1; v < V; v++) {
                    if (adjMatrix[u][v] != 0) {
                        int compU = component[u];
                        int compV = component[v];

                        if (compU != compV) {
                            if (adjMatrix[u][v] < minEdge[compU].weight) {
                                minEdge[compU] = Edge(u, v, adjMatrix[u][v]);
                            }
                            if (adjMatrix[u][v] < minEdge[compV].weight) {
                                minEdge[compV] = Edge(u, v, adjMatrix[u][v]);
                            }
                        }
                    }
                }
            }

            // Добавление найденных ребер в MST
            bool edgeAdded = false;
            for (int i = 0; i < V; i++) {
                if (minEdge[i].weight != INT_MAX) {
                    int u = minEdge[i].src;
                    int v = minEdge[i].dest;
                    int compU = component[u];
                    int compV = component[v];

                    if (compU != compV) {
                        MST.push_back(minEdge[i]);

                        // Объединение компонент
                        int oldComp = max(compU, compV);
                        int newComp = min(compU, compV);

                        for (int j = 0; j < V; j++) {
                            if (component[j] == oldComp) {
                                component[j] = newComp;
                            }
                        }

                        numComponents--;
                        edgeAdded = true;
                    }
                }
            }

            // Защита от бесконечного цикла
            if (!edgeAdded) {
                result.message = "Граф несвязный - невозможно построить MST";
                return result;
            }
        }

        // Расчет общего веса
        result.totalWeight = 0;
        for (const Edge& edge : MST) {
            result.totalWeight += edge.weight;
        }

        result.mstEdges = MST;
        result.success = true;
        result.message = "MST успешно построено";

    }
    catch (const exception& e) {
        result.message = "Ошибка при выполнении алгоритма: " + string(e.what());
    }

    return result;
}

BoruvkaResult BoruvkaAlgorithm::findMSTWithTimeMeasurement(const Graph& graph) {
    auto start = high_resolution_clock::now();

    BoruvkaResult result = findMST(graph);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    result.executionTimeMicroseconds = duration.count();

    return result;
}

string BoruvkaAlgorithm::resultToString(const BoruvkaResult& result) {
    string output;

    if (!result.success) {
        output = "Ошибка: " + result.message;
        return output;
    }

    output = "Минимальное остовное дерево:\n";
    output += "Количество ребер: " + to_string(result.mstEdges.size()) + "\n";
    output += "Ребра MST:\n";

    for (const Edge& edge : result.mstEdges) {
        output += to_string(edge.src) + " - " + to_string(edge.dest) +
            " (вес: " + to_string(edge.weight) + ")\n";
    }

    output += "Общий вес: " + to_string(result.totalWeight) + "\n";
    output += "Время выполнения: " + to_string(result.executionTimeMicroseconds) +
        " микросекунд";

    return output;
}

void BoruvkaAlgorithm::printResult(const BoruvkaResult& result) {
    cout << resultToString(result) << endl;
}

// Вспомогательные приватные методы
int BoruvkaAlgorithm::findComponent(const vector<int>& component, int vertex) {
    return component[vertex];
}

void BoruvkaAlgorithm::unionComponents(vector<int>& component, int comp1, int comp2) {
    int oldComp = max(comp1, comp2);
    int newComp = min(comp1, comp2);

    for (size_t i = 0; i < component.size(); i++) {
        if (component[i] == oldComp) {
            component[i] = newComp;
        }
    }
}