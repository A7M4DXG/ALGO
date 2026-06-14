#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
    Timer()
        : startTime(), stopTime(), isRunning(false)
    {
    }

    void start()
    {
        startTime = std::chrono::high_resolution_clock::now();
        stopTime = startTime;
        isRunning = true;
    }

    void stop()
    {
        stopTime = std::chrono::high_resolution_clock::now();
        isRunning = false;
    }

    void reset()
    {
        startTime = std::chrono::high_resolution_clock::time_point();
        stopTime = std::chrono::high_resolution_clock::time_point();
        isRunning = false;
    }

    double elapsedMilliseconds() const
    {
        const std::chrono::time_point<std::chrono::high_resolution_clock> endTime =
            isRunning ? std::chrono::high_resolution_clock::now() : stopTime;

        return std::chrono::duration<double, std::milli>(endTime - startTime).count();
    }

    double elapsedSeconds() const
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> stopTime;
    bool isRunning;
};

#endif
