#include "HashTable.h"

#include <cassert>
#include <iostream>

TValue::TValue(unsigned age, unsigned weight)
    : age(static_cast<int>(age)), weight(static_cast<int>(weight)){};

bool operator==(const TValue &a, const TValue &b) {
    return (a.age == b.age && a.weight == b.weight);
}

HashTable::TList::TList(const Key &k, const TValue &value) : k(k), value(value){};

HashTable::HashTable() : HashTable(START_SIZE) {}

HashTable::HashTable(size_t iSize) : iSize(iSize), iCount(0) {
    TTable = new std::list<TList>[iSize];
}

HashTable::~HashTable() {
    clear();
    delete[] TTable;
}

HashTable::HashTable(const HashTable &b) : iSize(b.iSize), iCount(b.iCount) {
    TTable = new std::list<TList>[iSize];
    std::copy(b.TTable, b.TTable + iSize, TTable);
}

HashTable::HashTable(HashTable &&b)
    : iSize(b.iSize), iCount(b.iCount), TTable(b.TTable) {
    b.iSize = 0;
    b.iCount = 0;
    b.TTable = nullptr;
}

void HashTable::swap(HashTable &b) {
    HashTable temp = std::move(*this);
    assert(this->TTable == nullptr);
    *this = std::move(b);
    assert(this->TTable != nullptr);
    b = std::move(temp);
}

HashTable &HashTable::operator=(const HashTable &b) {
    if (&b == this) {
        return *this;
    }
    iCount = b.iCount;
    iSize = b.iSize;
        clear();
    std::copy(b.TTable, b.TTable + iSize, TTable);
    return *this;
}

HashTable &HashTable::operator=(HashTable &&b) {
    iSize = b.iSize;
    iCount = b.iCount;
    if (&b == this) {
        return *this;
    }
    TTable = std::move(b.TTable);
    b.TTable = nullptr;
    b.iSize = 0;
    b.iCount = 0;
    return *this;
}

void HashTable::clear() {
    if (TTable != nullptr) {
        for (int i = 0; i < iSize; ++i) {
            TTable[i].clear();
        }
        iCount = 0;
    }
}

bool HashTable::erase(const Key &k) {
    auto hash = GetHash(k);
    return del(k, hash);
}

bool HashTable::insert(const Key &k, const TValue &v) {
    auto hash = GetHash(k);
    if (contains(k, hash)) {
        return false;
    }

    if (iCount > iSize * RECREATION_COEF) {
        ReCreation();
    }

    if (TTable[hash].empty()) {
        iCount++;
    }
    TTable[hash].push_back(TList(k, v));
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
    if (!TTable[hash].empty()) {
        for (auto i = TTable[hash].begin(); i != TTable[hash].end(); i++) {
            if (i->k == k) {
                return true;
            }
        }
    }
    return false;
}

TValue &HashTable::operator[](const Key &k) {
    auto hash = GetHash(k);
    if (!TTable[hash].empty()) {
        auto i = TTable[hash].begin();
        for (i; i != TTable[hash].end(); i++) {
            if (i->k == k) {
                return (i->value);
            }
        }
    }
    this->insert(k, TValue());
    return TTable[GetHash(k)].front().value;
}

TValue &HashTable::at(const Key &k) {
    auto hash = GetHash(k);
    if (!TTable[hash].empty()) {
        auto i = TTable[hash].begin();
        for (i; i != TTable[hash].end(); i++) {
            if (i->k == k) {
                return (i->value);
            }
        }
    }
    throw(std::invalid_argument("invalid index"));
}

const TValue &HashTable::at(const Key &k) const {
    auto hash = GetHash(k);
    if (!TTable[hash].empty()) {
        auto i = TTable[hash].begin();
        for (i; i != TTable[hash].end(); i++) {
            if (i->k == k) {
                return (i->value);
            }
        }
    }
    std::cerr << "invalid index" << std::endl;  //???
    throw(std::invalid_argument("invalid index"));
}



bool operator==(const HashTable::TList &a, const HashTable::TList &b) {
    return ((a.k == b.k) && (a.value == b.value)) ? true : false;
}

bool operator==(const HashTable &a, const HashTable &b) {
    if (&a == &b) {
        return true;
    } else if (a.size() != b.size()) {
        return false;
    } else {
        for (size_t i = 0; i < a.size(); ++i) {
            if (a.TTable[i] != b.TTable[i]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const HashTable &a, const HashTable &b) { return !(a == b); }

size_t HashTable::GetHash(const Key &k) const {
    size_t hash = 1;
    size_t degree = 1;
    for (int i = 0; i < k.size(); i++) {
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

void HashTable::ReCreation() {
    HashTable b(iSize * 2);
    for (size_t i = 0; i < iSize; ++i) {
        auto j = TTable[i].begin();
        for (j; j != TTable[i].end(); ++j) {
            b.insert(j->k, j->value);
        }
    }
    *this = std::move(b);
    return;
}
