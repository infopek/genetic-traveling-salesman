#include <genetic-algorithm/traveling_salesman.h>
#include <genetic-algorithm/genetic_algorithm.h>
#include <visualizer/visualizer.h>
#include <common/random.h>

#include <iostream>

using namespace core;
using namespace vis;

int main()
{
    // Window settings
    const unsigned int windowWidth = 1200;
    const unsigned int windowHeight = 800;

    // Towns
    const int numTowns = 41;
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
    Parameter parameter{};
    GeneticAlgorithm ga(tsp, parameter);

    // Visualizer
    GAVisualizer visualizer(ga, windowWidth, windowHeight);
    visualizer.draw();

    return 0;
}