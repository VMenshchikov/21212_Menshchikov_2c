#pragma once
#include "HashTable.h"

HashTable::HashTable() : iSize(32), iCount(0)
{
    TTable = new TList *[iSize];
    for (size_t i = 0; i < iSize; ++i)
    {
        TTable[i] = new TList[iSize];
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < iSize; ++i)
    {
        for (int j = 0; j < iSize; ++j)
        {
            TTable[i][j].List.clear();
            TTable[i][j].List.~list();
        }
        delete[] TTable[i];
    }
    delete[] TTable;
}

HashTable::HashTable(const HashTable &b) : iSize(iSize), iCount(iCount)
{
    if (b == *this)
    {
        return;
    }
    TTable = new TList *[iSize];
    for (size_t i = 0; i < iSize; ++i)
    {
        TTable[i] = new TList[iSize];
        for (size_t j = 0; j < iSize; ++j)
        {
            TTable[i][j].List = b.TTable[i][j].List;
        }
    }
}

HashTable::HashTable(const HashTable &&b) : iSize(iSize), iCount(iCount), TTable(TTable)
{
}

void HashTable::swap(HashTable &b)
{
    HashTable &temp = std::move<HashTable>(*this);
}
