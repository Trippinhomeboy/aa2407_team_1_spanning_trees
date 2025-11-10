#ifndef BORUVKAALGORITHM_H
#define BORUVKAALGORITHM_H

#include <vector>
#include <string>
#include <chrono>

// Структура для представления ребра
struct Edge {
    int src, dest, weight;

    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

// Структура для результатов выполнения алгоритма
struct BoruvkaResult {
    std::vector<Edge> mstEdges;
    int totalWeight;
    long long executionTimeMicroseconds;
    bool success;
    std::string message;
};

// Предварительное объявление класса Graph
class Graph;

class BoruvkaAlgorithm {
public:
    // Основной метод для поиска MST
    static BoruvkaResult findMST(const Graph& graph);

    // Метод для поиска MST с замером времени
    static BoruvkaResult findMSTWithTimeMeasurement(const Graph& graph);

    // Вспомогательные методы
    static std::string resultToString(const BoruvkaResult& result);
    static void printResult(const BoruvkaResult& result);

private:
    // Вспомогательные методы для реализации алгоритма
    static int findComponent(const std::vector<int>& component, int vertex);
    static void unionComponents(std::vector<int>& component, int comp1, int comp2);
};

#endif // BORUVKAALGORITHM_H
