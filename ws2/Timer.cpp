// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 27, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Timer.h"

Timer::Timer() : m_startTime(), m_running(false) {}

void Timer::start() {
    m_startTime = std::chrono::steady_clock::now();
    m_running = true;
}

long long Timer::stop() {
    long long result = 1;
    if (!m_running) {
        result = 0; // Timer not started
    } else {
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime);
        m_running = false;
        result = elapsedTime.count();
    }

    return result;
}
