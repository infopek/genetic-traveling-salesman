#pragma once

#include <genetic-algorithm/parameter_defaults.h>

namespace core
{
    class Parameter
    {
    public:
        Parameter();
        ~Parameter();

        inline size_t getPopulationSize() const { return m_populationSize; }
        inline size_t getParentSelectionSize() const { return m_parentSelectionSize; }
        inline size_t getMatingPoolSize() const { return m_matingPoolSize; }

        inline float getCrossoverRate() const { return m_crossoverRate; }
        inline float getMutationRate() const { return m_mutationRate; }

        // TODO: validation
        void setPopulationSize(size_t value);
        void setParentSelectionSize(size_t value);
        void setMatingPoolSize(size_t value);

        void setCrossoverRate(float value);
        void setMutationRate(float value);

    private:
        size_t m_populationSize{ populationSizeDefault };
        size_t m_parentSelectionSize{ parentSelectionSizeDefault };
        size_t m_matingPoolSize{ matingPoolSizeDefault };

        float m_crossoverRate{ crossoverRateDefault };
        float m_mutationRate{ mutationRateDefault };
    };
}
