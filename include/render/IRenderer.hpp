/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** IRenderer
*/

#ifndef EPITECH_RAYTRACER_IRENDERER_HPP
#define EPITECH_RAYTRACER_IRENDERER_HPP
#include "scene/Scene.hpp"
#include "PointArray.hpp"

namespace Raytracer {

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        /**
         * @brief Render the scene.
         *
         * This method will update the given PointArray with the rendered scene.
         * This method should be thread safe, as each thread must update a different part of the PointArray.
         * @param scene
         */
        virtual void render(const Scene &scene, PointArray &array) = 0;

        /**
         * @brief Set the range of the renderer.
         */
        virtual void setRange(sf::Vector2u start, sf::Vector2u end) = 0;

        /**
         *
         */
         virtual int getThreadsCount() const = 0;
    };
} // Raytracer

#endif //EPITECH_RAYTRACER_IRENDERER_HPP
