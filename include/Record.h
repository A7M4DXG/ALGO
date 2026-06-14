// ******
// Program: Record.h
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: [Insert TC4L]
// Tutorial Class: [Insert T13L]
// Trimester: 2610
// Member_1: ID | NAME | EMAIL | PHONE
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: ID | NAME | EMAIL | PHONE
// ******
// Task Distribution
// Member_1: [Description]
// Member_2: [Description]
// Member_3: [Description]
// Member_4: [Description]
// ******

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