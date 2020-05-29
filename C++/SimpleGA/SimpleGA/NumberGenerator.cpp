#pragma once

#include <random>

#include "NumberGenerator.h"

namespace NumberGenerator
{
	std::vector<BinaryNum> GenerateRandPopulation(const size_t size)
	{
		if (size == 0)
			throw std::runtime_error("Size of population can't be empty");

		std::vector<BinaryNum> randNums(size);

		// Non-deterministic random number (after operator ())
		std::random_device seeder;
		// Random number engine
		std::mt19937 engine{ seeder() };
		// For generation boolean random values
		std::bernoulli_distribution dist;

		// Fill population
		std::generate(randNums.begin(), randNums.end(), [&dist, &engine]()
		{
			BinaryNum binVec;
			for (auto i = 0; i < InputData::numBitsOfBinVec; i++)
				binVec.set(i, dist(engine));

			return binVec;
		});

		return randNums;
	}

	double GenerateRandDouble(const double begin, const double end)
	{
		std::random_device seeder;
		std::mt19937 engine{ seeder() };
		// For generation double random values
		std::uniform_real_distribution<> dist(begin, end);

		return dist(engine);
	}

	int GenerateRandInt(const int begin, const int end)
	{
		std::random_device seeder;
		std::mt19937 engine{ seeder() };
		// For generation int random values
		std::uniform_int_distribution<> dist(begin, end);

		return dist(engine);
	}
}