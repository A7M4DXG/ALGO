#ifndef CSVREADER_H
#define CSVREADER_H

#include "Record.h"

#include <string>
#include <vector>

class CSVReader
{
public:
    // Reads a CSV file and returns only valid records.
    static std::vector<Record> loadCSV(const std::string& filename);

private:
    static void removeTrailingCarriageReturn(std::string& value);
    static bool isValidTextField(const std::string& text);
    static bool parseId(const std::string& value, long long& id);
    static bool isValidRecordLine(const std::string& line, Record& record);
};

#endif
