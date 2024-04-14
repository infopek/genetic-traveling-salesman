#pragma once

#include "traveling_salesman.h"

namespace core
{
    struct Offspring
    {
        std::vector<Town> route{};
        float fitness{};

        bool operator==(const Offspring& other) const
        {
            return route == other.route && fitness == other.fitness;
        }

        friend std::size_t hashValue(const Offspring& offspring)
        {
            std::size_t seed = 0;
            for (const auto& town : offspring.route)
            {
                seed ^= std::hash<float>{}(town.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                seed ^= std::hash<float>{}(town.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            seed ^= std::hash<float>{}(offspring.fitness) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };


}

namespace std
{
    template <>
    struct hash<core::Offspring>
    {
        std::size_t operator()(const core::Offspring& offspring) const
        {
            return hashValue(offspring);
        }
    };
}
