#include <string>
#include <list>
typedef std::string Key;

struct TValue
{
    unsigned age = -1;
    unsigned weight = -1;
};

struct TList
{
    std::list<TValue> List;
};

class HashTable
{
public:
    HashTable();
    ~HashTable();

    HashTable(const HashTable &b);
    HashTable(const HashTable &&b);

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
    bool empty() const;

    friend bool operator==(const HashTable &a, const HashTable &b);
    friend bool operator!=(const HashTable &a, const HashTable &b);

private:
    TList **TTable;
    int iSize = 32;
    int iCount = 0;
};
