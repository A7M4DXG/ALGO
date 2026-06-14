#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include "Record.h"

#include <vector>

// Radix Sort interface for sorting records by id.
class RadixSort
{
public:
    static void sort(std::vector<Record>& data);

private:
    static void countingSortByDigit(std::vector<Record>& data, long long exp);
};

#endif
