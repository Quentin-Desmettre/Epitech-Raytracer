/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Raytracer
*/

#include "Raytracer.hpp"
#include "scene/SceneBuilder.hpp"
#include "clusters/Client.hpp"
#include "clusters/NetworkRenderer.hpp"
#include "render/RendererPool.hpp"
#include "render/LocalRenderer.hpp"
#include <thread>
#include <algorithm>
#include "objects/Sphere.hpp"

Raytracer::Raytracer::Raytracer(int ac, char **av):
        _array({1, 1})
{
    // Client mode: ac == 2 and av[1] starts with "--port=
    if (ac == 2 && std::string(av[1]).find("--port=") == 0) {
        _isClient = true;
        std::string port = std::string(av[1]).substr(7);
        if (!std::ranges::all_of(port.begin(), port.end(), ::isdigit))
            throw std::invalid_argument("Port must be numeric");
        _port = static_cast<unsigned short>(std::stoul(port));
    }
    // Normal mode
    else {
        SceneBuilder builder(ac, av);

        _scene = builder.build();
        _isClient = false;
        _drawer = std::make_unique<Drawer>(_scene->getResolution().x, _scene->getResolution().y);

        auto global_pool = std::make_unique<RendererPool>(sf::Vector2u{0, 0}, _scene->getResolution(), true);
        // Create clusters
        if (!_scene->getClusters().empty()) {
            for (const auto &cluster : _scene->getClusters())
                global_pool->addRenderer(std::make_unique<Clustering::NetworkRenderer>(cluster));
        }

        // Even if there are clusters, we still render the rest of the image on this computer
        auto thread_pool = std::make_unique<RendererPool>(sf::Vector2u{0, 0}, _scene->getResolution());
        std::size_t max = _scene->isMultithreadingEnabled() ? std::thread::hardware_concurrency() : 1;
        for (std::size_t i = 0; i < max; ++i)
            thread_pool->addRenderer(std::make_unique<LocalRenderer>(sf::Vector2u(0, 0), sf::Vector2u(1, 1)));

        // Set the range
        global_pool->addRenderer(std::move(thread_pool));
        global_pool->setRange();
        _array.resize(_scene->getResolution());
        _renderer = std::move(global_pool);
    }
}

void Raytracer::Raytracer::run()
{
    if (!_isClient)
        runNormal();
    else
        runClient();
}

void Raytracer::Raytracer::runClient()
{
    Clustering::Client client(_port);

    client.run();
}

void Raytracer::Raytracer::runNormal()
{
    sf::Time time;

    // Launch thread for events
    std::thread event_thread(&Raytracer::handleEvents, this);
    while (_run) {
        _renderer->render(*_scene, _array, &time);
        _drawer->draw(_array);
        _drawer->saveToFile(_scene->getOutputFile());
    }
    event_thread.join();
    _drawer->close();
}

void Raytracer::Raytracer::addSphereAtPos(const sf::Vector2f &pos)
{
    // calculating sphere position
    Ray ray = Ray(_scene->getCamera().getPos(), _scene->getCamera().getRayDir(pos));
    Vec3 inter = ray.getOrigin() + Math::normalize(ray.getDir()) * 10.0f;
    const IObject *obj = _scene->getClosest(ray);
    auto sphere = std::make_unique<Sphere>(inter, sf::Color(255, 64, 64), 0.5f);

    // setting sphere position if there is an intersection
    if (obj != nullptr)
        sphere->setPos(obj->getIntersection(ray));
    _scene->addObject(std::move(sphere));
    this->reset(_renderer);
}

void Raytracer::Raytracer::handleMovement(const sf::Event &event)
{
    bool reset = false;

    if (event.key.code == sf::Keyboard::Z)
        _scene->getCamera().move(Camera::FORWARD, 0.1f, reset);
    if (event.key.code == sf::Keyboard::S)
        _scene->getCamera().move(Camera::BACKWARD, 0.1f, reset);
    if (event.key.code == sf::Keyboard::Q)
        _scene->getCamera().move(Camera::LEFT, 0.1f, reset);
    if (event.key.code == sf::Keyboard::D)
        _scene->getCamera().move(Camera::RIGHT, 0.1f, reset);
    if (event.key.code == sf::Keyboard::A)
        _scene->getCamera().move(Camera::UP, 0.1f, reset);
    if (event.key.code == sf::Keyboard::E)
        _scene->getCamera().move(Camera::DOWN, 0.1f, reset);
    if (event.key.code == sf::Keyboard::Up)
        _scene->getCamera().turn(0.1f, 0, reset);
    if (event.key.code == sf::Keyboard::Down)
        _scene->getCamera().turn(-0.1f, 0, reset);
    if (event.key.code == sf::Keyboard::Left)
        _scene->getCamera().turn(0, -0.1f, reset);
    if (event.key.code == sf::Keyboard::Right)
        _scene->getCamera().turn(0, 0.1f, reset);
    if (event.key.code == sf::Keyboard::Enter)
        _drawer->saveToFile(_scene->getOutputFile());

    if (reset)
        this->reset(_renderer);
}

void Raytracer::Raytracer::handleEvents()
{
    sf::Event event;

    while (true) {
        while (_drawer->pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape)) {
                _drawer->saveToFile(_scene->getOutputFile());
                _run = false;
                return;
            } else if (event.type == sf::Event::MouseButtonPressed &&
                       event.mouseButton.button == sf::Mouse::Left &&
                       sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                addSphereAtPos(
                        sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            else if (event.type == sf::Event::KeyPressed)
                handleMovement(event);
        }
    }
}

void Raytracer::Raytracer::reset(const std::unique_ptr<IRenderer> &renderer)
{
    _scene->getCamera().updateRayDirs();
    _renderer->reset();
    for (auto &r : renderer->getSubRenderers())
        reset(r);
}
