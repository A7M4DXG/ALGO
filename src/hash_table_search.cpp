// *********************************************************
// Program: hash_table_search.cpp
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

#include "CSVReader.h"
#include "Record.h"
#include "Timer.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct HashSlot
{
    Record record;
    bool occupied;

    HashSlot()
        : record(), occupied(false)
    {
    }
};

struct TimingResults
{
    double bestSeconds;
    double averageSeconds;
    double worstSeconds;
};

std::filesystem::path resolveInputPath(const std::string& inputFilename);
std::filesystem::path buildOutputPath(const std::string& inputFilename);
size_t hashFunction(long long key, size_t capacity);
bool insert(std::vector<HashSlot>& table, const Record& record);
bool search(const std::vector<HashSlot>& table, long long key);
long long findBestCaseKey(const std::vector<HashSlot>& table);
long long findWorstCaseKey(const std::vector<HashSlot>& table);
std::vector<long long> buildAverageCaseKeys(const std::vector<Record>& records, size_t searchCount);
double measureBestCase(const std::vector<HashSlot>& table, long long key, size_t searchCount);
double measureAverageCase(const std::vector<HashSlot>& table, const std::vector<long long>& keys);
double measureWorstCase(const std::vector<HashSlot>& table, long long key, size_t searchCount);
bool writeResults(const std::filesystem::path& outputPath, const TimingResults& results);
bool runHashTableSearchProgram(const std::string& inputFilename);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: hash_table_search <dataset_file>" << std::endl;
        return 1;
    }

    if (!runHashTableSearchProgram(argv[1]))
    {
        return 1;
    }

    return 0;
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

std::filesystem::path buildOutputPath(const std::string& inputFilename)
{
    const std::filesystem::path inputPath(inputFilename);
    return std::filesystem::path("outputs") / "search" /
           ("hash_table_search_" + inputPath.stem().string() + ".txt");
}

size_t hashFunction(long long key, size_t capacity)
{
    if (capacity == 0U)
    {
        return 0U;
    }

    const long long capacityValue = static_cast<long long>(capacity);
    long long index = key % capacityValue;

    if (index < 0)
    {
        index += capacityValue;
    }

    return static_cast<size_t>(index);
}

