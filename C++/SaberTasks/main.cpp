#define _CRT_SECURE_NO_WARNINGS

#include "tasks.h"

#include <iostream>
#include <chrono>
#include <bitset>
#include <list>
#include <cstdio>

void TestPrintBinary() {
    auto before = std::chrono::high_resolution_clock::now();
    auto after = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(after - before).count() << " microseconds" << std::endl;

    tasks::PrintBinary(std::numeric_limits<long long>::min());
    tasks::PrintBinary(std::numeric_limits<short>::min());
    tasks::PrintBinary(std::numeric_limits<char>::min());
    tasks::PrintBinary(-1);
    tasks::PrintBinary(0);
    tasks::PrintBinary(1);
    tasks::PrintBinary(7);
    tasks::PrintBinary(std::numeric_limits<char>::max());
    tasks::PrintBinary(std::numeric_limits<short>::max());
    tasks::PrintBinary(std::numeric_limits<long long>::max());
}

void TestRemoveDup() {
    auto size = 1ull << 32;
    char* data = new char[size + 1] {};
    std::memset(data, 'A', size);
    data[1ull << 32] = '\0';

    auto before = std::chrono::high_resolution_clock::now();
    tasks::RemoveDups(data);
    auto after = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << " ms" << std::endl;
}

void TestSerialization() {
    // 1
    FILE* fs = std::fopen("test.data", "wb");
    if (!fs) {
        return;
    }

    tasks::List ls;
    ls.PushFront("3");
    ls.PushFront("2");
    ls.PushFront("1");
    ls.PushFront("0");
    ls.PushFront("-1");
    ls.Empty();

    ls.PopFront();
    ls.PopFront();
    ls.PopFront();
    ls.PopFront();
    ls.PopFront();
    ls.Empty();

    ls.PushBack("4");
    ls.PushBack("5");
    ls.PopBack();
    ls.PopBack();

    ls.PushFront("4");
    ls.PushFront("3");
    ls.PushFront("2");
    ls.PushFront("1");
    ls.PushFront("0");
    ls.SetRandomLink(1, 3);
    ls.SetRandomLink(3, 0);
    ls.SetRandomLink(4, 3);

    auto before = std::chrono::high_resolution_clock::now();
    ls.Serialize(fs);
    auto after = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(after - before).count() << " microseconds" << std::endl;

    std::fclose(fs);

    // 2
    FILE* fd = std::fopen("test.data", "rb");
    if (!fd) {
        return;
    }

    tasks::List ld;
    auto before2 = std::chrono::high_resolution_clock::now();
    ld.Deserialize(fd);
    auto after2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(after2 - before2).count() << " microseconds" << std::endl;
}

int main() {
    TestPrintBinary();
    TestRemoveDup();
    TestSerialization();

    return 0;
}