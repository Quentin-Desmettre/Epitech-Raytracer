/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** IRenderer
*/

#ifndef EPITECH_RAYTRACER_IRENDERER_HPP
#define EPITECH_RAYTRACER_IRENDERER_HPP
#include "scene/Scene.hpp"

namespace Raytracer {

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        /**
         * @brief Render the scene.
         *
         * This method will update its internal vertex array.
         * @param scene
         */
        virtual void render(const Scene &scene) = 0;

        /**
         * @brief Set the range of the renderer.
         */
        virtual void setRange(sf::Vector2u start, sf::Vector2u end) = 0;

        /**
         * @brief Get the vertex array of the renderer.
         * @return The internal vertex array of the renderer.
         */
        virtual sf::VertexArray getVertexArray() const = 0;

        /**
         *
         */
         virtual int getThreadsCount() const = 0;
    };
} // Raytracer

#endif //EPITECH_RAYTRACER_IRENDERER_HPP
