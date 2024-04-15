#include <visualizer/visualizer.h>

#include <cmath>

namespace vis
{
    GAVisualizer::GAVisualizer(core::GeneticAlgorithm& ga, unsigned int windowWidth, unsigned int windowHeight)
        : m_ga{ ga },
        m_windowWidth{ windowWidth },
        m_windowHeight{ windowHeight }
    {
        m_window.create(sf::VideoMode(windowWidth, windowHeight), "Genetic Algorithm for TSP");
        m_lines.setPrimitiveType(sf::LinesStrip);

        if (!m_font.loadFromFile("../../../visualizer/res/fonts/arial.ttf")) {}
    }

    GAVisualizer::~GAVisualizer()
    {
    }

    void GAVisualizer::draw()
    {
        while (m_window.isOpen())
        {
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    m_window.close();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    m_ga.step();
                    updateRoute();
                }
            }

            m_window.clear(sf::Color::White);

            drawLines();
            drawPoints();
            displayStats();

            m_window.display();
        }
    }

    void GAVisualizer::drawPoints()
    {
        for (size_t i = 0; i < m_route.size(); ++i)
        {
            const auto& town = m_route[i];

            // Draw town
            sf::CircleShape townCircle(5.0f);
            townCircle.setFillColor(sf::Color::Red);
            townCircle.setOrigin(townCircle.getRadius(), townCircle.getRadius());
            townCircle.setPosition(town);

            // Draw town number
            sf::Text townNumber;
            townNumber.setFont(m_font);
            townNumber.setString(std::to_string(i + 1));
            townNumber.setCharacterSize(12);
            townNumber.setFillColor(sf::Color::Black);
            townNumber.setPosition(town.x + 10, town.y - 10);

            m_window.draw(townCircle);
            m_window.draw(townNumber);
        }
    }

    void GAVisualizer::drawLines()
    {
        for (size_t i = 1; i < m_route.size(); ++i)
        {
            sf::Vertex line[] = {
                sf::Vertex(m_route[i - 1], sf::Color::Black),
                sf::Vertex(m_route[i], sf::Color::Black)
            };

            m_window.draw(line, 2, sf::Lines);
        }
    }

    void GAVisualizer::displayStats()
    {
        // Generation number
        sf::Text generationText;
        generationText.setFont(m_font);
        generationText.setString("Generation: " + std::to_string(m_ga.getGeneration()));
        generationText.setCharacterSize(15);
        generationText.setFillColor(sf::Color::Black);
        generationText.setPosition(m_windowWidth - 150, 0);

        // Best fitness
        sf::Text bestFitness;
        bestFitness.setFont(m_font);
        bestFitness.setString("Best fitness: " + std::to_string(static_cast<int>(m_ga.getBestFitness())));
        bestFitness.setCharacterSize(15);
        bestFitness.setFillColor(sf::Color::Black);
        bestFitness.setPosition(m_windowWidth - 150, 30);

        m_window.draw(generationText);
        m_window.draw(bestFitness);
    }

    void GAVisualizer::updateRoute()
    {
        const auto& towns = m_ga.getBestRoute();
        std::vector<sf::Vector2f> points{};
        std::transform(towns.begin(), towns.end(), std::back_inserter(points),
            [](const core::Town& town) {
                return sf::Vector2f(town.x, town.y);
            });
        m_route = points;
    }
}