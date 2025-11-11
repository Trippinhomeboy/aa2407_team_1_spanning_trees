#pragma once
#include <vector>
#include <string>
#include <map>

struct AlgorithmResult {
    std::string algorithmName;
    double executionTime;
    int totalWeight;
    bool isConnected;
};

class TournamentTable {
private:
    std::vector<AlgorithmResult> results;
    std::string currentTestName;

public:
    void startTest(const std::string& testName);
    void addResult(const std::string& algorithmName, double time, int weight, bool connected);
    void printTable();
    void clear();
};