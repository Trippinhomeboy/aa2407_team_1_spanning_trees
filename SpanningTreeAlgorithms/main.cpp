#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "Graph.h"
#include "algorithms/PrimAlgorithm.h"
#include "algorithms/KruskalAlgorithm.h"
#include "algorithms/BoruvkaAlgorithm.h"

class TestRunner {
private:
    std::vector<std::unique_ptr<SpanningTreeAlgorithm>> algorithms;

public:
    TestRunner() {
        algorithms.push_back(std::make_unique<PrimAlgorithm>());
        algorithms.push_back(std::make_unique<KruskalAlgorithm>());
        algorithms.push_back(std::make_unique<BoruvkaAlgorithm>());
    }

    void runTest(const std::string& testName, const Graph& graph) {
        std::cout << "\n" << std::string(80, '=') << "\n";
        std::cout << "TEST: " << testName << "\n";
        std::cout << std::string(80, '=') << "\n";

        graph.printGraph();
        std::cout << "\n";

        for (auto& algorithm : algorithms) {
            try {
                auto result = algorithm->findSpanningTree(graph);
                result.print();
            }
            catch (const std::exception& e) {
                std::cout << "❌ " << algorithm->getName() << " failed: " << e.what() << "\n";
            }
        }
    }
};

int main() {
    std::cout << "=== SPANNING TREE ALGORITHMS COMPREHENSIVE TEST SUITE ===\n";

    TestRunner runner;

    runner.runTest("Empty Graph (0 vertices)", Graph(0));

    Graph singleVertex(1);
    runner.runTest("Single Vertex Graph", singleVertex);

    Graph twoVertices(2);
    runner.runTest("Two Vertices No Edges", twoVertices);

    Graph twoVerticesConnected(2);
    twoVerticesConnected.addEdge(0, 1, 5);
    runner.runTest("Two Vertices Connected", twoVerticesConnected);

    Graph threeVerticesLine(3);
    threeVerticesLine.addEdge(0, 1, 2);
    threeVerticesLine.addEdge(1, 2, 3);
    runner.runTest("Three Vertices Line", threeVerticesLine);

    Graph threeVerticesTriangle(3);
    threeVerticesTriangle.addEdge(0, 1, 1);
    threeVerticesTriangle.addEdge(1, 2, 2);
    threeVerticesTriangle.addEdge(2, 0, 3);
    runner.runTest("Three Vertices Triangle", threeVerticesTriangle);

    Graph fourVerticesSquare(4);
    fourVerticesSquare.addEdge(0, 1, 1);
    fourVerticesSquare.addEdge(1, 2, 1);
    fourVerticesSquare.addEdge(2, 3, 1);
    fourVerticesSquare.addEdge(3, 0, 1);
    runner.runTest("Four Vertices Square", fourVerticesSquare);

    Graph fourVerticesComplete(4);
    fourVerticesComplete.addEdge(0, 1, 1);
    fourVerticesComplete.addEdge(0, 2, 2);
    fourVerticesComplete.addEdge(0, 3, 3);
    fourVerticesComplete.addEdge(1, 2, 4);
    fourVerticesComplete.addEdge(1, 3, 5);
    fourVerticesComplete.addEdge(2, 3, 6);
    runner.runTest("Four Vertices Complete", fourVerticesComplete);

    Graph starGraph(6);
    for (int i = 1; i < 6; ++i) {
        starGraph.addEdge(0, i, i);
    }
    runner.runTest("Star Graph Center 0", starGraph);

    Graph chainGraph(6);
    for (int i = 0; i < 5; ++i) {
        chainGraph.addEdge(i, i + 1, 1);
    }
    runner.runTest("Chain Graph", chainGraph);

    Graph cycleGraph(5);
    for (int i = 0; i < 4; ++i) {
        cycleGraph.addEdge(i, i + 1, 1);
    }
    cycleGraph.addEdge(4, 0, 1);
    runner.runTest("Cycle Graph", cycleGraph);

    Graph disconnectedGraph(4);
    disconnectedGraph.addEdge(0, 1, 1);
    disconnectedGraph.addEdge(2, 3, 1);
    runner.runTest("Disconnected Graph", disconnectedGraph);

    Graph sameWeightsGraph(5);
    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            sameWeightsGraph.addEdge(i, j, 1);
        }
    }
    runner.runTest("Complete Graph Same Weights", sameWeightsGraph);

    Graph increasingWeightsGraph(5);
    int weight = 1;
    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            increasingWeightsGraph.addEdge(i, j, weight++);
        }
    }
    runner.runTest("Complete Graph Increasing Weights", increasingWeightsGraph);

    Graph decreasingWeightsGraph(5);
    weight = 15;
    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            decreasingWeightsGraph.addEdge(i, j, weight--);
        }
    }
    runner.runTest("Complete Graph Decreasing Weights", decreasingWeightsGraph);

    Graph largeWeightsGraph(4);
    largeWeightsGraph.addEdge(0, 1, 1000);
    largeWeightsGraph.addEdge(0, 2, 100);
    largeWeightsGraph.addEdge(0, 3, 10);
    largeWeightsGraph.addEdge(1, 2, 1);
    largeWeightsGraph.addEdge(1, 3, 10000);
    largeWeightsGraph.addEdge(2, 3, 100000);
    runner.runTest("Large Weight Variations", largeWeightsGraph);

    Graph sparseGraph1 = Graph::generateSparseGraph(10, 0.1);
    runner.runTest("Sparse Graph 10 vertices", sparseGraph1);

    Graph sparseGraph2 = Graph::generateSparseGraph(20, 0.05);
    runner.runTest("Sparse Graph 20 vertices", sparseGraph2);

    Graph denseGraph1 = Graph::generateDenseGraph(8, 0.8);
    runner.runTest("Dense Graph 8 vertices", denseGraph1);

    Graph denseGraph2 = Graph::generateDenseGraph(15, 0.9);
    runner.runTest("Dense Graph 15 vertices", denseGraph2);

    Graph completeSmall = Graph::generateCompleteGraph(6);
    runner.runTest("Complete Graph 6 vertices", completeSmall);

    Graph completeMedium = Graph::generateCompleteGraph(10);
    runner.runTest("Complete Graph 10 vertices", completeMedium);

    Graph treeSmall = Graph::generateTree(8);
    runner.runTest("Tree Graph 8 vertices", treeSmall);

    Graph treeLarge = Graph::generateTree(20);
    runner.runTest("Tree Graph 20 vertices", treeLarge);

    Graph gridSmall = Graph::generateGridGraph(3, 3);
    runner.runTest("Grid Graph 3x3", gridSmall);

    Graph gridMedium = Graph::generateGridGraph(5, 4);
    runner.runTest("Grid Graph 5x4", gridMedium);

    Graph randomSmall = Graph::generateRandomGraph(8, 10);
    runner.runTest("Random Graph 8v 10e", randomSmall);

    Graph randomMedium = Graph::generateRandomGraph(15, 30);
    runner.runTest("Random Graph 15v 30e", randomMedium);

    Graph randomLarge = Graph::generateRandomGraph(25, 50);
    runner.runTest("Random Graph 25v 50e", randomLarge);

    Graph worstCasePrim(5);
    worstCasePrim.addEdge(0, 1, 1);
    worstCasePrim.addEdge(0, 2, 100);
    worstCasePrim.addEdge(0, 3, 100);
    worstCasePrim.addEdge(0, 4, 100);
    worstCasePrim.addEdge(1, 2, 1);
    worstCasePrim.addEdge(1, 3, 100);
    worstCasePrim.addEdge(1, 4, 100);
    worstCasePrim.addEdge(2, 3, 1);
    worstCasePrim.addEdge(2, 4, 100);
    worstCasePrim.addEdge(3, 4, 1);
    runner.runTest("Worst Case for Prim", worstCasePrim);

    Graph worstCaseKruskal(5);
    worstCaseKruskal.addEdge(0, 1, 5);
    worstCaseKruskal.addEdge(0, 2, 4);
    worstCaseKruskal.addEdge(0, 3, 3);
    worstCaseKruskal.addEdge(0, 4, 2);
    worstCaseKruskal.addEdge(1, 2, 1);
    worstCaseKruskal.addEdge(1, 3, 6);
    worstCaseKruskal.addEdge(1, 4, 7);
    worstCaseKruskal.addEdge(2, 3, 8);
    worstCaseKruskal.addEdge(2, 4, 9);
    worstCaseKruskal.addEdge(3, 4, 10);
    runner.runTest("Worst Case for Kruskal", worstCaseKruskal);

    Graph bestCasePrim(5);
    bestCasePrim.addEdge(0, 1, 1);
    bestCasePrim.addEdge(0, 2, 1);
    bestCasePrim.addEdge(0, 3, 1);
    bestCasePrim.addEdge(0, 4, 1);
    bestCasePrim.addEdge(1, 2, 100);
    bestCasePrim.addEdge(1, 3, 100);
    bestCasePrim.addEdge(1, 4, 100);
    bestCasePrim.addEdge(2, 3, 100);
    bestCasePrim.addEdge(2, 4, 100);
    bestCasePrim.addEdge(3, 4, 100);
    runner.runTest("Best Case for Prim", bestCasePrim);

    Graph bestCaseKruskal(5);
    bestCaseKruskal.addEdge(0, 1, 1);
    bestCaseKruskal.addEdge(0, 2, 1);
    bestCaseKruskal.addEdge(0, 3, 1);
    bestCaseKruskal.addEdge(0, 4, 1);
    bestCaseKruskal.addEdge(1, 2, 2);
    bestCaseKruskal.addEdge(1, 3, 2);
    bestCaseKruskal.addEdge(1, 4, 2);
    bestCaseKruskal.addEdge(2, 3, 3);
    bestCaseKruskal.addEdge(2, 4, 3);
    bestCaseKruskal.addEdge(3, 4, 4);
    runner.runTest("Best Case for Kruskal", bestCaseKruskal);

    Graph complexGraph1(7);
    complexGraph1.addEdge(0, 1, 7);
    complexGraph1.addEdge(0, 3, 5);
    complexGraph1.addEdge(1, 2, 8);
    complexGraph1.addEdge(1, 3, 9);
    complexGraph1.addEdge(1, 4, 7);
    complexGraph1.addEdge(2, 4, 5);
    complexGraph1.addEdge(3, 4, 15);
    complexGraph1.addEdge(3, 5, 6);
    complexGraph1.addEdge(4, 5, 8);
    complexGraph1.addEdge(4, 6, 9);
    complexGraph1.addEdge(5, 6, 11);
    runner.runTest("Complex Graph 1", complexGraph1);

    Graph complexGraph2(6);
    complexGraph2.addEdge(0, 1, 4);
    complexGraph2.addEdge(0, 2, 4);
    complexGraph2.addEdge(1, 2, 2);
    complexGraph2.addEdge(1, 3, 3);
    complexGraph2.addEdge(2, 3, 4);
    complexGraph2.addEdge(2, 4, 3);
    complexGraph2.addEdge(3, 4, 2);
    complexGraph2.addEdge(3, 5, 3);
    complexGraph2.addEdge(4, 5, 5);
    runner.runTest("Complex Graph 2", complexGraph2);

    Graph performanceTestSmall = Graph::generateRandomGraph(50, 100);
    runner.runTest("Performance Test Small", performanceTestSmall);

    Graph performanceTestMedium = Graph::generateRandomGraph(100, 300);
    runner.runTest("Performance Test Medium", performanceTestMedium);

    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "ALL TESTS COMPLETED\n";
    std::cout << std::string(80, '=') << "\n";

    return 0;
}