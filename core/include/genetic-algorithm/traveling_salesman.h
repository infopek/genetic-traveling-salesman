#pragma once

#include <string>
#include <vector>

namespace core
{
    class Town
    {
    public:
        float x;
        float y;

        bool operator==(const Town& other) const
        {
            return x == other.x && y == other.y;
        }
    };

    class TravelingSalesmanProblem
    {
    public:
        void loadTownsFromFile(const std::string& fileName);
        void saveTownsToFile(const std::string& fileName, const std::vector<Town>& townVector);

        float objective(const std::vector<Town>& solution);

        inline const std::vector<Town>& getTowns() const { return m_towns; }

    private:
        std::vector<Town> m_towns;
    };
}

