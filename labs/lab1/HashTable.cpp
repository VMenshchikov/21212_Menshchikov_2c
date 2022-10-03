#include <iostream>
#include "HashTable.h"

HashTable::TList::TList(const Key &k) : k(k){};

HashTable::TList::TList(const Key &k, const TValue &value) :
            k(k), value(value) { //в первую очередб смотри сюда!!!!!!!!!!!!!
};

HashTable::HashTable() : iSize(32), iCount(0)
{
    TTable = new std::list<TList>[iSize];
}

HashTable::~HashTable()
{
    this->clear(); //очищаются ли листы в delete?
    delete[] TTable;
}



HashTable::HashTable(const HashTable &b) : 
    iSize(b.iSize), iCount(b.iCount) {
    if (&b == this)
    {
        return;
    }

    TTable = new std::list<TList>[iSize];
    std::copy(b.TTable, b.TTable + iSize, TTable);
}

HashTable::HashTable(HashTable &&b) : 
    iSize(b.iSize), iCount(b.iCount), TTable(b.TTable) {
    b.iSize = 0;
    b.iCount = 0;
    b.TTable = nullptr;
}

void HashTable::swap(HashTable &b) {
    HashTable temp = std::move(*this);
    *this = std::move<HashTable &>(b);
    b = std::move<HashTable &>(temp);
}

HashTable &HashTable::operator=(const HashTable &b) {
    if (&b == this) {
        return *this;
    }
    if(TTable != nullptr) {
        clear();
    } 
    else {
        TTable = new std::list<TList>[iSize];
    }
    std::copy(b.TTable, b.TTable + iSize, TTable);
    return *this;
}

void HashTable::clear() {
    for (int i = 0; i < iSize; ++i) {
            TTable[i].clear();
    }
    iCount = 0;
    // уменьшение размера до стандартного?
}


bool HashTable::erase(const Key &k) {
    auto hash = GetHash(k);
    return del(k, hash);
}

bool HashTable::erase(const Key &k, const size_t hash) {
    return del(k, hash);
    
}

bool HashTable::insert(const Key &k, const TValue &v) {
    auto hash = GetHash(k);
    if (contains(k, hash)) {
        return false;
    }

    if(iCount > iSize*0.7) {
        *this = ReCreation(*this);
    }

    TList tmp(k, v);
    TTable[hash].push_back(TList(k, v));
    iCount++;
    return true;
}

bool HashTable::contains(const Key &k) const {
    auto hash = GetHash(k);
    if (!TTable[hash].empty()) {
        for (auto i = TTable[hash].begin(); i != TTable[hash].end(); i++) {
            if (i->k == k) {
                return true;
            }
        }
    }
    return false;
}

bool HashTable::contains(const Key &k, size_t hash) const {
    if (!TTable[hash].empty())
    {
        for (auto i = TTable[hash].begin(); i != TTable[hash].end(); i++)
        {
            if (i->k == k)
            {
                return true;
            }
        }
    }
    return false;
}

TValue &HashTable::operator[](const Key &k) {
    auto hash = GetHash(k);
    if (!TTable[hash].empty())
    {
        auto i = TTable[hash].begin();
        for (i; i != TTable[hash].end(); i++)
        {
            if (i->k == k)
            {
                return (i->value);
            }
        }
    }
    this->insert(k, TValue());
    return TTable[GetHash(k)].front().value;
}


TValue& HashTable::at(const Key &k) {
    auto hash = GetHash(k);
    if (!TTable[hash].empty())
    {
        auto i = TTable[hash].begin();
        for (i; i != TTable[hash].end(); i++)
        {
            if (i->k == k)
            {
                return (i->value);
            }
        }
    }
    std::cerr << "wrong key" << std::endl;
    throw(-1);//есть ли стандартные(+-) смыслы ошибок
}

const TValue& HashTable::at(const Key &k) const {
    auto hash = GetHash(k);
    if (!TTable[hash].empty())
    {
        auto i = TTable[hash].begin();
        for (i; i != TTable[hash].end(); i++)
        {
            if (i->k == k)
            {
                return (i->value);
            }
        }
    }
    std::cerr << "wrong key" << std::endl;
    throw(-1); //есть ли стандартные(+-) смыслы ошибок
}


 //   std::cerr << e.what() << '\n';


size_t HashTable::size() const {
    return HashTable::iSize;
}

size_t HashTable::count() const {
    return HashTable::iCount;
}

bool HashTable::empty() const {
    return HashTable::iCount;
}

bool operator==(const HashTable &a, const HashTable &b) {
    return (&a == &b);
}

bool operator!=(const HashTable &a, const HashTable &b) {
    return (&a != &b);
}

size_t HashTable::GetHash(const Key &k) const {
    size_t hash = 1;
    size_t degree = 1;
    for (int i = 0; i < k.size(); i++) { //переполнение невозможно при вменяемом ключе
        hash += static_cast<size_t>(k[i]) * degree;
        degree *= 3;
    }
    hash %= this->size();
    return hash;
}

bool HashTable::del(const Key &k, const size_t hash) {
    if (!TTable[hash].empty()) {
        auto i = TTable[hash].begin();
        for (i; i != TTable[hash].end(); i++) {
            if (i->k == k) {
                TTable[hash].erase(i);
                iCount--;
                return true;
            }
        }
    }
    return false;
}

HashTable&& HashTable::ReCreation() {
    HashTable b(iSize * 2);
    b.iCount = iCount;
    // какой размер возбмется?
}
