// *********************************************************
// Program: radix_sort.cpp
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
#include "CSVWriter.h"
#include "Record.h"
#include "Timer.h"

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::filesystem::path resolveInputPath(const std::string& inputFilename);
std::filesystem::path buildSortedOutputPath(const std::string& inputFilename);
std::filesystem::path buildRuntimeOutputPath(const std::string& inputFilename);
void countingSortByDigit(std::vector<Record>& records, long long exp);
void radixSort(std::vector<Record>& records);
bool writeRuntimeFile(const std::filesystem::path& outputPath, double milliseconds, double seconds);
bool runRadixSortProgram(const std::string& inputFilename);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: radix_sort <dataset_file>" << std::endl;
        return 1;
    }

    if (!runRadixSortProgram(argv[1]))
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

std::filesystem::path buildSortedOutputPath(const std::string& inputFilename)
{
    const std::filesystem::path inputPath(inputFilename);
    const std::string outputFilename = "radix_sorted_" + inputPath.filename().string();

    return std::filesystem::path("outputs") / "sorted" / outputFilename;
}

std::filesystem::path buildRuntimeOutputPath(const std::string& inputFilename)
{
    const std::filesystem::path inputPath(inputFilename);
    const std::string datasetName = inputPath.stem().string();
    const std::string prefix = "dataset_";
    const std::string sizePart =
        datasetName.rfind(prefix, 0) == 0 ? datasetName.substr(prefix.length()) : datasetName;

    return std::filesystem::path("outputs") / "sorted" /
           ("radix_sort_runtime_" + sizePart + ".txt");
}

void countingSortByDigit(std::vector<Record>& records, long long exp)
{
    std::array<size_t, 10> count = {0};
    std::vector<Record> output(records.size());

    for (const Record& record : records)
    {
        const size_t digit = static_cast<size_t>((record.id / exp) % 10);
        ++count[digit];
    }

    for (size_t i = 1; i < count.size(); ++i)
    {
        count[i] += count[i - 1];
    }

    for (size_t i = records.size(); i > 0; --i)
    {
        const Record& record = records[i - 1];
        const size_t digit = static_cast<size_t>((record.id / exp) % 10);
        output[count[digit] - 1] = record;
        --count[digit];
    }

    records = output;
}

void radixSort(std::vector<Record>& records)
{
    if (records.empty())
    {
        return;
    }

    long long maxId = records.front().id;
    for (const Record& record : records)
    {
        if (record.id > maxId)
        {
            maxId = record.id;
        }
    }

    for (long long exp = 1; maxId / exp > 0; exp *= 10)
    {
        countingSortByDigit(records, exp);
    }
}

bool writeRuntimeFile(const std::filesystem::path& outputPath, double milliseconds, double seconds)
{
    std::ofstream outputFile(outputPath);

    if (!outputFile.is_open())
    {
        std::cerr << "Error: could not open " << outputPath.string()
                  << " for writing." << std::endl;
        return false;
    }

    outputFile << "Radix Sort Runtime\n";
    outputFile << "Milliseconds: " << milliseconds << '\n';
    outputFile << "Seconds: " << seconds << '\n';

    return static_cast<bool>(outputFile);
}

bool runRadixSortProgram(const std::string& inputFilename)
{
    const std::filesystem::path inputPath = resolveInputPath(inputFilename);
    std::vector<Record> records = CSVReader::loadCSV(inputPath.string());

    if (records.empty())
    {
        std::cerr << "Error: no valid records loaded from " << inputPath.string() << std::endl;
        return false;
    }

    Timer timer;
    timer.start();
    radixSort(records);
    timer.stop();

    const double milliseconds = timer.elapsedMilliseconds();
    const double seconds = timer.elapsedSeconds();

    const std::filesystem::path sortedOutputPath = buildSortedOutputPath(inputFilename);
    const std::filesystem::path runtimeOutputPath = buildRuntimeOutputPath(inputFilename);

    if (!CSVWriter::saveCSV(sortedOutputPath.string(), records))
    {
        return false;
    }

    if (!writeRuntimeFile(runtimeOutputPath, milliseconds, seconds))
    {
        return false;
    }

    std::cout << "Radix Sort completed." << std::endl;
    std::cout << "Sorted output: " << sortedOutputPath.string() << std::endl;
    std::cout << "Runtime output: " << runtimeOutputPath.string() << std::endl;
    std::cout << "Milliseconds: " << milliseconds << std::endl;
    std::cout << "Seconds: " << seconds << std::endl;

    return true;
}
