/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LocalRenderer
*/

#include "render/LocalRenderer.hpp"
#include <SFML/Network.hpp>
#include "utils/Math.hpp"
#include "utils/Matrix.hpp"
#include "Print.hpp"
#include <semaphore.h>
#include <mutex>

Raytracer::LocalRenderer::LocalRenderer(sf::Vector2u start, sf::Vector2u end)
{
    internalSetRange(start, end);
    _directionalLights.emplace_back();
}

void Raytracer::LocalRenderer::render(const Scene &scene, PointArray &array, sf::Time *time)
{
    _array = &array;
    sf::Clock clock;
    for (unsigned x = _start.x; x < _end.x; x++) {
        for (unsigned y = _start.y; y < _end.y; y++) {
            Vec3 colors = VEC3_ZERO;
            for (int i = 0; i < scene.getRaysPerPixel(); i++)
                colors += getPixelFColor(sf::Vector2f(x, y), scene);
            colors /= static_cast<float>(scene.getRaysPerPixel());
            addPixel({x, y}, colors);
        }
    }
    *time = clock.getElapsedTime();
    Raytracer::cout << "Elapsed time: " << time->asSeconds() << std::endl;
    _nbFrames++;
}

void Raytracer::LocalRenderer::addPixel(sf::Vector2u pos, Vec3 color)
{
    color *= 255.0f;
    color.x = std::min(color.x, 255.0f);
    color.y = std::min(color.y, 255.0f);
    color.z = std::min(color.z, 255.0f);
    if (_nbFrames != 0) {
        sf::Color old = _array->getPixel(pos);
        Vec3 oldColor = Vec3(old.r, old.g, old.b);
        if (oldColor == VEC3_ZERO || color == VEC3_ZERO)
            color += oldColor;
        else {
            float weight = 1.0f / (_nbFrames + 1);
            color = oldColor * (1 - weight) + color * weight;
        }
    }
    _array->setPixel(pos, color);
}

Vec3 getRayDir(sf::Vector2f pos, const Scene &scene)
{
    unsigned maxX = scene.getResolution().x;
    unsigned maxY = scene.getResolution().y;

    Vec3 rayDir = Math::normalize(Vec3 (pos.x - maxX / 2.0f,
                                                        pos.y - maxY / 2.0f, maxX / 2.0f));
    return Math::normalize(Mat4::vecRotate(rayDir, scene.getCamera().getRot(), scene.getCamera().getPos()));
}

Vec3 Raytracer::LocalRenderer::getPixelFColor(sf::Vector2f pos, const Scene &scene)
{
    Ray ray = Ray(scene.getCamera().getPos(), scene.getCamera().getRayDir(pos));
    const IObject *obj = nullptr;
    const IObject *old = nullptr;
    float lightIntensity = 1;
    Vec3 light = VEC3_ZERO;

    for (int bounces = 0; bounces <= scene.getNbBounces(); bounces++) {
        obj = scene.getClosest(ray, old);

        if (!obj)
            break;
        Vec3 inter = obj->getIntersection(ray);
        Vec3 normal = obj->getNormal(inter, ray);

        // add light of object according to its color and other parameters
        light += obj->getLight().illuminate(normal, ray.getColor(), ray.getDir()) * lightIntensity;

        // updating ray for next iteration
        ray.setColor(ray.getColor() * obj->getColor());
        ray.setOrigin(inter);
        ray.reflect(normal, obj);

        // adding light of directional lights and light points
        light += addLights(normal, inter, ray.getColor(), scene, obj) * lightIntensity;

        // reducing light intensity for next iteration
        lightIntensity *= 0.7;
        old = obj;
    }

    // Lumière ambiante
    if (lightIntensity == 1 || !old)
        light += ray.getColor() * getBackgroundLight(pos);
    else if (old->isReflective() || old->isTransparent()) {
        light += ray.getColor() * getAmbientLight(pos) * old->getRoughness();
        if (!obj)
            light += ray.getColor() * getBackgroundLight(pos) * (1.0f - old->getRoughness());
    } else
        light += ray.getColor() * getAmbientLight(pos);
    return light;
}

Vec3 Raytracer::LocalRenderer::addLights(const Vec3 &normal, const Vec3 &inter, const Vec3 &color, const Scene &scene, const IObject *obj)
{
    Vec3 light = VEC3_ZERO;

    for (auto &dirLight : _directionalLights)
        light += dirLight.illuminate(normal, inter, color, scene, obj);
    for (auto &lightPoint : scene.getLightPoints())
        light += lightPoint.illuminate(normal, inter, color, scene, obj);
    return light;
}

void Raytracer::LocalRenderer::setRange(sf::Vector2u start, sf::Vector2u end)
{
    internalSetRange(start, end);
}

void Raytracer::LocalRenderer::internalSetRange(sf::Vector2u start, sf::Vector2u end)
{
    _start = start;
    _end = end;
}

int Raytracer::LocalRenderer::getThreadsCount() const
{
    return 1;
}

Vec3 Raytracer::LocalRenderer::getAmbientLight(unused const sf::Vector2f &pos) const
{
    return {255 / 255.0f, 255 / 255.0f, 255 / 255.0f};
}

Vec3 Raytracer::LocalRenderer::getBackgroundLight(unused const sf::Vector2f &pos) const
{
    return {50 / 255.0f, 50 / 255.0f, 50 / 255.0f};
}

std::pair<sf::Vector2u, sf::Vector2u> Raytracer::LocalRenderer::getRange() const
{
    return {_start, _end};
}

void Raytracer::LocalRenderer::reset()
{
    _nbFrames = 0;
}

const std::vector<std::unique_ptr<Raytracer::IRenderer>> &Raytracer::LocalRenderer::getSubRenderers()
{
    return _subRenderers;
}
