#include <genetic-algorithm/traveling_salesman.h>
#include <genetic-algorithm/genetic_algorithm.h>
#include <visualizer/visualizer.h>

#include <iostream>

using namespace core;
using namespace vis;

int main()
{
    std::vector<Town> towns = {
        {100.0f, 100.0f},
        {200.0f, 200.0f},
        {300.0f, 400.0f},
        {500.0f, 300.0f},
        {600.0f, 100.0f},
        {700.0f, 200.0f},
        {400.0f, 100.0f},
        {200.0f, 500.0f},
        {300.0f, 200.0f},
        {100.0f, 400.0f}
    };

    // TSP
    TravelingSalesmanProblem tsp{};
    tsp.saveTownsToFile("towns.txt", towns);
    tsp.loadTownsFromFile("towns.txt");

    // GA
    const size_t populationSize = 50;
    const size_t selectionSize = 6;
    const size_t matingPoolSize = 4;
    GeneticAlgorithm ga(tsp, populationSize, selectionSize, matingPoolSize);

    // Visualizer
    GAVisualizer visualizer(ga);

    visualizer.draw();

    return 0;
}