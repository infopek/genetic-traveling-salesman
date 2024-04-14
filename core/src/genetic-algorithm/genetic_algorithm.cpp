#include <genetic-algorithm/genetic_algorithm.h>

#include "../random.h"

#include <algorithm>
#include <cassert>

namespace core
{
    GeneticAlgorithm::GeneticAlgorithm(
        const TravelingSalesmanProblem& tsp,
        size_t m_populationSize,
        size_t selectionSize,
        size_t matingPoolSize
    )
        :
        m_tsp{ tsp },
        m_populationSize{ m_populationSize },
        m_selectionSize{ selectionSize },
        m_matingPoolSize{ matingPoolSize }
    {
        assert(m_populationSize > 0 &&
            m_selectionSize > 0 &&
            m_matingPoolSize > 0 &&
            "Size parameters have to be greater than 0");

        initPopulation();
        evaluate();
        m_fittest = &m_population[0];
    }

    GeneticAlgorithm::~GeneticAlgorithm()
    {
    }

    void GeneticAlgorithm::step()
    {
        std::unordered_set<Offspring> matingPool = select();

        std::vector<Offspring> newPopulation{};
        newPopulation.reserve(m_populationSize);
        while (newPopulation.size() < m_populationSize)
        {
            std::vector<Offspring> parents = chooseParentsRandomly(matingPool);

            Offspring newOffspring = crossover(parents);
            mutate(newOffspring);

            newPopulation.push_back(newOffspring);
        }

        m_population = newPopulation;
        evaluate();
        updateBestRoute();

        ++m_numGeneration;
    }

    void GeneticAlgorithm::initPopulation()
    {
        m_population.reserve(m_populationSize);
        for (size_t i = 0; i < m_populationSize; i++)
        {
            // Shuffle a copy of towns
            std::vector<Town> randomRoute = m_tsp.getTowns();
            std::shuffle(randomRoute.begin(), randomRoute.end(), Random::mt);

            Offspring offspring{ .route = randomRoute };
            m_population.push_back(offspring);
        }
    }

    std::unordered_set<Offspring> GeneticAlgorithm::select() const
    {
        std::unordered_set<Offspring> selected{};

        // Perform tournament selection
        while (selected.size() < m_matingPoolSize)
        {
            std::vector<const Offspring*> tournamentParticipants{};
            for (size_t i = 0; i < m_matingPoolSize; ++i)
            {
                const Offspring& participant = m_population[Random::get(0, m_populationSize - 1)];
                tournamentParticipants.push_back(&participant);
            }

            const Offspring* bestParticipant = *std::min_element(tournamentParticipants.begin(), tournamentParticipants.end(),
                [](const Offspring* a, const Offspring* b) {
                    return a->fitness < b->fitness;
                });

            selected.insert(*bestParticipant);
        }

        return selected;
    }

    Offspring GeneticAlgorithm::crossover(const std::vector<Offspring>& parents) const
    {
        // Randomly select two distinct points in the route
        size_t point1 = Random::get(0, parents[0].route.size() - 1);
        size_t point2 = Random::get(0, parents[0].route.size() - 1);
        while (point1 == point2)
            point2 = Random::get(0, parents[0].route.size() - 1);
        if (point1 > point2)
            std::swap(point1, point2);

        // Create the child's route by copying a segment from the first parent
        Offspring child;
        child.route.reserve(parents[0].route.size());
        child.route.insert(child.route.end(), parents[0].route.begin() + point1, parents[0].route.begin() + point2);

        // Fill the rest of the child's route with cities from the second parent
        for (const Town& town : parents[1].route)
        {
            if (!std::count(child.route.begin(), child.route.end(), town))
            {
                child.route.push_back(town);
            }
        }

        return child;
    }

    void GeneticAlgorithm::mutate(Offspring& offspring) const
    {

    }

    std::vector<Offspring> GeneticAlgorithm::chooseParentsRandomly(const std::unordered_set<Offspring>& matingPool) const
    {
        std::vector<Offspring> parents;

        std::vector<Offspring> poolVector(matingPool.begin(), matingPool.end());

        size_t selectionSize = std::min(m_selectionSize, m_matingPoolSize);

        std::sample(poolVector.begin(), poolVector.end(),
            std::back_inserter(parents), selectionSize, Random::mt);

        return parents;
    }

    void GeneticAlgorithm::evaluate()
    {
        for (auto& offspring : m_population)
        {
            offspring.fitness = fitness(offspring);
        }
    }

    float GeneticAlgorithm::fitness(const Offspring& offspring)
    {
        return m_tsp.objective(offspring.route);
    }

    void GeneticAlgorithm::updateBestRoute()
    {
        for (const auto& offspring : m_population)
        {
            if (offspring.fitness < m_fittest->fitness)
            {
                m_fittest = &offspring;
            }
        }
    }
}