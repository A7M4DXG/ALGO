// ******************************************************************************************************************************
// Program: Record.h
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
#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>

struct Record
{
    long long id;
    std::string text;

    // Default constructor
    Record();

    // Parameterized constructor
    Record(long long idParam, const std::string &textParam);

    // Stream helper for easy console printing
    friend std::ostream &operator<<(std::ostream &os, const Record &record);
};

#endif // RECORD_H