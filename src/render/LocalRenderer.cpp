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
            sf::Vector3f colors{0, 0, 0};
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

void Raytracer::LocalRenderer::addPixel(sf::Vector2u pos, sf::Vector3f color)
{
    color *= 255.0f;
    color.x = std::min(color.x, 255.0f);
    color.y = std::min(color.y, 255.0f);
    color.z = std::min(color.z, 255.0f);
    if (_nbFrames != 0) {
        sf::Color old = _array->getPixel(pos);
        sf::Vector3f oldColor = sf::Vector3f(old.r, old.g, old.b);
        if (oldColor == sf::Vector3f{0,0,0} || color == sf::Vector3f{0,0,0})
            color += oldColor;
        else {
            float weight = 1.0f / (_nbFrames + 1);
            color = oldColor * (1 - weight) + color * weight;
        }
    }
    _array->setPixel(pos, color);
}

sf::Vector3f getRayDir(sf::Vector2f pos, const Scene &scene)
{
    unsigned maxX = scene.getResolution().x;
    unsigned maxY = scene.getResolution().y;

    sf::Vector3f rayDir = Math::normalize(sf::Vector3f (pos.x - maxX / 2.0f,
                                                        pos.y - maxY / 2.0f, maxX / 2.0f));
    return Math::normalize(Mat4::vecRotate(rayDir, scene.getCamera().getRot(), scene.getCamera().getPos()));
}

sf::Vector3f Raytracer::LocalRenderer::getPixelFColor(sf::Vector2f pos, const Scene &scene)
{
    sf::Vector3f light = VEC3_ZERO;
    Ray ray = Ray(scene.getCamera().getPos(), scene.getCamera().getRayDir(pos));
    const IObject *old = nullptr;
    float lightIntensity = 1;

    for (int bounces = 0; bounces <= scene.getNbBounces(); bounces++) {
        const IObject *obj = scene.getClosest(ray, old);

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
        lightIntensity *= 0.6;
        old = obj;
    }

    // Lumière ambiante
    light += ray.getColor() * getAmbientLight(pos);
    return light;
}

Vec3 Raytracer::LocalRenderer::addLights(Vec3 normal, Vec3 inter, Vec3 color, const Scene &scene, const IObject *obj)
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

Vec3 Raytracer::LocalRenderer::getAmbientLight(unused sf::Vector2f pos) const
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
