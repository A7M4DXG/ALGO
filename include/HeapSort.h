#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "Record.h"

#include <vector>

// Heap Sort interface for sorting records by id.
class HeapSort
{
public:
    static void sort(std::vector<Record>& data);

private:
    static void heapify(std::vector<Record>& data, int n, int i);
};

#endif
