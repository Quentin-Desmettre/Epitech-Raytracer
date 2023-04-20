/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "objects/Plane.hpp"
#include <numeric>

#define NB_THREADS std::thread::hardware_concurrency()

Renderer::Renderer()
{
    for (int i = 0; i < WINDOW_SIZE.x; i++)
        for (int j = 0; j < WINDOW_SIZE.y; j++)
            _vertexArray.append(sf::Vertex(sf::Vector2f(i, j), sf::Color::Black));
}

void Renderer::handleMovement()
{
    bool reset = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        _camera.move(Camera::FORWARD, 0.1f, reset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        _camera.move(Camera::BACKWARD, 0.1f, reset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        _camera.move(Camera::LEFT, 0.1f, reset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        _camera.move(Camera::RIGHT, 0.1f, reset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        _camera.move(Camera::UP, 0.1f, reset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        _camera.move(Camera::DOWN, 0.1f, reset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _camera.turn(0.1f, 0, reset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _camera.turn(-0.1f, 0, reset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _camera.turn(0, -0.1f, reset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _camera.turn(0, 0.1f, reset);

    if (reset)
        _nbFrames = 0;
}

void Renderer::run(Scene *pool, Camera &camera)
{
    _camera = camera;
    _camera.updateRayDirs();
    _window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "RayTracer");
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
                return;
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                _window.close();
                return;
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                addSphereAtPos(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), pool);
            else
                handleMovement();
        }
        _window.clear();
        if (!_threads)
            perThread(0, WINDOW_SIZE.x, pool);
        else {
            std::vector<std::thread> threads;
            for (uint i = 0; i < NB_THREADS; i++)
                threads.push_back(std::thread(&Renderer::perThread, this,
                i * WINDOW_SIZE.x / NB_THREADS, (i + 1) * WINDOW_SIZE.x / NB_THREADS, pool));
            for (uint i = 0; i < NB_THREADS; i++)
                threads[i].join();
        }
        draw();
        drawToFile();
        _window.display();
    }
}

void Renderer::perThread(int startX, int endX, Scene *pool)
{
    for (int x = startX; x < endX; x++) {
        for (int y = 0; y < WINDOW_SIZE.y; y++) {
            Vec3 colors = Vec3(0, 0, 0);
            for (float i = 0; i < RAYS_PER_PIXEL; i++)
                colors += getPixelFColor(sf::Vector2f(x, y), pool);
            colors /= RAYS_PER_PIXEL;
            addPixel(sf::Vector2f(x, y), colors);
        }
    }
}

Vec3 Renderer::getPixelFColor(sf::Vector2f pos, const Scene *pool) const
{
    Vec3 rayColor = Vec3(1, 1, 1);
    Vec3 light = VEC_NULL;
    Ray ray = Ray(_camera.getPos(), _camera.getRayDir(pos));
    const Object *old = nullptr;

    for (int bounces = 0; bounces <= NB_BOUNCE; bounces++) {
        const Object *obj = pool->getClosest(&ray, old);

        if (!obj)
            break;
        Vec3 inter = obj->getIntersection(&ray);
        Vec3 normal = obj->getNormal(inter);
        float strength = std::max(Math::dot(normal, -ray.getDir()), 0.0f);
        light += obj->getEmissionColor() * rayColor * strength * obj->getEmissionIntensity();
        rayColor *= obj->getColor();
        ray.setOrigin(inter);
        ray.reflect(normal, obj->getReflectivity());
        if (bounces == 0) {
            light += addSunLight(normal, inter, rayColor, pool, obj);
            light += addLightOfPoints(normal, inter, rayColor, pool, obj);
        }
        old = obj;
    }

    // Lumière ambiante
    light += rayColor * getAmbientLight(pos);
    return light;
}

Vec3 Renderer::addSunLight(Vec3 normal, Vec3 inter,
Vec3 color, const Scene *pool, const Object *obj) const
{
    Ray ray(inter, -_sunLight);
    if (pool->getClosest(&ray, obj, true) != nullptr)
        return VEC_NULL;
    return std::max(Math::dot(normal, -_sunLight), 0.0f) * color * _sunColor;
}

Vec3 Renderer::addLightOfPoints(Vec3 normal, Vec3 inter,
Vec3 color, const Scene *pool, const Object *obj) const
{
    Vec3 light = VEC_NULL;

    for (auto &LightPoint : pool->getLightPoints()) {
        Ray ray(inter, Math::normalize(LightPoint.getPos() - inter));
        if (pool->getBetween(&ray, Math::length(LightPoint.getPos() - inter), obj, true) == nullptr) {
            Vec3 tmp = std::max(Math::dot(normal, ray.getDir()), 0.0f) * color * LightPoint.getColorF();
            light += tmp;
        }
    }
    return light;
}

void Renderer::addPixel(sf::Vector2f pos, Vec3 color)
{
    color *= 255.0f;
    color.x = std::min(color.x, 255.0f);
    color.y = std::min(color.y, 255.0f);
    color.z = std::min(color.z, 255.0f);
    if (_nbFrames != 0 && _smooth) {
        sf::Color old = _vertexArray[pos.y * WINDOW_SIZE.x + pos.x].color;
        Vec3 oldColor = Vec3(old.r, old.g, old.b);
        if (oldColor == VEC_NULL || color == VEC_NULL)
            color += oldColor;
        else {
            float weight = 1.0f / (_nbFrames + 1);
            color = oldColor * (1 - weight) + color * weight;
        }
    }
    _vertexArray[pos.y * WINDOW_SIZE.x + pos.x].position = sf::Vector2f(pos.x, pos.y);
    _vertexArray[pos.y * WINDOW_SIZE.x + pos.x].color = sf::Color(color.x, color.y, color.z);
}

void Renderer::addSphereAtPos(sf::Vector2f pos, Scene *pool)
{
    Ray ray = Ray(_camera.getPos(), _camera.getRayDir(pos));
    Vec3 inter = ray.getOrigin() + Math::normalize(ray.getDir()) * 10.0f;
    const Object *obj = pool->getClosest(&ray);
    Sphere *sphere = new Sphere(inter, sf::Color(255, 64, 64), 0.5f);

    if (obj != nullptr)
        sphere->setPos(obj->getIntersection(&ray));
    pool->addObject(sphere);
    _nbFrames = 0;
}
