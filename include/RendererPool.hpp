/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** RendererPool
*/

#ifndef EPITECH_RAYTRACER_RENDERERPOOL_HPP
#define EPITECH_RAYTRACER_RENDERERPOOL_HPP
#include "IRenderer.hpp"

typedef std::vector<std::unique_ptr<Raytracer::IRenderer>> UniqueRendererVector;

namespace Raytracer {

    class RendererPool: public IRenderer {
    public:
        RendererPool(sf::Vector2u start, sf::Vector2u end);
        ~RendererPool() override = default;

        void addRenderer(std::unique_ptr<IRenderer> &&renderer);
        void setRange(sf::Vector2u start, sf::Vector2u end) override;

        void render(const Scene &scene) override;
        sf::VertexArray getVertexArray() const override;
        int getThreadsCount() const override;
        static int getThreadsCount(const UniqueRendererVector &renderers);

        /**
         * @brief Split a range into multiple ranges, each with the same height.
         */
        static std::vector<std::pair<sf::Vector2u, sf::Vector2u>> splitRange(sf::Vector2u start, sf::Vector2u end, std::size_t count);

        typedef std::map<IRenderer *, std::pair<sf::Vector2u, sf::Vector2u>> RendererRangeMap;
        /**
         * @brief Split a range into multiple ranges, each with the same height. This method only uses the 'getThreadsCount' method on renderers.
         * @param start The start of the range.
         * @param end The end of the range.
         * @param renderers The renderers to split.
         * @return A map of renderers and their ranges.
         */
        static RendererRangeMap splitRange(sf::Vector2u start, sf::Vector2u end, const UniqueRendererVector &renderers);
    private:
        void internalSetRange(sf::Vector2u start, sf::Vector2u end);
        std::vector<std::unique_ptr<IRenderer>> _renderers;
        sf::VertexArray _vertexArray;
        sf::Vector2u _start, _end;
    };
}

#endif //EPITECH_RAYTRACER_RENDERERPOOL_HPP
