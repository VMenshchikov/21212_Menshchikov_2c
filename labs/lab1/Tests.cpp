#include "HashTable.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(Constructors, TEST_1) {
    HashTable table;
    EXPECT_TRUE(table.empty() && table.size() == table.GetStartSize() &&
                table.count() == 0);
}

TEST(Constructors, TEST_2) {
    HashTable table(500);
    EXPECT_TRUE(table.empty() && table.size() == 500);
}

TEST(Constructors, TEST_3) {
    HashTable table;
    HashTable table2(table);
    EXPECT_TRUE(table == table2);
}

TEST(Constructors, TEST_4) {
    HashTable table = HashTable();
    EXPECT_TRUE(table.empty());
}

TEST(Constructors, TEST_5) {
    TValue val;
    EXPECT_TRUE(val.age == -1 && val.weight == -1);
}

TEST(Constructors, TEST_6) {
    TValue val = TValue(10, 50);
    EXPECT_TRUE(val.age == 10 && val.weight == 50);
}

/////////

TEST(Functions, TEST_1) {
    HashTable table;
    EXPECT_TRUE(table.insert("1234567", TValue()));
}

TEST(Functions, TEST_2) {
    HashTable table;
    table.insert("1234567", TValue());
    EXPECT_FALSE(table.insert("1234567", TValue(5, 5)));
}

TEST(Functions, TEST_3) {
    HashTable table;
    TValue val(5, 6);
    table.insert("1234567", val);
    EXPECT_TRUE(table["1234567"] == val);
}

TEST(Functions, TEST_4) {
    HashTable table;
    EXPECT_TRUE(table["1234567"] == TValue());
}

TEST(Functions, TEST_5) {
    HashTable table, table2;
    table.insert("123", TValue());
    table2 = table;
    table2 = table2;
    table2 = std::move(table2);
    table.erase("123");
    table2.clear();
    EXPECT_TRUE(table.empty());
    EXPECT_TRUE(table2.empty());
}

TEST(Functions, TEST_6) {
    HashTable table;
    TValue val;
    table.insert("123", val);
    EXPECT_TRUE(table.at("123") == val);
}

TEST(Functions, TEST_7) {
    HashTable table;
    TValue val;
    table.insert("123", val);
    const HashTable table2(table);
    EXPECT_TRUE(table2.at("123") == val);
}

TEST(Functions, TEST_8) {
    HashTable table;
    const HashTable table2;
    EXPECT_ANY_THROW(table.at("123"));
    EXPECT_ANY_THROW(table2.at("12"));
}

TEST(Functions, TEST_9) {
    HashTable table, table2;
    TValue val1(1, 2), val2(10, 20), vals1(11, 22), vals2(101, 202);
    table.insert("123", val1);
    table.insert("1230", vals1);
    table2.insert("321", val2);
    table2.insert("3210", vals2);
    HashTable tableN = table, table2N = table2;
    table.swap(table2);
    EXPECT_TRUE(!(table != table2N) && (table2 == tableN));
}

TEST(Functions, TEST_10) {
    Key array[20] = {
        "10", "11",   "Иерихон", "13", "14",     "Петя", "Петя2",
        "17", "18",   "19",      "20", "Собака", "Кот",  "23",
        "24", "Котs", "26",      "27", "28",     "29",
    };

    TValue val[20];
    HashTable table;

    for (size_t i = 0; i < 20; ++i) {
        val[i].age = i;
        val[i].weight = 123456;
        table.insert(array[i], val[i]);
    }
    std::cout << "CurrentSize == " << table.size() << std::endl;
    EXPECT_TRUE(table["Петя"] == val[5] && table["27"] == val[17]);
}

TEST(Functions, TEST_11) {
    HashTable table;
    TValue val;
    for (size_t i = 0; i < 1000; ++i) {
        Key str;
        for (size_t j = 0; j < 10; ++j) {
            str.push_back(rand() % 256);
        }
        table.insert(str, val);
        std::cout << table.count() << " ";
    }
    std::cout << "CurrentSize == " << table.size() << std::endl;

    EXPECT_TRUE(table.size() > table.GetStartSize());
}

TEST(Functions, TEST_12) {
    HashTable table;
    table.insert("12", {12, 21});
    std::cout<<!table.contains("21");
    EXPECT_TRUE(!table.contains("21") && table.contains("12"));
}

TEST(Functions, TEST_13) {
    HashTable table;
    EXPECT_FALSE(table.erase("1"));
}

TEST(Functions, TEST_14) {
    HashTable table;
    HashTable table2;
    HashTable table3;

    table.insert("1", TValue());
    table3.insert("12", TValue());
    

    EXPECT_TRUE(table == table);
    EXPECT_FALSE(table == table2);
    TValue val;
    for (size_t i = 0; i < 1000; ++i) {
        Key str;
        for (size_t j = 0; j < 10; ++j) {
            str.push_back(rand() % 256);
        }
        table.insert(str, val);
    }
    EXPECT_FALSE(table == table3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}