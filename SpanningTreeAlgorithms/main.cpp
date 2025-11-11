#include <iostream>
#include "Graph/Graph.h"
#include "SpanninTreeAlgorithm/SpanningTreeAlgorithm.h"
#include "Prim/PrimAlgorithm.h"
#include "Kruskal/KruskalAlgorithm.h"
#include "Boruvka/BoruvkaAlgorithm.h"
#include "SecondBestMST/SecondBestMSTAlgorithm.h"
#include "Timer/Timer.h"
#include "Tournament/TournamentTable.h"

using namespace std;

TournamentTable tournament;

void testWithAlgorithm(SpanningTreeAlgorithm& algorithm, const string& testName, const Graph& graph) {
    cout << testName << "\n";
    graph.printGraph();

    Timer timer(algorithm.getName());
    auto mst = algorithm.findMST(graph);
    double executionTime = timer.stop();

    algorithm.printMST(mst);

    bool isConnected = mst.size() >= graph.getVerticesCount() - 1;
    int totalWeight = algorithm.calculateTotalWeight(mst);

    tournament.addResult(algorithm.getName(), executionTime, totalWeight, isConnected);
    cout << "\n";
}

void runAllAlgorithms(const string& testName, const Graph& graph) {
    tournament.startTest(testName);

    PrimAlgorithm prim;
    KruskalAlgorithm kruskal;
    BoruvkaAlgorithm boruvka;
    SecondBestMSTAlgorithm secondBest;

    testWithAlgorithm(prim, testName + " (Prim)", graph);
    testWithAlgorithm(kruskal, testName + " (Kruskal)", graph);
    testWithAlgorithm(boruvka, testName + " (Boruvka)", graph);
    testWithAlgorithm(secondBest, testName + " (Second-Best)", graph);

    tournament.printTable();
    cout << "----------------------------------------\n\n";
}

void testEmptyGraph() {
    Graph graph(0);
    runAllAlgorithms("Test 1: Empty Graph", graph);
}

void testSingleVertex() {
    Graph graph(1);
    runAllAlgorithms("Test 2: Single Vertex", graph);
}

void testTwoVerticesNoEdge() {
    Graph graph(2);
    runAllAlgorithms("Test 3: Two Vertices No Edge", graph);
}

void testTwoVerticesWithEdge() {
    Graph graph(2);
    graph.addEdge(0, 1, 5);
    runAllAlgorithms("Test 4: Two Vertices With Edge", graph);
}

void testDisconnectedGraph() {
    Graph graph(4);
    graph.addEdge(0, 1, 3);
    graph.addEdge(2, 3, 4);
    runAllAlgorithms("Test 5: Disconnected Graph", graph);
}

void testNormalGraph() {
    Graph graph(5);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 9);
    runAllAlgorithms("Test 6: Normal Graph", graph);
}

void testThreeVertices() {
    Graph graph(3);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 0, 3);
    runAllAlgorithms("Test 7: Three Vertices", graph);
}

void testFourVertices() {
    Graph graph(4);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 0, 1);
    runAllAlgorithms("Test 8: Four Vertices", graph);
}

int main() {
    cout << "Spanning Tree Algorithms Comparison\n\n";

    testEmptyGraph();
    testSingleVertex();
    testTwoVerticesNoEdge();
    testTwoVerticesWithEdge();
    testDisconnectedGraph();
    testNormalGraph();
    testThreeVertices();
    testFourVertices();

    cout << "All tests completed successfully!\n";
    return 0;
}