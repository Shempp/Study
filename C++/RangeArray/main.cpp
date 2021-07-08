// std
#include <iostream>
#include <chrono>
#include <cassert>

// Memory leaks
#if defined (_MSC_VER) && defined (_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif // _MSC_VER && _DEBUG

#include "RangeArray.h"

using namespace std::chrono;

void InitDumpMemoryLeaks()
{
#if defined (_MSC_VER) && defined (_DEBUG)
    // Work only in debug for Visual Studio
    // An automatic call to _CrtDumpMemoryLeaks at each exit point
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE); 
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
#endif // _MSC_VER && _DEBUG
}

void ExamplesRangeArray()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    constexpr size_t numOfElements = 1000000;
    uintptr_t ptrToFind = 0;
    size_t randomIteration = rand() % numOfElements;

    std::vector<Range> ranges;
    std::vector<void*> pointers;
    for (size_t i = 0; i < numOfElements; ++i) {
        int* p = new int(i);
        ranges.push_back({ reinterpret_cast<uintptr_t>(p), sizeof(int) });
        pointers.push_back(p);

        if (randomIteration == i) {
            ptrToFind = reinterpret_cast<uintptr_t>(p);
        }
    }

    // Init
    std::cout << "Init range array" << std::endl;
    auto startInitRangeArr = high_resolution_clock::now();
    RangeArray arr(ranges);
    auto stopInitRangeArr = high_resolution_clock::now();
    std::cout << "Time: " << duration_cast<microseconds>(stopInitRangeArr - startInitRangeArr).count()
        << " microseconds" << std::endl;

    // Find by addr
    std::cout << "Find all ranges that contains addr" << std::endl;
    auto startFind = high_resolution_clock::now();
    auto findResult = arr.FindContaining(ptrToFind);
    auto stopFind = high_resolution_clock::now();
    std::cout << "Time: " << duration_cast<microseconds>(stopFind - startFind).count()
        << " microseconds" << std::endl;

    // Find by brute force
    std::cout << "Find all ranges that contains addr (brute force)" << std::endl;
    auto startFindBruteForce = high_resolution_clock::now();
    std::vector<Range> findBruteForceResult;
    auto allRanges = arr.Ranges();
    for (const auto& range : allRanges) {
        if (range.m_startAddress <= ptrToFind && ptrToFind < range.m_startAddress + range.m_size) {
            findBruteForceResult.push_back(range);
        }
    }
    auto stopFindBruteForce = high_resolution_clock::now();
    std::cout << "Time: " << duration_cast<microseconds>(stopFindBruteForce - startFindBruteForce).count()
        << " microseconds" << std::endl;

    assert(findResult.size() == findBruteForceResult.size());

    // Insert
    std::cout << "Insert in range array" << std::endl;
    char* chP = new char[256];
    auto startInsert = high_resolution_clock::now();
    arr.Insert({ reinterpret_cast<uintptr_t>(chP), sizeof(char) });
    auto stopInsert = high_resolution_clock::now();
    std::cout << "Time: " << duration_cast<microseconds>(stopInsert - startInsert).count()
        << " microseconds" << std::endl;

    // Remove by addr
    std::cout << "Remove in range array by addr" << std::endl;
    auto startRemoveByAddr = high_resolution_clock::now();
    arr.Remove(reinterpret_cast<uintptr_t>(chP));
    auto stopRemoveByAddr = high_resolution_clock::now();
    std::cout << "Time: " << duration_cast<microseconds>(stopRemoveByAddr - startRemoveByAddr).count()
        << " microseconds" << std::endl;

    // Remove by range
    std::cout << "Remove in range array by range" << std::endl;
    struct CustomType {
        std::uint64_t i = 10000;
        bool b = true;
    };
    CustomType* customTypeP = new CustomType();
    auto rangeToDel = Range{ reinterpret_cast<uintptr_t>(customTypeP), sizeof(CustomType) };
    arr.Insert(rangeToDel);
    auto startRemoveByRange = high_resolution_clock::now();
    arr.Remove(rangeToDel);
    auto stopRemoveByRange = high_resolution_clock::now();
    std::cout << "Time: " << duration_cast<microseconds>(stopRemoveByRange - startRemoveByRange).count()
        << " microseconds" << std::endl;
}

int main()
{
    InitDumpMemoryLeaks();
    
    ExamplesRangeArray();

    return 0;
}