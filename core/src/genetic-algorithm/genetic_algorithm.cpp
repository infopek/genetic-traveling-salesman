#include <genetic-algorithm/genetic_algorithm.h>
#include <common/random.h>

#include <algorithm>
#include <iostream>
#include <cassert>
#include <unordered_map>

namespace core
{
    GeneticAlgorithm::GeneticAlgorithm(const TravelingSalesmanProblem& tsp, const Parameter& parameter)
        : m_tsp{ tsp }, m_parameter{ parameter }
    {
        initPopulation();
        evaluate();
    }

    GeneticAlgorithm::~GeneticAlgorithm()
    {
    }

    void GeneticAlgorithm::step()
    {
        std::unordered_set<Offspring> matingPool = select();

        std::vector<Offspring> newPopulation{};
        newPopulation.reserve(m_parameter.getPopulationSize());
        while (newPopulation.size() < m_parameter.getPopulationSize())
        {
            std::vector<Offspring> parents = chooseParentsRandomly(matingPool);

            Offspring newOffspring = (Random::get<float>(0.0f, 1.0f) <= m_parameter.getCrossoverRate())
                ? crossover(parents)
                : parents[Random::get(0, parents.size() - 1)];

            if (Random::get<float>(0.0f, 1.0f) <= m_parameter.getMutationRate())
                mutate(newOffspring);

            newPopulation.push_back(newOffspring);
        }

        m_population = newPopulation;
        evaluate();

        ++m_numGeneration;
    }

    void GeneticAlgorithm::initPopulation()
    {
        m_population.reserve(m_parameter.getPopulationSize());
        for (size_t i = 0; i < m_parameter.getPopulationSize(); i++)
        {
            std::vector<Town> randomRoute = m_tsp.getTowns();
            std::shuffle(randomRoute.begin(), randomRoute.end(), Random::mt);

            Offspring offspring;
            offspring.route = randomRoute;
            m_population.push_back(offspring);
        }
    }

    std::unordered_set<Offspring> GeneticAlgorithm::select() const
    {
        std::unordered_set<Offspring> matingPool{};

        // Perform tournament selection
        while (matingPool.size() < m_parameter.getMatingPoolSize())
        {
            std::vector<const Offspring*> tournamentParticipants{};
            for (size_t i = 0; i < m_parameter.getMatingPoolSize(); ++i)
            {
                const Offspring& participant = m_population[Random::get(0, m_parameter.getPopulationSize() - 1)];
                tournamentParticipants.push_back(&participant);
            }

            const Offspring* bestParticipant = *std::min_element(tournamentParticipants.begin(), tournamentParticipants.end(),
                [](const Offspring* a, const Offspring* b) {
                    return a->fitness < b->fitness;
                });

            matingPool.insert(*bestParticipant);
        }

        return matingPool;
    }

    Offspring GeneticAlgorithm::crossover(const std::vector<Offspring>& parents) const
    {
        const size_t numParents = parents.size();
        const size_t numTowns = m_tsp.getTowns().size();

        // Get two distinct parents
        size_t parent1Idx = Random::get(0, numParents - 1);
        size_t parent2Idx = Random::get(0, numParents - 1);
        while (parent1Idx == parent2Idx)
            parent2Idx = Random::get(0, numParents - 1);

        const auto& parent1 = parents[parent1Idx];
        const auto& parent2 = parents[parent2Idx];

        // Get random range [0, numTowns)
        const int r1 = Random::get(0, numTowns - 1);
        const int r2 = Random::get(0, numTowns - 1);

        const int lo = std::min(r1, r2);
        const int hi = std::max(r1, r2);

        // Copy the range of parent1 to child
        Offspring child{};
        auto& route = child.route;
        route.resize(numTowns);
        for (int i = lo; i <= hi; i++)
            route[i] = parent1.route[i];

        // Fill rest with other parent
        int childIdx = (hi + 1) % numTowns;
        int parentIdx = (hi + 1) % numTowns;
        int missing = numTowns - (hi - lo + 1);
        while (missing > 0)
        {
            while (std::find(route.begin(), route.end(), parent2.route[parentIdx]) != route.end())
                parentIdx = (parentIdx + 1) % numTowns;

            route[childIdx] = parent2.route[parentIdx];
            childIdx = (childIdx + 1) % numTowns;
            parentIdx = (parentIdx + 1) % numTowns;
            --missing;
        }

        return child;
    }

    void GeneticAlgorithm::mutate(Offspring& offspring) const
    {
        const size_t numTowns = m_tsp.getTowns().size();

        size_t gene1 = Random::get(0, numTowns - 1);
        size_t gene2 = Random::get(0, numTowns - 1);
        while (gene1 == gene2)
            gene2 = Random::get(0, numTowns - 1);

        std::swap(offspring.route[gene1], offspring.route[gene2]);
    }

    std::vector<Offspring> GeneticAlgorithm::chooseParentsRandomly(const std::unordered_set<Offspring>& matingPool) const
    {
        std::vector<Offspring> parents{};

        std::vector<Offspring> pool(matingPool.begin(), matingPool.end());

        std::sample(pool.begin(), pool.end(),
            std::back_inserter(parents), m_parameter.getParentSelectionSize(), Random::mt);

        return parents;
    }

    void GeneticAlgorithm::evaluate()
    {
        m_fittest = &m_population[0];
        for (auto& offspring : m_population)
        {
            offspring.fitness = fitness(offspring);
            if (offspring.fitness < m_fittest->fitness)
                m_fittest = &offspring;
        }
    }

    float GeneticAlgorithm::fitness(const Offspring& offspring)
    {
        return m_tsp.objective(offspring.route);
    }
}