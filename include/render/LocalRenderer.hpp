/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LocalRenderer
*/

#ifndef EPITECH_RAYTRACER_LOCALRENDERER_HPP
#define EPITECH_RAYTRACER_LOCALRENDERER_HPP

#include "IRenderer.hpp"
#include "lights/DirectionalLight.hpp"

namespace Raytracer {

    /**
     * @brief This class is responsible for rendering the scene locally.
     *
     * It will render the scene using the CPU.
     */
    class LocalRenderer : public IRenderer {
    public:
        LocalRenderer(sf::Vector2u start, sf::Vector2u end);

        void render(const Scene &scene, PointArray &array, sf::Time *time) override;

        std::pair<sf::Vector2u, sf::Vector2u> getRange() const override;

        int getThreadsCount() const override;

        void setRange(sf::Vector2u start, sf::Vector2u end) override;

        void reset() override;

        const std::vector<std::unique_ptr<IRenderer>> &getSubRenderers() override;

    private:
        void internalSetRange(sf::Vector2u start, sf::Vector2u end);
        void addPixel(sf::Vector2u pos, sf::Vector3f color);
        sf::Vector3f getPixelFColor(sf::Vector2f pos, const Scene &pool);
        static Vec3 addLightOfPoints(Vec3 normal, Vec3 inter, Vec3 color, const Scene &pool, const IObject *obj);

        PointArray *_array;
        sf::Vector2u _start, _end;
        int _nbFrames{};
        std::vector<std::unique_ptr<IRenderer>> _subRenderers;

        // TODO: get these from the scene
        sf::Vector3f getAmbientLight(sf::Vector2f pos) const;
        std::vector<DirectionalLight> _directionalLights;
    };
} // Raytracer

#endif //EPITECH_RAYTRACER_LOCALRENDERER_HPP
