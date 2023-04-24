/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LocalRenderer
*/

#ifndef EPITECH_RAYTRACER_LOCALRENDERER_HPP
#define EPITECH_RAYTRACER_LOCALRENDERER_HPP
#include "IRenderer.hpp"

inline sf::Vector3f operator*(sf::Vector3f vec, sf::Vector3f vec2) {
    return sf::Vector3f(vec.x * vec2.x, vec.y * vec2.y, vec.z * vec2.z);
}

inline void operator*=(sf::Vector3f &vec, sf::Vector3f vec2) {
    vec.x *= vec2.x;
    vec.y *= vec2.y;
    vec.z *= vec2.z;
}

namespace Raytracer {

    /**
     * @brief This class is responsible for rendering the scene locally.
     *
     * It will render the scene using the CPU.
     */
    class LocalRenderer : public IRenderer {
    public:
        LocalRenderer(sf::Vector2u start, sf::Vector2u end);

        void render(const Scene &scene) override;

        sf::VertexArray getVertexArray() const override;

        int getThreadsCount() const override;

        void setRange(sf::Vector2u start, sf::Vector2u end) override;

    private:
        void internalSetRange(sf::Vector2u start, sf::Vector2u end);
        void addPixel(sf::Vector2u pos, sf::Vector3f color);
        sf::Vector3f getPixelFColor(sf::Vector2f pos, const Scene &pool);
        static void addLightOfPoints(sf::Vector3f &light, sf::Vector3f normal, sf::Vector3f inter, sf::Vector3f color, const Scene &pool, Object *obj);
        sf::Vector3f addSunLight(sf::Vector3f normal, sf::Vector3f inter, sf::Vector3f color, const Scene &pool, Object *obj);

        sf::VertexArray _vertexArray;
        sf::Vector2u _start, _end;
        int _nbFrames{};

        // TODO: get these from the scene
        sf::Vector3f getAmbientLight(__attribute_maybe_unused__ sf::Vector2f pos) {
            return {50 / 255.0f, 50 / 255.0f, 50 / 255.0f};
        }
        sf::Vector3f _sunLight = Math::normalize(sf::Vector3f(-1, 1, 0));
        sf::Vector3f _sunColor = sf::Vector3f(1, 1, 1);
    };
} // Raytracer

#endif //EPITECH_RAYTRACER_LOCALRENDERER_HPP
