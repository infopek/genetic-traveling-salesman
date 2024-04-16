#pragma once

#include <genetic-algorithm/traveling_salesman.h>
#include <genetic-algorithm/offspring.h>
#include <genetic-algorithm/parameter.h>

#include <unordered_set>
#include <vector>

namespace core
{
    class GeneticAlgorithm
    {
    public:
        GeneticAlgorithm(const TravelingSalesmanProblem& tsp, const Parameter& parameter);
        ~GeneticAlgorithm();

        void step();

        inline const std::vector<Town>& getBestRoute() const { return m_fittest->route; }
        inline int getGeneration() const { return m_numGeneration; }
        inline float getBestFitness() const { return m_fittest->fitness; }

    private:
        void initPopulation();

        // Genetic algo methods
        std::unordered_set<Offspring> select() const;

        Offspring crossover(const std::vector<Offspring>& parents) const;

        void mutate(Offspring& offspring) const;

        void evaluate();

        float fitness(const Offspring& offspring);

        std::vector<Offspring> chooseParentsRandomly(const std::unordered_set<Offspring>& matingPool) const;

    private:
        TravelingSalesmanProblem m_tsp{};
        Parameter m_parameter{};

        std::vector<Offspring> m_population{};
        const Offspring* m_fittest;

        int m_numGeneration{};
    };
}
