// *********************************************************
// Program: dataset_generator.cpp
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

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace
{
    const long long MIN_ID = 1000000000LL;
    const long long MAX_ID = 9999999999LL;
    const unsigned long long ID_SPACE_SIZE =
        static_cast<unsigned long long>(MAX_ID - MIN_ID + 1LL);
    const size_t LARGE_DATASET_PROGRESS_THRESHOLD = 100000;
    const size_t PROGRESS_INTERVAL = 100000;

    bool parseDatasetSize(const std::string& value, size_t& size);
    std::string generateRandomText(std::mt19937_64& generator);
    long long generateUniqueId(
        std::mt19937_64& generator,
        std::unordered_set<long long>& usedIds);
    bool generateDataset(size_t size);
    void printProgress(size_t generated, size_t total);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: dataset_generator <size>" << std::endl;
        return 1;
    }

    size_t size = 0;
    if (!parseDatasetSize(argv[1], size))
    {
        std::cerr << "Error: size must be a positive integer." << std::endl;
        return 1;
    }

    if (static_cast<unsigned long long>(size) > ID_SPACE_SIZE)
    {
        std::cerr << "Error: requested size exceeds available unique ID range." << std::endl;
        return 1;
    }

    if (!generateDataset(size))
    {
        return 1;
    }

    return 0;
}

namespace
{
    bool parseDatasetSize(const std::string& value, size_t& size)
    {
        try
        {
            size_t parsedLength = 0;
            const unsigned long long parsedValue = std::stoull(value, &parsedLength);

            if (parsedLength != value.length() || parsedValue == 0)
            {
                return false;
            }

            size = static_cast<size_t>(parsedValue);
            return static_cast<unsigned long long>(size) == parsedValue;
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

    std::string generateRandomText(std::mt19937_64& generator)
    {
        static const char LOWERCASE_LETTERS[] = "abcdefghijklmnopqrstuvwxyz";
        std::uniform_int_distribution<int> letterDistribution(0, 25);

        std::string text;
        text.reserve(5);

        for (int i = 0; i < 5; ++i)
        {
            text.push_back(LOWERCASE_LETTERS[letterDistribution(generator)]);
        }

        return text;
    }

    long long generateUniqueId(
        std::mt19937_64& generator,
        std::unordered_set<long long>& usedIds)
    {
        std::uniform_int_distribution<long long> idDistribution(MIN_ID, MAX_ID);

        while (true)
        {
            const long long candidateId = idDistribution(generator);

            if (usedIds.insert(candidateId).second)
            {
                return candidateId;
            }
        }
    }

    bool generateDataset(size_t size)
    {
        const std::filesystem::path outputDirectory("datasets");
        const std::filesystem::path outputFile =
            outputDirectory / ("dataset_" + std::to_string(size) + ".csv");

        try
        {
            std::filesystem::create_directories(outputDirectory);
        }
        catch (const std::filesystem::filesystem_error& error)
        {
            std::cerr << "Error: could not create datasets directory: "
                      << error.what() << std::endl;
            return false;
        }

        std::ofstream file(outputFile);
        if (!file.is_open())
        {
            std::cerr << "Error: could not open " << outputFile.string()
                      << " for writing." << std::endl;
            return false;
        }

        std::random_device randomDevice;
        std::mt19937_64 generator(randomDevice());
        std::unordered_set<long long> usedIds;
        usedIds.reserve(size);

        for (size_t generated = 1; generated <= size; ++generated)
        {
            const long long id = generateUniqueId(generator, usedIds);
            const std::string text = generateRandomText(generator);

            file << id << ',' << text << '\n';

            if (!file)
            {
                std::cerr << "Error: failed while writing to "
                          << outputFile.string() << std::endl;
                return false;
            }

            if (size >= LARGE_DATASET_PROGRESS_THRESHOLD &&
                (generated % PROGRESS_INTERVAL == 0 || generated == size))
            {
                printProgress(generated, size);
            }
        }

        std::cout << "Dataset generated successfully: "
                  << outputFile.string() << std::endl;
        std::cout << "Total records: " << size << std::endl;

        return true;
    }

    void printProgress(size_t generated, size_t total)
    {
        const double percentage =
            (static_cast<double>(generated) / static_cast<double>(total)) * 100.0;

        std::cout << "Progress: " << generated << "/" << total
                  << " records (" << static_cast<int>(percentage) << "%)"
                  << std::endl;
    }
}
