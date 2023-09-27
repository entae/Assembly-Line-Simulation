// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 27, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <chrono>

namespace sdds {
    class Timer {
        std::chrono::steady_clock::time_point m_startTime;
        bool m_running;

    public:
        Timer();
        // Start the timer
        void start();
        // Stop the timer and return elapsed time in nanoseconds
        long long stop();
    };
}

    #endif // !SDDS_TIMER_H