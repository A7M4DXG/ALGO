// *********************************************************
// Program: radix_sort_step.cpp
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

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

const int START_ROW = 1;
const int END_ROW = 7;
const int TOTAL_ID_DIGITS = 10;

std::vector<Record> loadRange(const std::string& filename, int startRow, int endRow);
std::string formatRecords(const std::vector<Record>& records, const std::string& label);
void countingSortByDigit(std::vector<Record>& records, long long exp);
bool writeStep(std::ofstream& outputFile, const std::vector<Record>& records, const std::string& label);
bool runRadixSortStepDemo(const std::string& inputFilename);
bool parseRecordLine(const std::string& line, Record& record);
bool isValidTextField(const std::string& text);
std::filesystem::path buildOutputPath(const std::string& inputFilename, int startRow, int endRow);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: radix_sort_step <dataset_file>" << std::endl;
        return 1;
    }

    if (!runRadixSortStepDemo(argv[1]))
    {
        return 1;
    }

    return 0;
}

std::vector<Record> loadRange(const std::string& filename, int startRow, int endRow)
{
    std::vector<Record> records;

    if (startRow < 1 || endRow < startRow)
    {
        std::cerr << "Error: invalid row range." << std::endl;
        return records;
    }

    std::ifstream inputFile(filename);
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
                      << " in " << filename << std::endl;
        }
    }

    return records;
}

std::string formatRecords(const std::vector<Record>& records, const std::string& label)
{
    std::ostringstream output;
    output << "[";

    for (size_t i = 0; i < records.size(); ++i)
    {
        if (i > 0)
        {
            output << ", ";
        }

        output << records[i].id << "/" << records[i].text;
    }

    output << "] " << label;
    return output.str();
}

void countingSortByDigit(std::vector<Record>& records, long long exp)
{
    std::array<int, 10> count = {0};
    std::vector<Record> output(records.size());

    for (const Record& record : records)
    {
        const int digit = static_cast<int>((record.id / exp) % 10);
        ++count[digit];
    }

    for (size_t i = 1; i < count.size(); ++i)
    {
        count[i] += count[i - 1];
    }

    for (int i = static_cast<int>(records.size()) - 1; i >= 0; --i)
    {
        const int digit = static_cast<int>((records[static_cast<size_t>(i)].id / exp) % 10);
        const int outputIndex = count[digit] - 1;
        output[static_cast<size_t>(outputIndex)] = records[static_cast<size_t>(i)];
        --count[digit];
    }

    records = output;
}

bool writeStep(std::ofstream& outputFile, const std::vector<Record>& records, const std::string& label)
{
    outputFile << formatRecords(records, label) << '\n';
    return static_cast<bool>(outputFile);
}

bool runRadixSortStepDemo(const std::string& inputFilename)
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

    if (!writeStep(outputFile, records, "original"))
    {
        std::cerr << "Error: failed while writing original step." << std::endl;
        return false;
    }

    long long exp = 1;
    for (int digitLabel = TOTAL_ID_DIGITS; digitLabel >= 1; --digitLabel)
    {
        countingSortByDigit(records, exp);

        if (!writeStep(outputFile, records, "d=" + std::to_string(digitLabel)))
        {
            std::cerr << "Error: failed while writing digit step." << std::endl;
            return false;
        }

        exp *= 10;
    }

    std::cout << "Radix Sort step output generated: "
              << outputPath.string() << std::endl;

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

std::filesystem::path buildOutputPath(const std::string& inputFilename, int startRow, int endRow)
{
    const std::filesystem::path inputPath(inputFilename);
    const std::string outputFilename =
        inputPath.stem().string() + "_radix_sorted_step_" +
        std::to_string(startRow) + "_" + std::to_string(endRow) + ".txt";

    return std::filesystem::path("outputs") / "radix_steps" / outputFilename;
}
