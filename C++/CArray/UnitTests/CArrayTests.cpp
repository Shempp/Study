// std
#include <random>
#include <algorithm>

// unit tests
#include <CppUnitTest.h>

// Visual Studio 
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

// Tested functionality
#include "CArray/CArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CArrayTests
{
	struct LeakChecker
	{
		LeakChecker()
		{
			_CrtMemCheckpoint(&m_before);
		}
		~LeakChecker()
		{
			_CrtMemCheckpoint(&m_after);

			Assert::AreEqual(0, _CrtMemDifference(&m_diff, &m_before, &m_after), L"Memory leak detected");
		}

		_CrtMemState m_before{};
		_CrtMemState m_after{};
		_CrtMemState m_diff{};
	};

	void PrintArr(
			const CArray<int>& _arr
		)
	{
		for (unsigned int i = 0; i < _arr.size(); ++i)
		{
			Logger::WriteMessage(std::to_string(_arr[i]).c_str());
		}
	}

	void PrintArr(
			const CArray<std::string>& _arr
		)
	{
		for (unsigned int i = 0; i < _arr.size(); ++i)
		{
			Logger::WriteMessage(_arr[i].c_str());		
		}
	}

	int randInt(
			std::mt19937& _rng, 
			int _min, 
			int _max
		)
	{
		std::uniform_int_distribution<int> uniRange(_min, _max);
		return uniRange(_rng);
	}

	std::string randStr(
			std::mt19937& _rng, 
			size_t _length = 10
		)
	{
		std::uniform_int_distribution<int> uniRange('a', 'z');
		std::string result(_length, '\0');
		for (auto& symb : result)
		{
			symb = uniRange(_rng);
		}
		return result;
	}

	TEST_CLASS(IntTests)
	{
	private:
		// Input params
		const int m_origNumOfItems = 20;
		const int m_minVal = 0;
		const int m_maxVal = 100;
		const int m_numOfInserts = 10;

		// For random generation
		std::mt19937 m_rng;

	public:
		IntTests()
			: m_rng((std::random_device())())
		{
		}

		TEST_METHOD(A1_AddTest)
		{
			// Memory leak checker
			LeakChecker checker;
			Logger::WriteMessage(__FUNCTION__);

			CArray<int> arr;
			for (auto i = 0; i < m_origNumOfItems; ++i)
			{
				arr.push_back(randInt(m_rng, m_minVal, m_maxVal));
			}
			Logger::WriteMessage(L"Array:");
			PrintArr(arr);

			Assert::AreEqual(m_origNumOfItems, static_cast<int>(arr.size()));
			for (unsigned int i = 0; i < arr.size(); ++i)
			{
				if (arr[i] < m_minVal || arr[i] > m_maxVal)
				{
					Assert::Fail(L"Array value is out of bounds");
				}
			}
		}

		TEST_METHOD(A2_SortTest)
		{
			LeakChecker checker;
			Logger::WriteMessage(__FUNCTION__);

			CArray<int> arr;
			for (auto i = 0; i < m_origNumOfItems; ++i)
			{
				arr.push_back(randInt(m_rng, m_minVal, m_maxVal));
			}
			Logger::WriteMessage(L"Array:");
			PrintArr(arr);

			std::sort(arr.begin(), arr.end());
			Logger::WriteMessage(L"Sorted array:");
			PrintArr(arr);

			Assert::IsTrue(std::is_sorted(arr.begin(), arr.end()));
		}

		TEST_METHOD(A3_EraseTest)
		{
			LeakChecker checker;
			Logger::WriteMessage(__FUNCTION__);

			CArray<int> arr;
			for (auto i = 0; i < m_origNumOfItems; ++i)
			{
				arr.push_back(randInt(m_rng, m_minVal, m_maxVal));
			}
			Logger::WriteMessage(L"Array:");
			PrintArr(arr);

			std::sort(arr.begin(), arr.end());
			Logger::WriteMessage(L"Sorted array:");
			PrintArr(arr);

			for (unsigned int i = 1; i < arr.size(); ++i)
			{
				arr.erase(i);
			}
			Logger::WriteMessage(L"Array after erase:");
			PrintArr(arr);

			Assert::AreEqual(m_origNumOfItems / 2, static_cast<int>(arr.size()));
		}

		TEST_METHOD(A4_InsertTest)
		{
			LeakChecker checker;
			Logger::WriteMessage(__FUNCTION__);

			CArray<int> arr;
			for (auto i = 0; i < m_origNumOfItems; ++i)
			{
				arr.push_back(randInt(m_rng, m_minVal, m_maxVal));
			}
			Logger::WriteMessage(L"Array:");
			PrintArr(arr);

			std::sort(arr.begin(), arr.end());
			Logger::WriteMessage(L"Sorted array:");
			PrintArr(arr);

			for (unsigned int i = 1; i < arr.size(); ++i)
			{
				arr.erase(i);
			}
			Logger::WriteMessage(L"Array after erase:");
			PrintArr(arr);

			for (auto i = 0; i < m_numOfInserts; ++i)
			{
				auto randPos = randInt(m_rng, 0, static_cast<int>(arr.size() - 1));
				auto randNum = randInt(m_rng, m_minVal, m_maxVal);
				arr.insert(randPos, randNum);
			}
			Logger::WriteMessage(L"Array after insert:");
			PrintArr(arr);

			Assert::AreEqual(m_origNumOfItems, static_cast<int>(arr.size()));
		}
		TEST_METHOD(A5_ClearTest)
		{
			LeakChecker checker;
			Logger::WriteMessage(__FUNCTION__);

			CArray<int> arr;
			for (auto i = 0; i < m_origNumOfItems; ++i)
			{
				arr.push_back(randInt(m_rng, m_minVal, m_maxVal));
			}
			Logger::WriteMessage(L"Array:");
			PrintArr(arr);

			std::sort(arr.begin(), arr.end());
			Logger::WriteMessage(L"Sorted array:");
			PrintArr(arr);

			for (unsigned int i = 1; i < arr.size(); ++i)
			{
				arr.erase(i);
			}
			Logger::WriteMessage(L"Array after erase:");
			PrintArr(arr);

			for (auto i = 0; i < m_numOfInserts; ++i)
			{
				auto randPos = randInt(m_rng, 0, static_cast<int>(arr.size() - 1));
				auto randNum = randInt(m_rng, m_minVal, m_maxVal);
				arr.insert(randPos, randNum);
			}
			Logger::WriteMessage(L"Array after insert:");
			PrintArr(arr);

			arr.clear();
			Logger::WriteMessage(L"Array after clear:");
			PrintArr(arr);

			Assert::AreEqual(0, static_cast<int>(arr.size()));
		}
	};

	TEST_CLASS(StrTests)
	{
	private:
		// Input params
		const int m_origNumOfItems = 15;
		const int m_numOfInserts = 3;
		const std::vector<char> m_symbForErase = { 'a', 'b', 'c', 'd', 'e' };

		std::mt19937 m_rng;

	public:
		StrTests()
			: m_rng((std::random_device())())
		{
		}

		TEST_METHOD(A1_AddTest)
		{
			LeakChecker checker;
			Logger::WriteMessage(__FUNCTION__);

			CArray<std::string> arr;
			for (auto i = 0; i < m_origNumOfItems; ++i)
			{
				arr.push_back(randStr(m_rng));
			}
			Logger::WriteMessage(L"Array:");
			PrintArr(arr);

			Assert::AreEqual(m_origNumOfItems, static_cast<int>(arr.size()));
			for (unsigned int i = 0; i < arr.size(); ++i)
			{
				const auto& str = arr[i];
				Assert::IsTrue(std::all_of(str.begin(), str.end(), [](char ch) 
				{
					return std::islower(static_cast<unsigned char>(ch));
				}));
			}
		}

		TEST_METHOD(A2_SortTest)
		{
			LeakChecker checker;
			Logger::WriteMessage(__FUNCTION__);

			CArray<std::string> arr;
			for (auto i = 0; i < m_origNumOfItems; ++i)
			{
				arr.push_back(randStr(m_rng));
			}
			Logger::WriteMessage(L"Array:");
			PrintArr(arr);
			
			std::sort(arr.begin(), arr.end());
			Logger::WriteMessage(L"Sorted array:");
			PrintArr(arr);

			Assert::AreEqual(true, std::is_sorted(arr.begin(), arr.end()));
		}

		TEST_METHOD(A3_EraseTest)
		{
			LeakChecker checker;
			Logger::WriteMessage(__FUNCTION__);

			CArray<std::string> arr;
			for (auto i = 0; i < m_origNumOfItems; ++i)
			{
				arr.push_back(randStr(m_rng));
			}
			Logger::WriteMessage(L"Array:");
			PrintArr(arr);

			std::sort(arr.begin(), arr.end());
			Logger::WriteMessage(L"Sorted array:");
			PrintArr(arr);

			int eraseCount = 0;
			for (unsigned int i = 0; i < arr.size(); ++i)
			{
				const auto& str = arr[i];
				auto isErase = std::any_of(str.begin(), str.end(), [this](char ch) 
				{
					auto isContains = std::find(m_symbForErase.begin(), m_symbForErase.end(), ch) != m_symbForErase.end();
					return isContains;
				});

				if (isErase)
				{
					arr.erase(i);
					i--;
					eraseCount++;
				}
			}
			Logger::WriteMessage(L"Array after erase:");
			PrintArr(arr);

			Assert::AreEqual(m_origNumOfItems - eraseCount, static_cast<int>(arr.size()));

			for (unsigned int i = 0; i < arr.size(); ++i)
			{
				const auto& str = arr[i];
				auto isErase = std::any_of(str.begin(), str.end(), [this](char ch)
				{
					auto isContains = std::find(m_symbForErase.begin(), m_symbForErase.end(), ch) != m_symbForErase.end();
					return isContains;
				});

				if (isErase)
				{
					Logger::WriteMessage(str.c_str());
					Assert::Fail(L"String is not erased from array");
				}
			}
		}

		TEST_METHOD(A4_InsertTest)
		{
			LeakChecker checker;
			Logger::WriteMessage(__FUNCTION__);

			CArray<std::string> arr;
			for (auto i = 0; i < m_origNumOfItems; ++i)
			{
				arr.push_back(randStr(m_rng));
			}
			Logger::WriteMessage(L"Array:");
			PrintArr(arr);

			std::sort(arr.begin(), arr.end());
			Logger::WriteMessage(L"Sorted array:");
			PrintArr(arr);

			for (unsigned int i = 0; i < arr.size(); ++i)
			{
				const auto& str = arr[i];
				auto isErase = std::any_of(str.begin(), str.end(), [this](char ch)
				{
					auto isContains = std::find(m_symbForErase.begin(), m_symbForErase.end(), ch) != m_symbForErase.end();
					return isContains;
				});

				if (isErase)
				{
					arr.erase(i);
				}
			}
			Logger::WriteMessage(L"Array after erase:");
			PrintArr(arr);

			auto sizeBeforeInsert = static_cast<int>(arr.size());
			for (auto i = 0; i < m_numOfInserts; ++i)
			{
				auto randPos = randInt(m_rng, 0, static_cast<int>(arr.size() - 1));
				auto newStr = randStr(m_rng);
				arr.insert(randPos, newStr);
			}
			Logger::WriteMessage(L"Array after insert:");
			PrintArr(arr);

			Assert::AreEqual(sizeBeforeInsert + m_numOfInserts, static_cast<int>(arr.size()));
		}
	};
}