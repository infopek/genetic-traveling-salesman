#pragma once

#include <genetic-algorithm/genetic_algorithm.h>

#include <SFML/Graphics.hpp>

namespace vis
{
    class GAVisualizer
    {
    public:
        GAVisualizer(core::GeneticAlgorithm& ga);
        ~GAVisualizer();

        void draw();

    private:
        void drawPoints();

        void drawLines();

        void displayStats();

        void updateRoute();

    private:
        core::GeneticAlgorithm& m_ga;
        std::vector<sf::Vector2f> m_route;

        sf::RenderWindow m_window;
        sf::VertexArray m_lines;

        sf::Font m_font;
    };
}

