#include <genetic-algorithm/parameter.h>

namespace core
{
    Parameter::Parameter()
    {
    }

    Parameter::~Parameter()
    {
    }

    void Parameter::setPopulationSize(size_t value)
    {
        m_populationSize = value;
    }

    void Parameter::setParentSelectionSize(size_t value)
    {
        m_parentSelectionSize = value;
    }

    void Parameter::setMatingPoolSize(size_t value)
    {
        m_matingPoolSize = value;
    }

    void Parameter::setCrossoverRate(float value)
    {
        m_crossoverRate = value;
    }

    void Parameter::setMutationRate(float value)
    {
        m_mutationRate = value;
    }
}