bool insert(std::vector<HashSlot>& table, const Record& record)
{
    const size_t capacity = table.size();
    const size_t startIndex = hashFunction(record.id, capacity);

    for (size_t probe = 0U; probe < capacity; ++probe)
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

bool search(const std::vector<HashSlot>& table, long long key)
{
    const size_t capacity = table.size();
    const size_t startIndex = hashFunction(key, capacity);

    for (size_t probe = 0U; probe < capacity; ++probe)
    {
        const size_t index = (startIndex + probe) % capacity;

        if (!table[index].occupied)
        {
            return false;
        }

        if (table[index].record.id == key)
        {
            return true;
        }
    }

    return false;
}

long long findBestCaseKey(const std::vector<HashSlot>& table)
{
    for (size_t index = 0U; index < table.size(); ++index)
    {
        if (table[index].occupied && hashFunction(table[index].record.id, table.size()) == index)
        {
            return table[index].record.id;
        }
    }

    for (const HashSlot& slot : table)
    {
        if (slot.occupied)
        {
            return slot.record.id;
        }
    }

    return -1LL;
}

long long findWorstCaseKey(const std::vector<HashSlot>& table)
{
    size_t worstStartIndex = 0U;
    size_t worstProbeCount = 0U;
    const size_t capacity = table.size();

    for (size_t startIndex = 0U; startIndex < capacity; ++startIndex)
    {
        size_t probeCount = 0U;

        while (probeCount < capacity && table[(startIndex + probeCount) % capacity].occupied)
        {
            ++probeCount;
        }

        if (probeCount > worstProbeCount)
        {
            worstProbeCount = probeCount;
            worstStartIndex = startIndex;
        }
    }

    long long candidateKey = static_cast<long long>(worstStartIndex);
    const long long capacityStep = static_cast<long long>(table.size());

    while (search(table, candidateKey))
    {
        candidateKey += capacityStep;
    }

    return candidateKey;
}

std::vector<long long> buildAverageCaseKeys(const std::vector<Record>& records, size_t searchCount)
{
    std::vector<long long> keys;
    keys.reserve(searchCount);

    std::mt19937_64 generator(6214U);
    std::uniform_int_distribution<size_t> distribution(0U, records.size() - 1U);

    for (size_t i = 0U; i < searchCount; ++i)
    {
        keys.push_back(records[distribution(generator)].id);
    }

    return keys;
}

double measureBestCase(const std::vector<HashSlot>& table, long long key, size_t searchCount)
{
    size_t foundCount = 0U;
    Timer timer;

    timer.start();
    for (size_t i = 0U; i < searchCount; ++i)
    {
        if (search(table, key))
        {
            ++foundCount;
        }
    }
    timer.stop();

    if (foundCount != searchCount)
    {
        std::cerr << "Warning: best-case search target was not found every time." << std::endl;
    }

    return timer.elapsedSeconds();
}

double measureAverageCase(const std::vector<HashSlot>& table, const std::vector<long long>& keys)
{
    size_t foundCount = 0U;
    Timer timer;

    timer.start();
    for (long long key : keys)
    {
        if (search(table, key))
        {
            ++foundCount;
        }
    }
    timer.stop();

    if (foundCount != keys.size())
    {
        std::cerr << "Warning: average-case search target was not found every time." << std::endl;
    }

    return timer.elapsedSeconds();
}

double measureWorstCase(const std::vector<HashSlot>& table, long long key, size_t searchCount)
{
    size_t foundCount = 0U;
    Timer timer;

    timer.start();
    for (size_t i = 0U; i < searchCount; ++i)
    {
        if (search(table, key))
        {
            ++foundCount;
        }
    }
    timer.stop();

    if (foundCount != 0U)
    {
        std::cerr << "Warning: worst-case non-existing target was unexpectedly found." << std::endl;
    }

    return timer.elapsedSeconds();
}

bool writeResults(const std::filesystem::path& outputPath, const TimingResults& results)
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

    outputFile << "Best case time: " << results.bestSeconds << " seconds\n\n";
    outputFile << "Average case time: " << results.averageSeconds << " seconds\n\n";
    outputFile << "Worst case time: " << results.worstSeconds << " seconds\n";

    return static_cast<bool>(outputFile);
}

bool runHashTableSearchProgram(const std::string& inputFilename)
{
    const std::filesystem::path inputPath = resolveInputPath(inputFilename);
    const std::vector<Record> records = CSVReader::loadCSV(inputPath.string());

    if (records.empty())
    {
        std::cerr << "Error: no valid records loaded from " << inputPath.string() << std::endl;
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

    const long long bestCaseKey = findBestCaseKey(table);
    const long long worstCaseKey = findWorstCaseKey(table);
    const size_t searchCount = records.size();
    const std::vector<long long> averageCaseKeys = buildAverageCaseKeys(records, searchCount);

    TimingResults results;
    results.bestSeconds = measureBestCase(table, bestCaseKey, searchCount);
    results.averageSeconds = measureAverageCase(table, averageCaseKeys);
    results.worstSeconds = measureWorstCase(table, worstCaseKey, searchCount);

    const std::filesystem::path outputPath = buildOutputPath(inputFilename);

    if (!writeResults(outputPath, results))
    {
        return false;
    }

    std::cout << "Best case time: " << results.bestSeconds << " seconds" << std::endl;
    std::cout << std::endl;
    std::cout << "Average case time: " << results.averageSeconds << " seconds" << std::endl;
    std::cout << std::endl;
    std::cout << "Worst case time: " << results.worstSeconds << " seconds" << std::endl;
    std::cout << "Output file: " << outputPath.string() << std::endl;

    return true;
}
