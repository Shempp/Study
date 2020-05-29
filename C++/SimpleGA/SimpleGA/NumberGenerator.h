#pragma once

#include "InputData.h"

using BinaryNum = std::bitset<InputData::numBitsOfBinVec>;

namespace NumberGenerator
{
	std::vector<BinaryNum> GenerateRandPopulation(const size_t size);
	double GenerateRandDouble(const double begin = 0.0, const double end = 1.0);
	int GenerateRandInt(const int begin = 0, const int end = 1);
}

