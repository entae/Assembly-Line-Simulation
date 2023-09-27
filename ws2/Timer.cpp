// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 27, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Timer.h"

Timer::Timer() : startTime(), running(false) {}

void Timer::start() {
    startTime = std::chrono::steady_clock::now();
    running = true;
}

long long Timer::stop() {
    if (!running) {
        return 0; // Timer not started
    }

    auto endTime = std::chrono::steady_clock::now();
    running = false;

    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}
