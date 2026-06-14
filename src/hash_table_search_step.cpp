// *********************************************************
// Program: hash_table_search_step.cpp
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

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

const long long FOUND_TARGET = -1;
const long long NOT_FOUND_TARGET = 123456789LL;

struct HashSlot
{
    Record record;
    bool occupied;

    HashSlot()
        : record(), occupied(false)
    {
    }
};

size_t hashFunction(long long key, size_t capacity);
bool insert(std::vector<HashSlot>& table, const Record& record);
bool searchWithSteps(
    const std::vector<HashSlot>& table,
    long long target,
    const std::filesystem::path& outputPath);
std::vector<Record> loadDataset(const std::string& filename);
bool runHashTableSearchStepDemo(const std::string& inputFilename);
bool parseRecordLine(const std::string& line, Record& record);
bool isValidTextField(const std::string& text);
std::filesystem::path resolveInputPath(const std::string& inputFilename);
std::filesystem::path buildOutputPath(const std::string& inputFilename, long long target);
long long resolveFoundTarget(const std::vector<Record>& records);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: hash_table_search_step <dataset_file>" << std::endl;
        return 1;
    }

    if (!runHashTableSearchStepDemo(argv[1]))
    {
        return 1;
    }

    return 0;
}

size_t hashFunction(long long key, size_t capacity)
{
    if (capacity == 0)
    {
        return 0;
    }

    const long long positiveKey = key < 0 ? -key : key;
    return static_cast<size_t>(positiveKey) % capacity;
}

bool insert(std::vector<HashSlot>& table, const Record& record)
{
    const size_t capacity = table.size();
    const size_t startIndex = hashFunction(record.id, capacity);

    for (size_t probe = 0; probe < capacity; ++probe)
    {
        const size_t index = (startIndex + probe) % capacity;

        if (!table[index].occupied)
        {
            table[index].record = record;
            table[index].occupied = true;
            return true;
        }
    }

    return false;
}

bool searchWithSteps(
    const std::vector<HashSlot>& table,
    long long target,
    const std::filesystem::path& outputPath)
{
    try
    {
        std::filesystem::create_directories(outputPath.parent_path());
    }
    catch (const std::filesystem::filesystem_error& error)
    {
        std::cerr << "Error: could not create output directory: "
                  << error.what() << std::endl;
        return false;
    }

    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open())
    {
        std::cerr << "Error: could not open " << outputPath.string()
                  << " for writing." << std::endl;
        return false;
    }

    const size_t capacity = table.size();
    const size_t startIndex = hashFunction(target, capacity);

    for (size_t probe = 0; probe < capacity; ++probe)
    {
        const size_t index = (startIndex + probe) % capacity;

        outputFile << "Probe " << (probe + 1) << ":\n";

        if (!table[index].occupied)
        {
            outputFile << "Compare " << target << "\n\n";
            outputFile << "Not Found\n\n";
            outputFile << "-1 != " << target << '\n';
            return static_cast<bool>(outputFile);
        }

        outputFile << "Compare " << table[index].record.id << "\n\n";

        if (table[index].record.id == target)
        {
            outputFile << "Found\n\n";
            outputFile << target << " = " << table[index].record.id
                       << "/" << table[index].record.text << '\n';
            return static_cast<bool>(outputFile);
        }
    }

    outputFile << "Not Found\n\n";
    outputFile << "-1 != " << target << '\n';
    return static_cast<bool>(outputFile);
}

std::vector<Record> loadDataset(const std::string& filename)
{
    std::vector<Record> records;
    const std::filesystem::path inputPath = resolveInputPath(filename);

    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open " << filename << std::endl;
        return records;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(inputFile, line))
    {
        ++lineNumber;

        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.empty())
        {
            continue;
        }

        Record record;
        if (parseRecordLine(line, record))
        {
            records.push_back(record);
        }
        else
        {
            std::cerr << "Warning: skipped invalid row " << lineNumber
                      << " in " << inputPath.string() << std::endl;
        }
    }

    return records;
}

bool runHashTableSearchStepDemo(const std::string& inputFilename)
{
    const std::vector<Record> records = loadDataset(inputFilename);

    if (records.empty())
    {
        std::cerr << "Error: no valid records loaded from dataset." << std::endl;
        return false;
    }

    std::vector<HashSlot> table(records.size() * 2U);

    for (const Record& record : records)
    {
        if (!insert(table, record))
        {
            std::cerr << "Error: hash table is full." << std::endl;
            return false;
        }
    }

    const long long foundTarget = resolveFoundTarget(records);
    const std::filesystem::path foundOutputPath = buildOutputPath(inputFilename, foundTarget);
    const std::filesystem::path notFoundOutputPath = buildOutputPath(inputFilename, NOT_FOUND_TARGET);

    if (!searchWithSteps(table, foundTarget, foundOutputPath))
    {
        return false;
    }

    if (!searchWithSteps(table, NOT_FOUND_TARGET, notFoundOutputPath))
    {
        return false;
    }

    std::cout << "Hash Table found-search output generated: "
              << foundOutputPath.string() << std::endl;
    std::cout << "Hash Table not-found-search output generated: "
              << notFoundOutputPath.string() << std::endl;

    return true;
}

bool parseRecordLine(const std::string& line, Record& record)
{
    std::stringstream parser(line);
    std::string idField;
    std::string textField;
    std::string extraField;

    if (!std::getline(parser, idField, ',') || !std::getline(parser, textField, ','))
    {
        return false;
    }

    if (std::getline(parser, extraField, ','))
    {
        return false;
    }

    if (!textField.empty() && textField.back() == '\r')
    {
        textField.pop_back();
    }

    if (!isValidTextField(textField))
    {
        return false;
    }

    try
    {
        size_t parsedLength = 0;
        const long long id = std::stoll(idField, &parsedLength);

        if (parsedLength != idField.length())
        {
            return false;
        }

        record = Record(id, textField);
    }
    catch (const std::invalid_argument&)
    {
        return false;
    }
    catch (const std::out_of_range&)
    {
        return false;
    }

    return true;
}

bool isValidTextField(const std::string& text)
{
    if (text.length() != 5)
    {
        return false;
    }

    for (char character : text)
    {
        if (character < 'a' || character > 'z')
        {
            return false;
        }
    }

    return true;
}

std::filesystem::path resolveInputPath(const std::string& inputFilename)
{
    const std::filesystem::path directPath(inputFilename);

    if (std::filesystem::exists(directPath))
    {
        return directPath;
    }

    const std::filesystem::path datasetPath =
        std::filesystem::path("datasets") / directPath.filename();

    if (std::filesystem::exists(datasetPath))
    {
        return datasetPath;
    }

    return directPath;
}

std::filesystem::path buildOutputPath(const std::string& inputFilename, long long target)
{
    const std::filesystem::path inputPath(inputFilename);
    const std::string outputFilename =
        inputPath.stem().string() + "_hash_table_search_step_" +
        std::to_string(target) + ".txt";

    return std::filesystem::path("outputs") / "search" / outputFilename;
}

long long resolveFoundTarget(const std::vector<Record>& records)
{
    if (FOUND_TARGET == -1)
    {
        return records.front().id;
    }

    return FOUND_TARGET;
}
