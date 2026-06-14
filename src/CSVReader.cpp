// *********************************************************
// Program: CSVReader.cpp
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

#include "../include/CSVReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::vector<Record> CSVReader::loadCSV(const std::string& filename)
{
    std::vector<Record> records;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return records;
    }

    std::string line;
    long lineNumber = 0;

    while (std::getline(file, line))
    {
        ++lineNumber;
        removeTrailingCarriageReturn(line);

        if (line.empty())
        {
            continue;
        }

        Record record;
        if (isValidRecordLine(line, record))
        {
            records.push_back(record);
        }
        else
        {
            std::cerr << "Warning: Invalid CSV row at line " << lineNumber
                      << " in " << filename << std::endl;
        }
    }

    return records;
}

void CSVReader::removeTrailingCarriageReturn(std::string& value)
{
    if (!value.empty() && value.back() == '\r')
    {
        value.pop_back();
    }
}

bool CSVReader::isValidTextField(const std::string& text)
{
    if (text.length() != 5)
    {
        return false;
    }

    for (char ch : text)
    {
        if (ch < 'a' || ch > 'z')
        {
            return false;
        }
    }

    return true;
}

bool CSVReader::parseId(const std::string& value, long long& id)
{
    try
    {
        size_t parsedLength = 0;
        id = std::stoll(value, &parsedLength);
        return parsedLength == value.length();
    }
    catch (const std::invalid_argument&)
    {
        return false;
    }
    catch (const std::out_of_range&)
    {
        return false;
    }
}

bool CSVReader::isValidRecordLine(const std::string& line, Record& record)
{
    std::stringstream ss(line);
    std::string idField;
    std::string textField;
    std::string extraField;

    if (!std::getline(ss, idField, ',') || !std::getline(ss, textField, ','))
    {
        return false;
    }

    if (std::getline(ss, extraField, ','))
    {
        return false;
    }

    removeTrailingCarriageReturn(textField);

    long long id = 0;
    if (!parseId(idField, id) || !isValidTextField(textField))
    {
        return false;
    }

    record = Record(id, textField);
    return true;
}
