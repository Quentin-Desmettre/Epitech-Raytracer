/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LocalRenderer
*/

#ifndef EPITECH_RAYTRACER_LOCALRENDERER_HPP
#define EPITECH_RAYTRACER_LOCALRENDERER_HPP
#include "IRenderer.hpp"

namespace Raytracer {

    /**
     * @brief This class is responsible for rendering the scene locally.
     *
     * It will render the scene using the CPU.
     */
    class LocalRenderer : public IRenderer {
    public:
        LocalRenderer(std::size_t xStart, std::size_t xEnd, std::size_t height);

        void render(const Scene &scene) override;

        sf::VertexArray getVertexArray() const override;

    private:
        sf::VertexArray _vertexArray;
        int _xStart, _xEnd, _height;
    };
} // Raytracer


#endif //EPITECH_RAYTRACER_LOCALRENDERER_HPP
