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
        RendererPool(sf::Vector2u start, sf::Vector2u end, bool updateRangeOnRender = false);
        ~RendererPool() override = default;

        void addRenderer(std::unique_ptr<IRenderer> &&renderer);
        void setRange(sf::Vector2u start, sf::Vector2u end) override;
        std::pair<sf::Vector2u, sf::Vector2u> getRange() const override;
        void setRange();

        void render(const Scene &scene, PointArray &array, sf::Time *time) override;
        int getThreadsCount() const override;
        static int getThreadsCount(const UniqueRendererVector &renderers);

        typedef std::map<IRenderer *, std::pair<sf::Vector2u, sf::Vector2u>> RendererRangeMap;
        /**
         * @brief Split a range into multiple ranges, each with the same height. This method only uses the 'getThreadsCount' method on renderers.
         * @param start The start of the range.
         * @param end The end of the range.
         * @param renderers The renderers to split.
         * @return A map of renderers and their ranges.
         */
        static RendererRangeMap splitRange(sf::Vector2u start, sf::Vector2u end, const UniqueRendererVector &renderers);

        void reset() override;
        void reset(const std::unique_ptr<IRenderer> &renderers = nullptr);

        const std::vector<std::unique_ptr<IRenderer>> &getSubRenderers() override;
    private:
        void internalSetRange(sf::Vector2u start, sf::Vector2u end);
        std::vector<std::unique_ptr<IRenderer>> _renderers;
        sf::Vector2u _start, _end;
        bool _updateRangeOnRender;
    };
}

#endif //EPITECH_RAYTRACER_RENDERERPOOL_HPP
