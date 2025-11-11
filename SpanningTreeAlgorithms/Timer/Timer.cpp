#include "Timer.h"
#include <iostream>

using namespace std::chrono;

Timer::Timer(const std::string& name) : algorithmName(name) {
    startTime = high_resolution_clock::now();
}

Timer::~Timer() {
}

double Timer::stop() {
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);
    double milliseconds = duration.count() / 1000.0;

    std::cout << algorithmName << " execution time: "
        << milliseconds << " ms\n";
    return milliseconds;
}