#include <numeric>
#include <random>

#include "GeneticAlgorithm.h"
#include "NumberGenerator.h"

GeneticAlgorithm::GeneticAlgorithm(std::vector<BinaryNum>&& population, TypeExtremum exType)
	:_exType(exType),
	_currentPopulation(std::move(population))
{
	if (_currentPopulation.empty())
		throw std::runtime_error("Source population can't be empty");
	
	if (InputData::numIterations <= 0)
		throw std::runtime_error("Count of iteration must be greater than 0");

	if (InputData::numBitsOfBinVec <= 0)
		throw std::runtime_error("Count of iteration must be greater than 0");

	if (InputData::probabilityCrossover > 1 || InputData::probabilityCrossover < 0)
		throw std::runtime_error("Crossover probability should be between 0 and 1");

	if (InputData::probabilityMutation > 1 || InputData::probabilityMutation < 0)
		throw std::runtime_error("Mutation probability should be between 0 and 1");
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::PerformGA()
{
	for (auto i = 0; i < InputData::numIterations; i++)
	{
		_currentPopulation = PerformGAIteraion(_currentPopulation);
	}

	// Convert to double nums
	auto populationDouble = FromBinToDouble(_currentPopulation);
	// Get results from target function
	auto populationResult = InputData::targetFunc(populationDouble);
	if (_exType == Min)
		_extremum = *std::min_element(populationResult.begin(), populationResult.end());
	else if (_exType == Max)
		_extremum = *std::max_element(populationResult.begin(), populationResult.end());;
}

double GeneticAlgorithm::GetExtremum() const
{
	return _extremum;
}


std::vector<BinaryNum> GeneticAlgorithm::PerformGAIteraion(const std::vector<BinaryNum>& currentPopulation)
{
	auto resultRepr = Reproduction(currentPopulation);
	auto resultCros = Crossover(resultRepr);
	auto resultPopulGA = Mutation(resultCros);

	return resultPopulGA;
}

std::vector<BinaryNum> GeneticAlgorithm::Reproduction(const std::vector<BinaryNum>& currentPopulation)
{
	std::vector<BinaryNum> resultPopulation;

	// Convert to double nums
	auto populationDouble = FromBinToDouble(currentPopulation);

	// Get results from target function (for tests)
	//auto populationResult = InputData::targetFunc(populationDouble);

	// Get fitness values for min/max
	auto fitnessValMin = InputData::fitnessFuncMin(populationDouble);
	auto fitnessValMax = InputData::fitnessFuncMax(populationDouble);

	// Normalize the values
	auto normalizeMin = std::accumulate(fitnessValMin.begin(), fitnessValMin.end(), 0.0);
	auto normalizeMax = std::accumulate(fitnessValMax.begin(), fitnessValMax.end(), 0.0);
	
	// Get the selection probabilities
	std::vector<double> selProbsMin;
	std::vector<double> selProbsMax;
	for (auto i = 0; i < InputData::sizeOfPopulation; i++)
	{
		selProbsMin.emplace_back(fitnessValMin[i] / normalizeMin);
		selProbsMax.emplace_back(fitnessValMax[i] / normalizeMax);
	}

	// Roulette Wheel Selection
	if (_exType == Min)
		resultPopulation = RWS(currentPopulation, selProbsMin);
	else if (_exType == Max)
		resultPopulation = RWS(currentPopulation, selProbsMax);

	return resultPopulation;
}

std::vector<BinaryNum> GeneticAlgorithm::Crossover(const std::vector<BinaryNum>& currentPopulation)
{
	auto resultPopulation = currentPopulation;

	for (auto i = 0; i < InputData::sizeOfPopulation / 2; i++)
	{
		// Current crossover probability
		auto rndCrosProb = NumberGenerator::GenerateRandDouble();

		// Crossover probability worked
		if (rndCrosProb < InputData::probabilityCrossover)
		{
			// Cross point for crossover
			auto rndCrossPoint = NumberGenerator::GenerateRandInt(1, InputData::numBitsOfBinVec);
			
			auto& firstÑhromosome = resultPopulation[i];
			auto& secondÑhromosome = resultPopulation[i + 1];

			// Change the substrings after the crossing point
			for (auto y = rndCrossPoint - 1; y < InputData::numBitsOfBinVec; y++)
			{
				auto tmpBinVal = firstÑhromosome.test(y);
				firstÑhromosome.set(y, secondÑhromosome.test(y));
				secondÑhromosome.set(y, tmpBinVal);
			}
		}
		else
			continue;
	}

	return resultPopulation;
}

std::vector<BinaryNum> GeneticAlgorithm::Mutation(const std::vector<BinaryNum>& currentPopulation)
{
	std::vector<BinaryNum> resultPopulation = currentPopulation;

	// Current mutation probability
	auto rndMutProb = NumberGenerator::GenerateRandDouble();

	for (auto& chromosome : resultPopulation)
	{
		// Mutation probability worked
		if (rndMutProb < InputData::probabilityMutation)
		{
			// Random bit in chromosome for mutation
			auto rndMutationBit = NumberGenerator::GenerateRandInt(1, InputData::numBitsOfBinVec);
			
			// Perform inversion of the received bit
			chromosome.flip(rndMutationBit - 1);
		}
		else
			continue;
	}

	return resultPopulation;
}

std::vector<BinaryNum> GeneticAlgorithm::RWS(const std::vector<BinaryNum>& currentPopulation, const std::vector<double>& probabilities)
{
	std::default_random_engine generator;
	std::discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
	std::vector<int> indices(probabilities.size());
	std::vector<BinaryNum> resultPopulation(probabilities.size());

	std::generate(indices.begin(), indices.end(), [&generator, &dist]() { return dist(generator); });
	std::transform(indices.begin(), indices.end(), resultPopulation.begin(), [&currentPopulation](int index) { return currentPopulation[index]; });

	return resultPopulation;
}

std::vector<double> GeneticAlgorithm::FromBinToDouble(const std::vector<BinaryNum>& binNums)
{
	std::vector<double> doubleNums;
	for (const auto& binNum : binNums)
	{
		//std::cout << "BINARY = " << binNum << std::endl;

		// 1. Convert from bin to dec number
		auto decNum = 0;
		for (auto i = 0; i < binNum.size(); i++)
			decNum += binNum[i] * pow(2, i);

		// 2. Calculation real number
		auto realNum = InputData::leftIntevalValue + decNum * 
			((InputData::rightIntevalValue - InputData::leftIntevalValue) / (pow(2.0, InputData::numBitsOfBinVec) - 1));

		// Round up to 3 significant digits
		realNum = std::round(realNum * 1000.0) / 1000.0;

		doubleNums.push_back(realNum);
	}

	return doubleNums;
}
