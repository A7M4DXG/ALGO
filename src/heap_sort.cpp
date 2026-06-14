// ******************************************************************************************************************************
// Program: heap_sort.cpp
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

#include "CSVReader.h"
#include "CSVWriter.h"
#include "Record.h"
#include "Timer.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::filesystem::path resolveInputPath(const std::string &inputFilename);
std::filesystem::path buildSortedOutputPath(const std::string &inputFilename);
std::filesystem::path buildRuntimeOutputPath(const std::string &inputFilename);
void heapify(std::vector<Record> &records, size_t heapSize, size_t rootIndex);
void buildMaxHeap(std::vector<Record> &records);
void heapSort(std::vector<Record> &records);
bool writeRuntimeFile(const std::filesystem::path &outputPath, double milliseconds, double seconds);
bool runHeapSortProgram(const std::string &inputFilename);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: heap_sort <dataset_file>" << std::endl;
        return 1;
    }

    if (!runHeapSortProgram(argv[1]))
    {
        return 1;
    }

    return 0;
}

std::filesystem::path resolveInputPath(const std::string &inputFilename)
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

std::filesystem::path buildSortedOutputPath(const std::string &inputFilename)
{
    const std::filesystem::path inputPath(inputFilename);
    const std::string outputFilename = "heap_sorted_" + inputPath.filename().string();

    return std::filesystem::path("outputs") / "sorted" / outputFilename;
}

std::filesystem::path buildRuntimeOutputPath(const std::string &inputFilename)
{
    const std::filesystem::path inputPath(inputFilename);
    const std::string datasetName = inputPath.stem().string();
    const std::string prefix = "dataset_";
    const std::string sizePart =
        datasetName.rfind(prefix, 0) == 0 ? datasetName.substr(prefix.length()) : datasetName;

    return std::filesystem::path("outputs") / "sorted" /
           ("heap_sort_runtime_" + sizePart + ".txt");
}

void heapify(std::vector<Record> &records, size_t heapSize, size_t rootIndex)
{
    size_t largest = rootIndex;
    const size_t leftChild = (2U * rootIndex) + 1U;
    const size_t rightChild = (2U * rootIndex) + 2U;

    if (leftChild < heapSize && records[leftChild].id > records[largest].id)
    {
        largest = leftChild;
    }

    if (rightChild < heapSize && records[rightChild].id > records[largest].id)
    {
        largest = rightChild;
    }

    if (largest != rootIndex)
    {
        std::swap(records[rootIndex], records[largest]);
        heapify(records, heapSize, largest);
    }
}

void buildMaxHeap(std::vector<Record> &records)
{
    for (size_t i = records.size() / 2U; i > 0; --i)
    {
        heapify(records, records.size(), i - 1U);
    }
}

void heapSort(std::vector<Record> &records)
{
    if (records.empty())
    {
        return;
    }

    buildMaxHeap(records);

    for (size_t i = records.size(); i > 1U; --i)
    {
        std::swap(records[0], records[i - 1U]);
        heapify(records, i - 1U, 0);
    }
}

bool writeRuntimeFile(const std::filesystem::path &outputPath, double milliseconds, double seconds)
{
    std::ofstream outputFile(outputPath);

    if (!outputFile.is_open())
    {
        std::cerr << "Error: could not open " << outputPath.string()
                  << " for writing." << std::endl;
        return false;
    }

    outputFile << "Heap Sort Runtime\n";
    outputFile << "Milliseconds: " << milliseconds << '\n';
    outputFile << "Seconds: " << seconds << '\n';

    return static_cast<bool>(outputFile);
}

bool runHeapSortProgram(const std::string &inputFilename)
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
    heapSort(records);
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

    std::cout << "Heap Sort completed." << std::endl;
    std::cout << "Sorted output: " << sortedOutputPath.string() << std::endl;
    std::cout << "Runtime output: " << runtimeOutputPath.string() << std::endl;
    std::cout << "Milliseconds: " << milliseconds << std::endl;
    std::cout << "Seconds: " << seconds << std::endl;

    return true;
}
