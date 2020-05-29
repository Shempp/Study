#pragma once

#include <functional>

#include "NumberGenerator.h"

class GeneticAlgorithm
{
public:
	using FuncValues = std::function<std::vector<double>(const std::vector<double>&)>;

	enum TypeExtremum
	{
		Min,
		Max
	};

	GeneticAlgorithm(std::vector<BinaryNum>&& population, TypeExtremum exType);
	~GeneticAlgorithm();

	void PerformGA();
	double GetExtremum() const;

private:
	// Basic operators of the genetic algorithm
	std::vector<BinaryNum> Reproduction(const std::vector<BinaryNum>& currentPopulation);
	std::vector<BinaryNum> Crossover(const std::vector<BinaryNum>& currentPopulation);
	std::vector<BinaryNum> Mutation(const std::vector<BinaryNum>& currentPopulation);

	// One iteration of genetic algorithm
	std::vector<BinaryNum> PerformGAIteraion(const std::vector<BinaryNum>& currentPopulation);

	// Helper functions for basic operators of GA
	std::vector<BinaryNum> RWS(const std::vector<BinaryNum>& currentPopulation, const std::vector<double>& probabilities);
	std::vector<double> FromBinToDouble(const std::vector<BinaryNum>& binNums);

	std::vector<BinaryNum> _currentPopulation;
	const TypeExtremum _exType;
	double _extremum;
};

