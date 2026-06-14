// ******************************************************************************************************************************
// Program: heap_sort_step.cpp
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

#include "Record.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

const int START_ROW = 1;
const int END_ROW = 7;

std::vector<Record> loadRange(const std::string &filename, int startRow, int endRow);
std::string formatRecords(const std::vector<Record> &records, const std::string &label);
void heapify(std::vector<Record> &records, int heapSize, int rootIndex);
void buildMaxHeap(std::vector<Record> &records);
bool writeStep(std::ofstream &outputFile, const std::vector<Record> &records, const std::string &label);
bool runHeapSortStepDemo(const std::string &inputFilename);
bool parseRecordLine(const std::string &line, Record &record);
bool isValidTextField(const std::string &text);
std::filesystem::path resolveInputPath(const std::string &inputFilename);
std::filesystem::path buildOutputPath(const std::string &inputFilename, int startRow, int endRow);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: heap_sort_step <dataset_file>" << std::endl;
        return 1;
    }

    if (!runHeapSortStepDemo(argv[1]))
    {
        return 1;
    }

    return 0;
}

std::vector<Record> loadRange(const std::string &filename, int startRow, int endRow)
{
    std::vector<Record> records;

    if (startRow < 1 || endRow < startRow)
    {
        std::cerr << "Error: invalid row range." << std::endl;
        return records;
    }

    const std::filesystem::path inputPath = resolveInputPath(filename);
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open " << filename << std::endl;
        return records;
    }

    std::string line;
    int currentRow = 0;

    while (currentRow < endRow && std::getline(inputFile, line))
    {
        ++currentRow;

        if (currentRow < startRow)
        {
            continue;
        }

        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        Record record;
        if (parseRecordLine(line, record))
        {
            records.push_back(record);
        }
        else
        {
            std::cerr << "Warning: skipped invalid row " << currentRow
                      << " in " << inputPath.string() << std::endl;
        }
    }

    return records;
}

std::string formatRecords(const std::vector<Record> &records, const std::string &label)
{
    std::ostringstream output;
    output << "[";

    for (size_t i = 0; i < records.size(); ++i)
    {
        if (i > 0)
        {
            output << ",";
        }

        output << records[i].id << "/" << records[i].text;
    }

    output << "] " << label;
    return output.str();
}

void heapify(std::vector<Record> &records, int heapSize, int rootIndex)
{
    int largest = rootIndex;
    const int leftChild = (2 * rootIndex) + 1;
    const int rightChild = (2 * rootIndex) + 2;

    if (leftChild < heapSize &&
        records[static_cast<size_t>(leftChild)].id > records[static_cast<size_t>(largest)].id)
    {
        largest = leftChild;
    }

    if (rightChild < heapSize &&
        records[static_cast<size_t>(rightChild)].id > records[static_cast<size_t>(largest)].id)
    {
        largest = rightChild;
    }

    if (largest != rootIndex)
    {
        std::swap(records[static_cast<size_t>(rootIndex)], records[static_cast<size_t>(largest)]);
        heapify(records, heapSize, largest);
    }
}

void buildMaxHeap(std::vector<Record> &records)
{
    const int heapSize = static_cast<int>(records.size());

    for (int i = (heapSize / 2) - 1; i >= 0; --i)
    {
        heapify(records, heapSize, i);
    }
}

bool writeStep(std::ofstream &outputFile, const std::vector<Record> &records, const std::string &label)
{
    outputFile << formatRecords(records, label) << '\n';
    return static_cast<bool>(outputFile);
}

bool runHeapSortStepDemo(const std::string &inputFilename)
{
    std::vector<Record> records = loadRange(inputFilename, START_ROW, END_ROW);

    if (records.empty())
    {
        std::cerr << "Error: no valid records loaded from selected range." << std::endl;
        return false;
    }

    const std::filesystem::path outputPath = buildOutputPath(inputFilename, START_ROW, END_ROW);

    try
    {
        std::filesystem::create_directories(outputPath.parent_path());
    }
    catch (const std::filesystem::filesystem_error &error)
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

    buildMaxHeap(records);

    if (!writeStep(outputFile, records, "initial"))
    {
        std::cerr << "Error: failed while writing initial heap step." << std::endl;
        return false;
    }

    for (int i = static_cast<int>(records.size()) - 1; i >= 1; --i)
    {
        std::swap(records[0], records[static_cast<size_t>(i)]);
        heapify(records, i, 0);

        if (!writeStep(outputFile, records, "i = " + std::to_string(i)))
        {
            std::cerr << "Error: failed while writing heap sort step." << std::endl;
            return false;
        }
    }

    std::cout << "Heap Sort step output generated: "
              << outputPath.string() << std::endl;

    return true;
}

bool parseRecordLine(const std::string &line, Record &record)
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
    catch (const std::invalid_argument &)
    {
        return false;
    }
    catch (const std::out_of_range &)
    {
        return false;
    }

    return true;
}

bool isValidTextField(const std::string &text)
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

std::filesystem::path buildOutputPath(const std::string &inputFilename, int startRow, int endRow)
{
    const std::filesystem::path inputPath(inputFilename);
    const std::string outputFilename =
        inputPath.stem().string() + "_heap_sorted_step_" +
        std::to_string(startRow) + "_" + std::to_string(endRow) + ".txt";

    return std::filesystem::path("outputs") / "heap_steps" / outputFilename;
}
