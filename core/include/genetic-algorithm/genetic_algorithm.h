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
            size_t matingPoolSize
        );
        ~GeneticAlgorithm();

        void step();

        inline const std::vector<Town>& getBestRoute() const { return m_fittest->route; }
        inline int getGeneration() const { return m_numGeneration; }

    private:
        void initPopulation();

        void evaluate();

        std::unordered_set<Offspring> select() const;

        Offspring crossover(const std::vector<Offspring>& parents) const;

        void mutate(Offspring& offspring) const;

        std::vector<Offspring> chooseParentsRandomly(const std::unordered_set<Offspring>& matingPool) const;

        float fitness(const Offspring& offspring);

        void updateBestRoute();

    private:
        TravelingSalesmanProblem m_tsp{};

        size_t m_populationSize{};
        size_t m_matingPoolSize{};
        size_t m_selectionSize{};
        std::vector<Offspring> m_population{};
        const Offspring* m_fittest;

        int m_numGeneration{};
    };
}
