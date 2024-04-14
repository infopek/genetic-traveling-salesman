#include <visualizer/visualizer.h>

namespace vis
{
    GAVisualizer::GAVisualizer(core::GeneticAlgorithm& ga)
        : m_ga{ ga }
    {
        m_window.create(sf::VideoMode(800, 600), "Genetic Algorithm for TSP");
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
                    m_window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
        sf::Text generationText;
        generationText.setFont(m_font);
        generationText.setString("Generation: " + std::to_string(m_ga.getGeneration()));
        generationText.setCharacterSize(24);
        generationText.setFillColor(sf::Color::Black);
        generationText.setPosition(600, 0);

        m_window.draw(generationText);
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