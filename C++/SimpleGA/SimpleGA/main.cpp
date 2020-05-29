#include "NumberGenerator.h"
#include "GeneticAlgorithm.h"

int main()
{
	try
	{
		// Source population
		auto srcPopulation = NumberGenerator::GenerateRandPopulation(InputData::sizeOfPopulation);

		GeneticAlgorithm ga(std::move(srcPopulation), GeneticAlgorithm::Min);
		ga.PerformGA();

		std::cout << "Result of GA = " << ga.GetExtremum() << std::endl;
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << "The program terminated with error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}