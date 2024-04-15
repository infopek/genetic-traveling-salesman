#pragma once

#include "traveling_salesman.h"

namespace core
{
    static int64_t offspringId = 0;

    struct Offspring
    {
        Offspring()
            : id(offspringId++)
        {
        }

        int64_t id;
        std::vector<Town> route{};
        float fitness{};

        bool operator==(const Offspring& other) const
        {
            return id == other.id;
        }

        friend std::size_t hashValue(const Offspring& offspring)
        {
            std::size_t seed = 0;
            seed ^= std::hash<int64_t>{}(offspring.id);
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
