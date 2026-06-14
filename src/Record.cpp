// *********************************************************
// Program: Record.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC4L
// Tutorial Class: T13L
// Trimester: 2610
// Member_1: ID | NAME | EMAIL | PHONE
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: ID | NAME | EMAIL | PHONE
// *********************************************************
// Task Distribution
// Member_1:
// Member_2:
// Member_3:
// Member_4:
// *********************************************************

#include "Record.h"

Record::Record() : id(0), text("") {}

Record::Record(long long idParam, const std::string &textParam)
    : id(idParam), text(textParam) {}

std::ostream &operator<<(std::ostream &os, const Record &record)
{
    os << record.id << "," << record.text;
    return os;
}