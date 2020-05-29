#pragma once

#include <vector>
#include <bitset>
#include <iostream>

namespace InputData
{
	constexpr auto sizeOfPopulation = 20;
	constexpr auto numIterations = 3;
	constexpr auto leftIntevalValue = -10;
	constexpr auto rightIntevalValue = 10;
	constexpr auto numBitsOfBinVec = 15; //todo
	// Crossover probability
	constexpr auto probabilityCrossover = 0.5;
	// Mutation probability
	constexpr auto probabilityMutation = 0.001;

	// Target function can't be a fitness fucntion in GA 
	// because in this example there are negative values 
	// and also the problem of finding the minimum (not only the maximum)
	auto targetFunc = [](const std::vector<double>& xValues)
	{
		std::vector<double> yValues;
		for (const auto& xValue : xValues)
		{
			auto yValue = cos(xValue - 0.5) / abs(xValue);
			// Round up to 3 significant digits
			yValue = std::round(yValue * 1000.0) / 1000.0;
			yValues.push_back(yValue);
		}

		return yValues;
	};

	// Fitness function for minimum	
	auto fitnessFuncMin = [](const std::vector<double>& xValues)
	{
		std::vector<double> yValues;
		for (const auto& xValue : xValues)
		{
			auto yValue = (1 - cos(xValue - 0.5)) / abs(xValue);
			// Round up to 3 significant digits
			//yValue = std::round(yValue * 1000.0) / 1000.0;
			yValues.push_back(yValue);
		}

		return yValues;
	};

	// Fitness function for maximum
	auto fitnessFuncMax = [](const std::vector<double>& xValues)
	{
		std::vector<double> yValues;
		for (const auto& xValue : xValues)
		{
			auto yValue = (1 + cos(xValue - 0.5)) / abs(xValue);
			// Round up to 3 significant digits
			//yValue = std::round(yValue * 1000.0) / 1000.0;
			yValues.push_back(yValue);
		}

		return yValues;
	};
}

//using BinaryNum = std::bitset<InputData::numBitsOfBinVec>;
