#pragma once

#include <list>
#include <string>

typedef std::string Key;

struct TValue {
    int age = -1;
    int weight = -1;

    TValue() = default;
    TValue(unsigned age, unsigned weight);

    friend bool operator==(const TValue &a, const TValue &b);
};

class HashTable {
  public:
    HashTable();
    HashTable(size_t iSize);
    ~HashTable();

    HashTable(const HashTable &b);
    HashTable(HashTable &&b);

    // Обменивает значения двух хэш-таблиц.
    void swap(HashTable &b);

    HashTable &operator=(const HashTable &b);
    HashTable &operator=(HashTable &&b);

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

    size_t size() const { return iCount; }
    size_t capacity() const { return iSize; }
    bool empty() const { return !(iCount); }
    size_t GetStartSize() const {return START_SIZE;}
    double GetCoef() const {return RECREATION_COEF;}

    friend bool operator==(const HashTable &a, const HashTable &b);
    friend bool operator!=(const HashTable &a, const HashTable &b);

  private:
    static constexpr size_t START_SIZE = 16 ;
    static constexpr double RECREATION_COEF = 0.5l ;

    struct TList {
        Key k = "";
        TValue value;

        TList(const Key &k);
        TList() = default;
        TList(const Key &k, const TValue &value);
        ~TList() = default;
    };

    std::list<TList> *TTable = nullptr;
    size_t iSize = START_SIZE;
    // занятые ячейки таблицы(не кол-во элементов в ней)    
    size_t iCount = 0;

    size_t GetHash(const Key &k) const;
    // Пересобирает таблицу, при count > RECREATION_COEF
    void ReCreation();
    // дублирующие методы для избежания повторного подсчета хеша
    bool contains(const Key &k, size_t hash) const;
    bool erase(const Key &k, const size_t hash);
    // обертка erase
    bool del(const Key &k, const size_t hash);
    friend bool operator==(const HashTable::TList &a,
                           const HashTable::TList &b);
};
