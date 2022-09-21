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
    this->clear();
    for (int i = 0; i < iSize; ++i)
    {
        delete[] TTable[i]; // теоретически должны вызываться деструкторы листов
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
    HashTable &temp = std::move<HashTable &>(*this);
    *this = std::move<HashTable &>(b);
    b = std::move<HashTable &>(temp);
}

HashTable &HashTable::operator=(const HashTable &b)
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
    return *this;
}

void HashTable::clear()
{
    for (int i = 0; i < iSize; ++i)
    {
        for (int j = 0; j < iSize; ++j)
        {
            TTable[i][j].List.clear();
        }
    }
}

/* bool HashTable::erase(const Key &k)
{
    // get hesh1 get hesh 2
    // HashTable::TTable[][].;
}

bool HashTable::insert(const Key &k, const TValue &v)
{
    // HashTable::TTable[GetHash1(k)][GetHash2(k)].List.push_back(v);
} */

/* bool contains(const Key &k) const{
    //return HashTable::TTable[GetHash1(k)][GetHash2(k)].List.size;
} */

TValue &HashTable::operator[](const Key &k)
{
    if (this->contains(k))
    {
        this->insert(k, TValue());
    }
    //надо вернуть значение, а если коллизия?
}

