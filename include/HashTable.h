#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Record.h"

#include <cstddef>

// Hash table interface for searching records by id.
class HashTable
{
public:
    HashTable(size_t capacity);

    void insert(const Record& record);
    bool search(long long key, Record& result);

private:
    size_t tableCapacity;
    // TODO: Add table storage, collision handling data, and hash helper declarations.
};

#endif
