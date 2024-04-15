#pragma once

#include <genetic-algorithm/traveling_salesman.h>
#include <genetic-algorithm/offspring.h>

#include <unordered_set>
#include <vector>

namespace core
{
    class GeneticAlgorithm
    {
    public:
        GeneticAlgorithm(
            const TravelingSalesmanProblem& tsp,
            size_t populationSize,
            size_t selectionSize,
            size_t matingPoolSize,
            float crossoverRate,
            float mutationRate
        );
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

        // Other
        void updateBestRoute();

    private:
        TravelingSalesmanProblem m_tsp{};

        size_t m_populationSize{};
        size_t m_matingPoolSize{};
        size_t m_selectionSize{};

        float m_crossoverRate{};
        float m_mutationRate{};

        std::vector<Offspring> m_population{};
        const Offspring* m_fittest;

        int m_numGeneration{};
    };
}
