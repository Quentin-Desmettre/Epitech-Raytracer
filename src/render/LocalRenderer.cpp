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
    sf::Vector3f rayColor = sf::Vector3f(1, 1, 1);
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
        // calcualte light angle with object
        float strength = std::max(Math::dot(normal, -ray.getDir()), 0.0f);
        // add light of object according to its color and other parameters
        light += obj->getEmissionColor() * rayColor * strength * obj->getEmissionIntensity() * lightIntensity;

        // updating ray for next iteration
        rayColor *= obj->getColor();
        ray.setOrigin(inter);
        ray.reflect(normal, obj->getReflectivity());

        // adding light of sun and light points
//        light += addSunLight(normal, inter, rayColor, scene, obj) * lightIntensity;
//        light += addLightOfPoints(normal, inter, rayColor, scene, obj) * lightIntensity;

        // reducing light intensity for next iteration
        lightIntensity *= 0.6;
        old = obj;
    }

    // Lumière ambiante
//    light += rayColor * getAmbientLight(pos);
    return light;
}

Vec3 Raytracer::LocalRenderer::addLightOfPoints(Vec3 normal, Vec3 inter, Vec3 color, const Scene &pool, const IObject *obj)
{
    Vec3 light = VEC3_ZERO;

    for (auto &LightPoint : pool.getLightPoints()) {
        Ray ray(inter, Math::normalize(LightPoint.getPos() - inter));
        // adding light of light points if there is no object between the intersection and the light point
        if (pool.getBetween(ray, Math::length(LightPoint.getPos() - inter), obj, true) == nullptr) {
            Vec3 tmp = std::max(Math::dot(normal, ray.getDir()), 0.0f) * color * LightPoint.getColorF();
            light += tmp;
        }
    }
    return light;
}

sf::Vector3f Raytracer::LocalRenderer::addSunLight(sf::Vector3f normal, sf::Vector3f inter, sf::Vector3f color, const Scene &pool, const IObject *obj)
{
    static float length = Math::length(_sunLight);
    const Ray ray(inter, -_sunLight);

    // returns if there is an object between the sun and the intersection
    if (pool.getBetween(ray, length, obj, true) != nullptr)
        return VEC3_ZERO;
    // returns if the sun is not visible from the intersection
    // if (Math::dot(normal, ray.getDir()) <= 0)
    //     return VEC3_ZERO;
    return std::max(Math::dot(normal, ray.getDir()), 0.0f) * color * _sunColor;
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

Vec3 Raytracer::LocalRenderer::getAmbientLight(sf::Vector2f pos) const
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
