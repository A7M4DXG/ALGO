// *********************************************************
// Program: CSVWriter.cpp
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

#include "../include/CSVWriter.h"

#include <filesystem>
#include <fstream>
#include <iostream>

bool CSVWriter::saveCSV(const std::string& filename, const std::vector<Record>& records)
{
    const std::filesystem::path outputPath(filename);
    const std::filesystem::path parentPath = outputPath.parent_path();

    if (!parentPath.empty())
    {
        std::filesystem::create_directories(parentPath);
    }

    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    for (const Record& record : records)
    {
        file << record.id << "," << record.text << '\n';
    }

    return true;
}

void CSVWriter::writeCSV(const std::string& filename, const std::vector<Record>& records)
{
    (void)saveCSV(filename, records);
}
