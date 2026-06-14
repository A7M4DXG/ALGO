// ******************************************************************************************************************************
// Program: Timer.h
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC1L
// Tutorial Class: TT3L
// Trimester: 2610
// Member_1: 241UC240H5 | AHMED SIDDIG ADAM MOHAMED | ahmed.siddig.adam@student.mmu.edu.my | +60148514100
// Member_2: 241UC240QK | AL-MAWERI, EBRAHIM MOHAMMED ABDULLAH | ALMAWERI.EBRAHIM.MOHAMMED@student.mmu.edu.my | +601112758063
// Member_3: 251UC25085 | MOHAMMED, MOHAMMED ABDULAZIZ | MOHAMMED.MOHAMMED.ABDULAZ@student.mmu.edu.my | +60147386355
// Member_4: ID | NAME | EMAIL | PHONE
// ******************************************************************************************************************************
// Task Distribution
// Member_1: Project Leader, System Architecture,
//            Complete Algorithm Implementation,
//            Code Integration, Testing and Debugging.
//
// Member_2: Report Writing, Documentation,
//            Charts, Screenshots, References,
//            Final Report Preparation.
//
// Member_3: Experiment Execution,
//            Output Verification,
//            Results Collection and Validation.
//
// Member_4: N/A
// ******************************************************************************************************************************

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
