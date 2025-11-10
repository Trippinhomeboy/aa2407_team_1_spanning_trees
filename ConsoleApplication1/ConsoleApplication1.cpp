#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <windows.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Структура для представления ребра
struct Edge {
    int src, dest, weight;
};

// Структура для представления графа
class Graph {
    int V; // Количество вершин
    vector<vector<int>> adjMatrix; // Матрица смежности

public:
    Graph(int vertices) : V(vertices) {
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    // Установка матрицы смежности
    void setAdjacencyMatrix(const vector<vector<int>>& matrix) {
        adjMatrix = matrix;
    }

    // Поиск минимального остовного дерева алгоритмом Борувки
    void boruvkaMST() {
        auto start = high_resolution_clock::now(); // Начало замера времени

        // Массив для хранения компонент связности
        vector<int> component(V);
        // Изначально каждая вершина - отдельная компонента
        for (int i = 0; i < V; i++) {
            component[i] = i;
        }

        // Вектор для хранения ребер MST
        vector<Edge> MST;

        // Количество компонент связности
        int numComponents = V;

        cout << "Построение минимального остовного дерева алгоритмом Борувки:\n";

        // Пока есть более одной компоненты
        while (numComponents > 1) {
            // Вектор для хранения минимальных ребер для каждой компоненты
            vector<Edge> minEdge(V, { -1, -1, INT_MAX });

            // Поиск минимального ребра для каждой компоненты
            for (int u = 0; u < V; u++) {
                for (int v = 0; v < V; v++) {
                    if (adjMatrix[u][v] != 0) { // Если ребро существует
                        int compU = component[u];
                        int compV = component[v];

                        // Если вершины в разных компонентах
                        if (compU != compV) {
                            // Обновляем минимальное ребро для компоненты compU
                            if (adjMatrix[u][v] < minEdge[compU].weight) {
                                minEdge[compU] = { u, v, adjMatrix[u][v] };
                            }
                            // Обновляем минимальное ребро для компоненты compV
                            if (adjMatrix[u][v] < minEdge[compV].weight) {
                                minEdge[compV] = { u, v, adjMatrix[u][v] };
                            }
                        }
                    }
                }
            }

            // Добавляем найденные минимальные ребра в MST
            for (int i = 0; i < V; i++) {
                if (minEdge[i].weight != INT_MAX) {
                    int u = minEdge[i].src;
                    int v = minEdge[i].dest;
                    int compU = component[u];
                    int compV = component[v];

                    // Если вершины еще в разных компонентах
                    if (compU != compV) {
                        MST.push_back(minEdge[i]);

                        // Объединяем компоненты
                        int oldComp = max(compU, compV);
                        int newComp = min(compU, compV);

                        for (int j = 0; j < V; j++) {
                            if (component[j] == oldComp) {
                                component[j] = newComp;
                            }
                        }

                        numComponents--;

                        cout << "Добавлено ребро: " << u << " - " << v
                            << " (вес: " << minEdge[i].weight << ")\n";
                    }
                }
            }
        }

        auto stop = high_resolution_clock::now(); // Конец замера времени
        auto duration = duration_cast<microseconds>(stop - start);

        // Вывод результата
        cout << "\nМинимальное остовное дерево содержит следующие ребра:\n";
        int totalWeight = 0;
        for (const Edge& edge : MST) {
            cout << edge.src << " - " << edge.dest << " (вес: " << edge.weight << ")\n";
            totalWeight += edge.weight;
        }
        cout << "Общий вес MST: " << totalWeight << endl;

        // Вывод времени выполнения
        cout << "\nВремя выполнения алгоритма Борувки: "
            << duration.count() << " микросекунд ("
            << duration.count() / 1000.0 << " миллисекунд)" << endl;
    }

    // Вывод матрицы смежности
    void printAdjacencyMatrix() {
        cout << "Матрица смежности:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    SetConsoleOutputCP(1251);
    // Пример графа с 5 вершинами
    int V = 5;
    Graph graph(V);

    // Матрица смежности для примера
    vector<vector<int>> adjMatrix = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    graph.setAdjacencyMatrix(adjMatrix);

    // Вывод исходной матрицы смежности
    graph.printAdjacencyMatrix();
    cout << endl;

    // Построение минимального остовного дерева
    graph.boruvkaMST();

    return 0;
}