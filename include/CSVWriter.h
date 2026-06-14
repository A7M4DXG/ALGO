#ifndef CSVWRITER_H
#define CSVWRITER_H

#include "Record.h"

#include <string>
#include <vector>

class CSVWriter
{
public:
    // Writes a vector of Records to a CSV file.
    static bool saveCSV(const std::string& filename, const std::vector<Record>& records);

    // Compatibility wrapper for skeleton naming.
    static void writeCSV(const std::string& filename, const std::vector<Record>& records);
};

#endif
