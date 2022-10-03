#pragma once

#include <string>
#include <list>

#define START_SIZE 1024

typedef std::string Key;

struct TValue
{
    unsigned age = -1;
    unsigned weight = -1;
};

class HashTable
{
public:


    HashTable();
    ~HashTable();

    HashTable(const HashTable &b);
    HashTable(HashTable &&b);

    // Обменивает значения двух хэш-таблиц.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функци
    // std::swap.
    void swap(HashTable &b);

    HashTable &operator=(const HashTable &b);

    // Очищает контейнер.
    void clear();
    // Удаляет элемент по заданному ключу.
    bool erase(const Key &k);
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key &k, const TValue &v);

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key &k) const;

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    TValue &operator[](const Key &k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    TValue &at(const Key &k);
    const TValue &at(const Key &k) const;

    size_t size() const;
    size_t count() const;
    bool empty() const;

    friend bool operator==(const HashTable &a, const HashTable &b);
    friend bool operator!=(const HashTable &a, const HashTable &b);

private:
    struct TList
    {
        Key k = "";
        TValue value;

        TList(const Key &k);
        TList() = default;
        TList(const Key &k, const TValue &value);
        ~TList() = default;
    };

    std::list<TList>* TTable = nullptr;
    size_t iSize = START_SIZE;
    size_t iCount = 0;

   

    size_t GetHash(const Key &k) const;
    HashTable&& ReCreation(HashTable &b);
    bool contains(const Key &k, size_t hash) const;
    bool erase(const Key &k, const size_t hash);
    bool del(const Key &k, const size_t hash);
};
