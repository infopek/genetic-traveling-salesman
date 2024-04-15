#include <genetic-algorithm/traveling_salesman.h>
#include <genetic-algorithm/genetic_algorithm.h>
#include <visualizer/visualizer.h>
#include <common/random.h>

#include <iostream>

using namespace core;
using namespace vis;

int main()
{
    // Parameters
    const unsigned int windowWidth = 1200;
    const unsigned int windowHeight = 800;

    const int numTowns = 20;

    const size_t populationSize = 100;
    const size_t selectionSize = 10;
    const size_t matingPoolSize = 14;
    const float crossoverRate = 0.78f;
    const float mutationRate = 0.4f;

    // Towns
    std::vector<Town> towns(numTowns);
    for (int i = 0; i < numTowns; i++)
    {
        towns[i] = Town{
            .x = Random::get<float>(10.0f, static_cast<float>(windowWidth) - 50.0f),
            .y = Random::get<float>(10.0f, static_cast<float>(windowHeight) - 50.0f)
        };
    }

    // TSP
    TravelingSalesmanProblem tsp{};
    tsp.saveTownsToFile("towns.txt", towns);
    tsp.loadTownsFromFile("towns.txt");

    // GA
    GeneticAlgorithm ga(tsp,
        populationSize,
        selectionSize,
        matingPoolSize,
        crossoverRate,
        mutationRate);

    // Visualizer
    GAVisualizer visualizer(ga, windowWidth, windowHeight);

    visualizer.draw();

    return 0;
}