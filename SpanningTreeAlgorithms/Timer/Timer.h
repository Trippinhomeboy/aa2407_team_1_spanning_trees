#pragma once
#include <chrono>
#include <string>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::string algorithmName;

public:
    Timer(const std::string& name);
    ~Timer();
    double stop();
};