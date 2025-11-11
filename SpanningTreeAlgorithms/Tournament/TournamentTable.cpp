#include "TournamentTable.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void TournamentTable::startTest(const std::string& testName) {
    currentTestName = testName;
    results.clear();
}

void TournamentTable::addResult(const std::string& algorithmName, double time, int weight, bool connected) {
    results.push_back({ algorithmName, time, weight, connected });
}

void TournamentTable::printTable() {
    if (results.empty()) return;

    cout << "\nTOURNAMENT TABLE - " << currentTestName << "\n";
    cout << "=======================================================\n";
    cout << left << setw(6) << "Place"
        << setw(30) << "Algorithm"
        << setw(12) << "Time (ms)"
        << setw(10) << "Weight"
        << setw(15) << "Status" << "\n";
    cout << "-------------------------------------------------------\n";

    vector<AlgorithmResult> sortedResults = results;

    sort(sortedResults.begin(), sortedResults.end(),
        [](const AlgorithmResult& a, const AlgorithmResult& b) {
            if (a.executionTime != b.executionTime) {
                return a.executionTime < b.executionTime;
            }
            return a.totalWeight < b.totalWeight;
        });

    for (size_t i = 0; i < sortedResults.size(); i++) {
        string status = sortedResults[i].isConnected ? "Connected" : "Disconnected";
        string place;
        switch (i) {
        case 0: place = "1st"; break;
        case 1: place = "2nd"; break;
        case 2: place = "3rd"; break;
        case 3: place = "4th"; break;
        default: place = to_string(i + 1) + "th";
        }

        cout << left << setw(6) << place
            << setw(30) << sortedResults[i].algorithmName
            << setw(12) << fixed << setprecision(3) << sortedResults[i].executionTime
            << setw(10) << sortedResults[i].totalWeight
            << setw(15) << status << "\n";
    }

    auto fastest = min_element(results.begin(), results.end(),
        [](const AlgorithmResult& a, const AlgorithmResult& b) {
            return a.executionTime < b.executionTime;
        });

    auto bestWeight = min_element(results.begin(), results.end(),
        [](const AlgorithmResult& a, const AlgorithmResult& b) {
            if (a.totalWeight != b.totalWeight) {
                return a.totalWeight < b.totalWeight;
            }
            return a.executionTime < b.executionTime;
        });

    cout << "-------------------------------------------------------\n";
    cout << "Fastest: " << fastest->algorithmName << " (" << fastest->executionTime << " ms)\n";
    cout << "Best Weight: " << bestWeight->algorithmName << " (" << bestWeight->totalWeight << ")\n";
    cout << "=======================================================\n\n";
}

void TournamentTable::clear() {
    results.clear();
}