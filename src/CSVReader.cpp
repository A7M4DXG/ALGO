// ******************************************************************************************************************************
// Program: CSVReader.cpp
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

#include "../include/CSVReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::vector<Record> CSVReader::loadCSV(const std::string &filename)
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

void CSVReader::removeTrailingCarriageReturn(std::string &value)
{
    if (!value.empty() && value.back() == '\r')
    {
        value.pop_back();
    }
}

bool CSVReader::isValidTextField(const std::string &text)
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

bool CSVReader::parseId(const std::string &value, long long &id)
{
    try
    {
        size_t parsedLength = 0;
        id = std::stoll(value, &parsedLength);
        return parsedLength == value.length();
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
    catch (const std::out_of_range &)
    {
        return false;
    }
}

bool CSVReader::isValidRecordLine(const std::string &line, Record &record)
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
